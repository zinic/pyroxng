#include <unistd.h>     /* Symbolic Constants */
#include <sys/types.h>  /* Primitive System Data Types */
#include <errno.h>      /* Errors */
#include <stdio.h>      /* Input/Output */
#include <sys/wait.h>   /* Wait for Process Termination */
#include <stdlib.h>     /* General Utilities */
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <ev.h>


const short PORT_NO = 2222;

// Structs
struct client_s {
    struct ev_io io;
    struct ev_loop *loop;
    struct sockaddr_in addr;
    socklen_t naddr;
    int fd;
};

struct server_s {
    struct ev_io io;
};

// Functions
void fail(char *errmsg) {
    printf(errmsg);
    exit(1);
}

void client_cb(struct ev_loop *loop, struct ev_io *watcher, int revents) {
    struct client_s *client = (struct client_s *)watcher;
    char str[1024] = ".\0";
    ssize_t nbytes;
    
    if (EV_READ & revents) {
        nbytes = recv(client->fd, str, 100, NULL);
        
        if (nbytes < 0) {
            fail("read error");
        } else if (nbytes == 0) {
            ev_io_stop(loop, watcher);
            free(client);
            printf("Peer disconnected\n");
        } else {
            printf("Received %zu bytes as %s\n", nbytes, str);
        }
    } else if (EV_WRITE & revents) {
        nbytes = send(watcher->fd, "hello", 5, NULL);
        
        if (nbytes < 0) {
            fail("write error");
        } else if (nbytes == 0) {
            ev_io_stop(loop, watcher);
            free(client);
            printf("Peer disconnected\n");
            return;
        } else {
            printf("Sent %zu bytes\n", nbytes);
            ev_io_stop(loop, watcher);
            ev_io_set(watcher, watcher->fd, EV_READ);
            ev_io_start(loop, watcher);
        }
    } else {
        fail("got invalid event");
    }
}

void accept_cb(struct ev_loop *loop, struct ev_io *watcher, int revents) {
    struct client_s *client;
    struct server_s *server = (struct server_s *)watcher;
    int flags;

    if (EV_ERROR & revents) {
        fail("got invalid event");
    }

    client = malloc(sizeof(struct client_s));
    if (!client) {
        fail("client watcher alloc");
    }
    
    client->loop = loop;
    client->naddr = sizeof(client->addr);
    client->fd = accept(watcher->fd, (struct sockaddr *)&client->addr, &client->naddr);
    
    if (client->fd < 0) {
        fail("accept error");
    }
    if ((flags = fcntl(client->fd, F_GETFL, NULL)) == -1) {
        fail("fcntl(F_GETFL)");
    }
    if (fcntl(client->fd, F_SETFL, flags | O_NONBLOCK) == -1) {
        fail("fcntl(F_SETFL, O_NONBLOCK)");
    }

    printf("Successfully connected with client\n");

    ev_io_init((ev_io *)client, client_cb, client->fd, EV_READ);
    ev_io_start(loop, (ev_io *)client);
}

// Main
int main_test(int argc, char **argv) {
    struct ev_loop *loop = ev_default_loop(0);
    struct server_s server;
    struct sockaddr_in addr;
    int sd;

    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        fail("socket error");
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT_NO);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sd, (struct sockaddr *) &addr, sizeof(addr)) != 0) {
        fail("bind error");
    }
    if (listen(sd, 2) < 0) {
        fail("listen error");
    }

    ev_io_init(&server.io, accept_cb, sd, EV_READ);
    ev_io_start(loop, &server.io);

    printf("Listen on %d\n", PORT_NO);
    ev_run(loop, 0);

    return 0;
}
#include <unistd.h>     /* Symbolic Constants */
#include <sys/types.h>  /* Primitive System Data Types */ 
#include <errno.h>      /* Errors */
#include <stdio.h>      /* Input/Output */
#include <sys/wait.h>   /* Wait for Process Termination */
#include <stdlib.h>     /* General Utilities */
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <ev.h>


const int SERVER = 0;
const int WORKER = 1;


struct child_proc {
    int spair[2];
};

struct peer_connection {
    struct sockaddr_in addr;
    int sock_fd;
};

int close_unneeded_child_spairs(struct child_proc procs[], size_t num_children) {
    int result = 0;
    size_t index;
    
    for (index = 0; index < num_children; index++) {
        if ((result = close(procs[index].spair[WORKER])) != 0) {
            break;
        }
    }
    
    return result;
}

size_t next_child(size_t child, size_t num_children) {
    const size_t next = child + 1;
    return next < 0 || child >= num_children ? 0 : next;
}

void on_server(struct child_proc procs[], size_t num_children) {
    int listen_fd, accepted_fd;
    int on = 1;
    size_t dispatch_to = 0;
    struct cmsghdr *cmsg;
    struct sockaddr_in addr;
    struct msghdr msg;

    if ((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("listen socket error");
        return;
    }

    setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, (const char *) &on, sizeof(on));
    
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(2222);
    addr.sin_addr.s_addr = INADDR_ANY;
    
    if (bind(listen_fd, (struct sockaddr *) &addr, sizeof(addr)) != 0) {
        printf("bind error");
        return;
    }

    if (listen(listen_fd, 2) < 0) {
        printf("listen error");
        return;
    }
    
    // Close unneeded FDs
    close_unneeded_child_spairs(procs, num_children);

    for (;;) {
        printf("Listening for a client on FD %i...\n", listen_fd);
        
        if ((accepted_fd = accept(listen_fd, NULL, NULL)) < 0) {
            printf("Failed to accept connection");
            continue;
        }

        printf("Accepted client connection on FD: %i\n", accepted_fd);
        
        // Prep FD for dispatch
        memset(&msg, 0, sizeof(msg));
        
        char cmsgbuf[CMSG_SPACE(sizeof(accepted_fd))];
        msg.msg_control = cmsgbuf;
        msg.msg_controllen = sizeof(cmsgbuf); // necessary for CMSG_FIRSTHDR to return the correct value
        
        cmsg = CMSG_FIRSTHDR(&msg);
        cmsg->cmsg_level = SOL_SOCKET;
        cmsg->cmsg_type = SCM_RIGHTS;
        cmsg->cmsg_len = CMSG_LEN(sizeof(accepted_fd));
        memcpy(CMSG_DATA(cmsg), &accepted_fd, sizeof(accepted_fd));
        msg.msg_controllen = cmsg->cmsg_len; // total size of all control blocks

        // Dispatch and set the next child to dispatch to
        printf("Dispatch fd to worker no. %i\n", dispatch_to);
        sendmsg(procs[dispatch_to].spair[SERVER], &msg, 0);
        dispatch_to = next_child(dispatch_to, num_children);
    }

    close(listen_fd);
}

void on_worker(struct child_proc self) {
    if (close(self.spair[SERVER]) != 0) {
        printf("Failed to close write portion of inherited spair");
        return;
    }
    
    struct msghdr msg;
    int passed_fd, rc;
    char cmsgbuf[CMSG_SPACE(sizeof(int))];
    
    for (;;) {
        printf("Waiting for a socket to work on using FD: %i...\n", self.spair[WORKER]);

        memset(&msg, 0, sizeof(msg));
        msg.msg_control = cmsgbuf;
        msg.msg_controllen = sizeof(cmsgbuf);
        
        rc = recvmsg(self.spair[WORKER], &msg, 0);

        if (rc < 0) {
            printf("Unable to recieve message. Failing.");
            close(self.spair[WORKER]);
            break;
        } else {
            struct cmsghdr *cmsg = CMSG_FIRSTHDR(&msg);

            if (cmsg == NULL || cmsg -> cmsg_type != SCM_RIGHTS) {
                printf("The first control structure contains no file descriptor.\n");
            } else {
                memcpy(&passed_fd, CMSG_DATA(cmsg), sizeof(passed_fd));

                printf("Got FD: %i!\n", passed_fd);

                char buffer[4096];
                size_t nrecv = 0;
                while ((nrecv = recv(passed_fd, buffer, 4096, 0)) > 0) {
                    printf("Got %i bytes\n", nrecv);
                }

                printf("Finished recv with %i bytes\n", nrecv);
                
                if (close(passed_fd) != 0) {
                    printf("Failed to close FD: %i!\n", passed_fd);
                }
            }
        }
    }
}


int main(int argc, char **argv) {
    struct child_proc procs[8];
    pid_t pid;
    int i;

    printf("Process begins\n");
    
    /* now create new process */
    for (i = 0; i < 8; i++) {
        int spair[2];

        // Unix dgram socket for exporting accepted FDs
        if (socketpair(AF_UNIX, SOCK_DGRAM, 0, spair) != 0) {
            perror("socketpair() failed");
            exit(-1);
        }
        
        procs[i].spair[0] = spair[0];
        procs[i].spair[1] = spair[1];

        pid = fork();
        
        if (pid > 0) {
            on_worker(procs[i]);
            break;
        } else if (pid < 0) {
            printf("Fork error\n");
            exit(1);
        }
    }

    if (pid == 0) {
        printf("Starting up server...\n");
        on_server(procs, 8);
    }

    exit(0);
}
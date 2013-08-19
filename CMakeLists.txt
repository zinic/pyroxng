project(pyrox)

cmake_minimum_required(VERSION 2.8)

include_directories(/usr/include/ev, /usr/include/python)
link_libraries(ev)
link_libraries(python2.7)
add_executable(pyrox ev_test.c main.c)

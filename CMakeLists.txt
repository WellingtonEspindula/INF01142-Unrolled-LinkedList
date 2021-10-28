cmake_minimum_required(VERSION 3.20)
project(Locality_Study C)

set(CMAKE_C_STANDARD 11)

add_executable(Locality_Study main.c classic_linkedlist.c linkedlist.h mp_linkedlist.c)

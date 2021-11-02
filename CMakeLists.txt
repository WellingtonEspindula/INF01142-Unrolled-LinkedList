cmake_minimum_required(VERSION 3.20)
project(Locality_Study C)

set(CMAKE_C_STANDARD 11)

#set(CMAKE_CXX_FLAGS "-Wall -Wextra")
#set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_C_FLAGS "-Ofast")

add_executable(Locality_Study main.c LinkedList.h Classic_LinkedList.c
        Node.h Unrolled_LinkedList.c)

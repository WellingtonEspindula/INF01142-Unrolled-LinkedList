cmake_minimum_required(VERSION 3.20)
project(Locality_Study C)

set(CMAKE_C_STANDARD 11)

add_executable(Locality_Study main.c LinkedList.h Classic_LinkedList.c
        Node.h Unrolled_LinkedList.c)

target_link_libraries(${PROJECT_NAME} m)

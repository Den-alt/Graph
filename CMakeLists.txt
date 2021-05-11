cmake_minimum_required(VERSION 3.19)
project(Graph C)

set(CMAKE_C_STANDARD 11)

set(SOURCE Sources/readinfo.c Sources/graph.c)
set(HEADER Headers/info.h)

add_executable(Graph main.c ${SOURCE} ${HEADER})
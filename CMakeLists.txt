cmake_minimum_required(VERSION 3.21)
project(PL2 C)

set(CMAKE_C_STANDARD 99)

add_executable(untitled Source.c binary.c binary.h btree.c btree.h node.c node.h)
cmake_minimum_required(VERSION 3.21)
project(tetris C)

set(CMAKE_C_STANDARD 11)

add_executable(tetris main.c tetris.c tetris.h vector.c vector.h)

cmake_minimum_required(VERSION 3.20)
project(circular_buffer C)

set(CMAKE_C_STANDARD 11)

add_executable(circular_buffer main.c circular_buffer.c circular_buffer.h)

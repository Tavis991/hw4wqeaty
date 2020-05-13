cmake_minimum_required(VERSION 3.16)
project(hw4 C)

set(CMAKE_C_STANDARD 99)

add_executable(hw4 main.c sort_league.c sort_league.h Team.h Team.c Match.h Match.c League.h League.c)
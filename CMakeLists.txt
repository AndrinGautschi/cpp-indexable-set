cmake_minimum_required(VERSION 3.14)
project(indexable)

set(CMAKE_CXX_STANDARD 17)

# build calculator executable
add_executable(executor main.cpp indexableSet.h)

# build calculator test executable
include_directories(../libs/cute)
add_executable(tester tests/test.cpp indexableSet.h)

cmake_minimum_required(VERSION 3.14)
project(words)

set(CMAKE_CXX_STANDARD 17)

# specify library calculator
add_library(word_lib
        word.cpp)

# build calculator executable
add_executable(executor main.cpp)
target_link_libraries(executor word_lib)

# build calculator test executable
include_directories(../libs/cute)
add_executable(tester tests/test.cpp)
target_link_libraries(tester word_lib)
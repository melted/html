cmake_minimum_required(VERSION 3.3)
project(html)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES hello.cpp)
add_executable(hello ${SOURCE_FILES})
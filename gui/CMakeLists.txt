cmake_minimum_required(VERSION 3.5)
project(pq2gui)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES pq2gui.cpp pq2gui.h)
add_library(pq2gui SHARED ${SOURCE_FILES})

target_link_libraries(pq2gui pq2game)
include_directories(../game)
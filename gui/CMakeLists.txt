cmake_minimum_required(VERSION 3.27)
project(pq2gui)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCE_FILES pq2gui.cpp pq2gui.h view.cpp view.h)
add_library(pq2gui SHARED ${SOURCE_FILES})

target_link_libraries(pq2gui pq2game)
include_directories(../game)
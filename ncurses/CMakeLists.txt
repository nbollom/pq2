cmake_minimum_required(VERSION 3.5)
project(pq2ncurses)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES pq2ncurses.cpp pq2ncurses.h view.h mainmenu.cpp mainmenu.h view.cpp)
add_library(pq2ncurses SHARED ${SOURCE_FILES})

target_link_libraries(pq2ncurses pq2gui pq2game pq2utils ncurses)
include_directories(../gui ../game ../utils)
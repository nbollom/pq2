cmake_minimum_required(VERSION 3.5)
project(pq2ncurses)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCE_FILES pq2ncurses.cpp pq2ncurses.h nview.h mainmenu.cpp mainmenu.h nview.cpp)
add_library(pq2ncurses SHARED ${SOURCE_FILES})

target_link_libraries(pq2ncurses pq2gui pq2game pq2utils ncurses)
include_directories(../gui ../game ../utils)
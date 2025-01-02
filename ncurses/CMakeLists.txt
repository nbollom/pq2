cmake_minimum_required(VERSION 3.27)
project(pq2ncurses)

set(
        SOURCE_FILES
        pq2ncurses.cpp
        pq2ncurses.hpp
        mainmenu.cpp
        mainmenu.hpp
        ncursesview.cpp
        ncursesview.hpp
        charactercreator.cpp
        charactercreator.hpp
        gamescreen.cpp
        gamescreen.hpp
        loadscreen.cpp
        loadscreen.hpp
)

add_library(pq2ncurses SHARED ${SOURCE_FILES})

target_link_libraries(pq2ncurses pq2gui pq2game pq2utils ncurses)
include_directories(../gui ../game ../utils)
cmake_minimum_required(VERSION 3.27)
project(pq2gui)

set(
        SOURCE_FILES
        pq2gui.cpp
        pq2gui.hpp
        view.cpp
        view.hpp
)

add_library(pq2gui SHARED ${SOURCE_FILES})

target_link_libraries(pq2gui pq2game)
target_include_directories(pq2gui
        PRIVATE pq2game
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)
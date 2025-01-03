cmake_minimum_required(VERSION 3.27)
project(pq2qt)

set(
        SOURCE_FILES
        pq2qt.cpp
        pq2qt.hpp
        qtmainmenu.cpp
        qtmainmenu.hpp
        qtcharatercreator.cpp
        qtcharatercreator.hpp
        qtgamescreen.cpp
        qtgamescreen.hpp
)

find_package(Qt6 REQUIRED Core Widgets)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_library(pq2qt SHARED ${SOURCE_FILES} resources.qrc)

target_link_libraries(pq2qt pq2gui pq2game pq2utils Qt6::Core Qt6::Widgets)
target_include_directories(pq2qt
        PRIVATE pq2gui pq2game pq2utils
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

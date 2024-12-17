cmake_minimum_required(VERSION 3.27)
project(pq2qt)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCE_FILES pq2qt.cpp pq2qt.h qtmainmenu.cpp qtmainmenu.h qtcharatercreator.cpp qtcharatercreator.h qtgamescreen.cpp qtgamescreen.h)

find_package(Qt5 REQUIRED Core Widgets)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_library(pq2qt SHARED ${SOURCE_FILES} resources.qrc)

target_link_libraries(pq2qt pq2gui pq2game pq2utils Qt5::Core Qt5::Widgets)
include_directories(../gui ../game ../utils)

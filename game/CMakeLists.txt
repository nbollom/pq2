cmake_minimum_required(VERSION 3.5)
project(pq2game)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES game.cpp spells.h spells.cpp game.h types.h offensiveattributes.h offensiveattributes.cpp defensiveattributes.h defensiveattributes.cpp shields.cpp shields.h armors.cpp armors.h weapons.cpp weapons.h specials.cpp specials.h itemattributes.cpp itemattributes.h itemofs.cpp itemofs.h boringitems.cpp boringitems.h monsters.cpp monsters.h races.cpp races.h classes.cpp classes.h titles.cpp titles.h newgame.cpp newgame.h character.cpp character.h)
add_library(pq2game SHARED ${SOURCE_FILES})

target_link_libraries(pq2game pq2utils)
include_directories(../utils)
cmake_minimum_required(VERSION 3.27)
project(pq2game)

include(FetchContent)

FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
    GIT_SHALLOW ON
    GIT_PROGRESS ON
    FIND_PACKAGE_ARGS 3.11.3
)

FetchContent_MakeAvailable(nlohmann_json)

set(SOURCE_FILES game.cpp spells.h spells.cpp game.h types.h offensiveattributes.h offensiveattributes.cpp defensiveattributes.h defensiveattributes.cpp shields.cpp shields.h armors.cpp armors.h weapons.cpp weapons.h specials.cpp specials.h itemattributes.cpp itemattributes.h itemofs.cpp itemofs.h boringitems.cpp boringitems.h monsters.cpp monsters.h races.cpp races.h classes.cpp classes.h titles.cpp titles.h newgame.cpp newgame.h character.h monstermods.cpp monstermods.h
        jsonserialiser.cpp
        jsonserialiser.h)

add_library(pq2game SHARED ${SOURCE_FILES})

target_link_libraries(pq2game PRIVATE pq2utils nlohmann_json::nlohmann_json)
include_directories(../utils nlohmann_json::nlohmann_json)
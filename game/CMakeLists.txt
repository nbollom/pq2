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

set(
        SOURCE_FILES
        game.cpp
        spells.hpp
        spells.cpp
        game.hpp
        types.hpp
        offensiveattributes.hpp
        offensiveattributes.cpp
        defensiveattributes.hpp
        defensiveattributes.cpp
        shields.cpp
        shields.hpp
        armors.cpp
        armors.hpp
        weapons.cpp
        weapons.hpp
        specials.cpp
        specials.hpp
        itemattributes.cpp
        itemattributes.hpp
        itemofs.cpp
        itemofs.hpp
        boringitems.cpp
        boringitems.hpp
        monsters.cpp
        monsters.hpp
        races.cpp
        races.hpp
        classes.cpp
        classes.hpp
        titles.cpp
        titles.hpp
        newgame.cpp
        newgame.hpp
        character.hpp
        monstermods.cpp
        monstermods.hpp
        jsonserialiser.cpp
        jsonserialiser.hpp
        character.cpp
)

add_library(pq2game SHARED ${SOURCE_FILES})

target_link_libraries(pq2game PRIVATE pq2utils nlohmann_json::nlohmann_json)
target_include_directories(pq2game
        PRIVATE pq2utils nlohmann_json::nlohmann_json
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)
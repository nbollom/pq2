cmake_minimum_required(VERSION 3.27)
project(pq2utils)

set(
        SOURCE_FILES
        utils.hpp
        signals.cpp
        signals.hpp
        commandline.cpp
        commandline.hpp
        commandlineexeptions.cpp
        commandlineexeptions.hpp
        commandlineoptions.hpp
        commandlineoptions.cpp
        romannumerals.cpp
        romannumerals.hpp
        namegenerator.cpp
        namegenerator.hpp
)

add_library(pq2utils SHARED ${SOURCE_FILES})

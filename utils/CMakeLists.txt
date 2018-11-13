cmake_minimum_required(VERSION 3.5)
project(pq2utils)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES utils.h signals.cpp signals.h commandline.cpp commandline.h commandlineexeptions.cpp commandlineexeptions.h commandlineoptions.h commandlineoptions.cpp romannumerals.cpp romannumerals.h namegenerator.cpp namegenerator.h)
add_library(pq2utils SHARED ${SOURCE_FILES})

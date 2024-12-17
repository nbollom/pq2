cmake_minimum_required(VERSION 3.27)
project(pq2utils)

set(SOURCE_FILES utils.h signals.cpp signals.h commandline.cpp commandline.h commandlineexeptions.cpp commandlineexeptions.h commandlineoptions.h commandlineoptions.cpp romannumerals.cpp romannumerals.h namegenerator.cpp namegenerator.h)
add_library(pq2utils SHARED ${SOURCE_FILES})

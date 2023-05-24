cmake_minimum_required(VERSION 3.5)
project(pq2cocoa)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCE_FILES
	pq2cocoa.mm
	pq2cocoa.h
	cocoamainmenu.mm
	cocoamainmenu.h
	cocoacharatercreator.mm
	cocoacharatercreator.h
)

configure_file(../resources/pq.png ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/pq.png COPYONLY)

add_library(pq2cocoa SHARED ${SOURCE_FILES})

target_link_libraries(pq2cocoa pq2gui pq2game pq2utils "-framework cocoa")
include_directories(../gui ../game ../utils)

cmake_minimum_required(VERSION 3.5)
project(pq2mac)


set(SOURCE_FILES
	pq2mac.mm
	pq2mac.hpp
	cocoamainmenu.mm
	cocoamainmenu.hpp
	cocoacharatercreator.mm
	cocoacharatercreator.hpp
)

configure_file(../resources/pq.png ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/pq.png COPYONLY)

add_library(pq2mac SHARED ${SOURCE_FILES})

target_link_libraries(pq2mac pq2gui pq2game pq2utils "-framework cocoa")
target_include_directories(pq2mac
    PRIVATE pq2gui pq2game pq2utils
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

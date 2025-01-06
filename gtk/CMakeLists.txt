cmake_minimum_required(VERSION 3.27)
project(pq2gtk)

set(
        SOURCE_FILES
        pq2gtk.cpp
        pq2gtk.hpp
        ${CMAKE_CURRENT_BINARY_DIR}/resources.cpp
        mainmenu.cpp
        mainmenu.cpp
        mainmenu.hpp
        charactercreator.cpp
        charactercreator.hpp
        gtkview.cpp
        gtkview.hpp
        gamescreen.cpp
        gamescreen.hpp
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)

find_program(GLIB_COMPILE_RESOURCES NAMES glib-compile-resources REQUIRED)

add_custom_command(
        OUTPUT resources.cpp
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMAND ${GLIB_COMPILE_RESOURCES}
        ARGS
        --generate-source
        --target=${CMAKE_CURRENT_BINARY_DIR}/resources.cpp
        resources.xml
        VERBATIM
        MAIN_DEPENDENCY resources.xml
        DEPENDS
        ../resources/pq.png
        style.css
)

add_custom_target(
        dummy-resource
        DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/resources.cpp
)

add_library(pq2gtk SHARED ${SOURCE_FILES})
add_dependencies(pq2gtk dummy-resource)

target_link_libraries(pq2gtk pq2gui pq2game pq2utils ${GTKMM_LIBRARIES})
target_link_directories(pq2gtk
        PRIVATE ${GTKMM_LIBRARY_DIRS}
        INTERFACE pq2gtk ${GTKMM_LIBRARY_DIRS}
)
target_include_directories(pq2gtk
        PRIVATE pq2gui pq2game pq2utils ${GTKMM_INCLUDE_DIRS}
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR} ${GTKMM_INCLUDE_DIRS}
)
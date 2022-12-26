cmake_minimum_required(VERSION 3.10)
project(opengl_lab)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES 
    "source/*.cpp")
file(GLOB_RECURSE HEADERS 
    "source/*.h")
set(ALL_FILES ${SOURCES} ${HEADERS})

include_directories(
    "include" 
    "include/opengl" 
    "include/utils")

foreach(FILE ${ALL_FILES}) 
    # Get the directory of the source file
    get_filename_component(PARENT_DIR "${FILE}" DIRECTORY)

    # Remove common directory prefix to make the group
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" GROUP "${PARENT_DIR}")

    # Make sure we are using windows slashes
    string(REPLACE "/" "\\" GROUP "${GROUP}")

    source_group("${GROUP}" FILES "${FILE}")
endforeach()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT opengl_lab)

add_executable(opengl_lab ${SOURCES} ${HEADERS})



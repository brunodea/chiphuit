cmake_minimum_required (VERSION 3.5.2)
project (chiphuit)

set (CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set (EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set (LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

include_directories("${PROJECT_SOURCE_DIR}/src")

add_subdirectory (src)


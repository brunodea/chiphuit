add_executable(chiphuit main.cpp)
target_link_libraries (chiphuit cpu util)

include_directories("${PROJECT_SOURCE_DIR}/src/cpu")
include_directories("${PROJECT_SOURCE_DIR}/src/util")

add_subdirectory (cpu)
add_subdirectory (util)
install (TARGETS chiphuit DESTINATION bin)

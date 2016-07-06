add_executable(chiphuit main.cpp)
target_link_libraries (chiphuit cpu)

include_directories("${PROJECT_SOURCE_DIR}/src/cpu")

add_subdirectory (cpu)
install (TARGETS chiphuit DESTINATION bin)

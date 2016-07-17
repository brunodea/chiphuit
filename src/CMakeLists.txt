add_executable(chiphuit main.cpp chiphuit.cpp)
target_link_libraries (chiphuit cpu util mem)

include_directories("${PROJECT_SOURCE_DIR}/src/cpu")
include_directories("${PROJECT_SOURCE_DIR}/src/mem")
include_directories("${PROJECT_SOURCE_DIR}/src/util")

add_subdirectory (cpu)
add_subdirectory (mem)
add_subdirectory (util)

install (TARGETS chiphuit DESTINATION bin)
install (FILES chiphuit.h DESTINATION include)

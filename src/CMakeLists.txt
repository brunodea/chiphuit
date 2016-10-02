add_executable(chiphuit main.cpp chiphuit.cpp debugger.cpp)
target_link_libraries (chiphuit cpu util mem video)

include_directories("${PROJECT_SOURCE_DIR}/src/cpu")
include_directories("${PROJECT_SOURCE_DIR}/src/mem")
include_directories("${PROJECT_SOURCE_DIR}/src/util")
include_directories("${PROJECT_SOURCE_DIR}/src/video")
include_directories("${PROJECT_SOURCE_DIR}/src/input")

add_subdirectory (cpu)
add_subdirectory (mem)
add_subdirectory (util)
add_subdirectory (video)
add_subdirectory (input)

install (TARGETS chiphuit DESTINATION bin)
install (FILES chiphuit.h debugger.h DESTINATION include)

INCLUDE(FindPkgConfig)

FIND_PACKAGE( Boost 1.61 COMPONENTS  REQUIRED)
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)

include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${Boost_LIBRARIES})

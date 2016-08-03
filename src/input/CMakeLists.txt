add_library(input input.cpp)

install (TARGETS input DESTINATION bin)
install (FILES input.h DESTINATION include)

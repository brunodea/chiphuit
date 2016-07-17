add_library(mem mem.cpp)

install (FILES mem.h DESTINATION include)
install (TARGETS mem DESTINATION bin)

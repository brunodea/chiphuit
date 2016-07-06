add_library(cpu cpu.cpp)

install (TARGETS cpu DESTINATION bin)
install (FILES cpu.h DESTINATION include)

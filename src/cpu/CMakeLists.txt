add_library(cpu cpu.cpp instr.cpp)

install (TARGETS cpu DESTINATION bin)
install (FILES cpu.h instr.h DESTINATION include)

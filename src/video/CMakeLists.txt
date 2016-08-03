add_library(video video.cpp)

install (TARGETS video DESTINATION bin)
install (FILES video.h DESTINATION include)

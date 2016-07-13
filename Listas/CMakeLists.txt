add_library(list STATIC list.c dlist.c)
file(COPY list.h dlist.h DESTINATION ${CMAKE_SOURCE_DIR}/include)
install(TARGETS list ARCHIVE DESTINATION ${CMAKE_SOURCE_DIR}/lib)

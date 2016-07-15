#install(FILES alloc.h DESTINATION ${CMAKE_SOURCE_DIR}/include)
file(COPY ./alloc.h DESTINATION ${CMAKE_SOURCE_DIR}/include)
#add_library(ed1 STATIC alloc.c)
#install(TARGETS alloc ARCHIVE DESTINATION ${CMAKE_SOURCE_DIR}/lib)

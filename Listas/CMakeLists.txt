add_library(list STATIC list.c)
file(COPY ./list.h DESTINATION ${CMAKE_SOURCE_DIR}/include)
install(TARGETS list ARCHIVE DESTINATION ${CMAKE_SOURCE_DIR}/lib)

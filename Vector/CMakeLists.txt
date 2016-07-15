#install(FILES stack.h DESTINATION ${CMAKE_SOURCE_DIR}/include)
#add_library(ed1 STATIC vector.c)
file(COPY vector.h DESTINATION ${CMAKE_SOURCE_DIR}/include)
#install(TARGETS vector ARCHIVE DESTINATION ${CMAKE_SOURCE_DIR}/lib)

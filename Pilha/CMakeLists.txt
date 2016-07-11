#install(FILES stack.h DESTINATION ${CMAKE_SOURCE_DIR}/include)
add_library(stack STATIC stack.c)
file(COPY ./stack.h DESTINATION ${CMAKE_SOURCE_DIR}/include)
install(TARGETS stack ARCHIVE DESTINATION ${CMAKE_SOURCE_DIR}/lib)

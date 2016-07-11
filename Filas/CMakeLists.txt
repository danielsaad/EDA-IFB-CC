#install(FILES stack.h DESTINATION ${CMAKE_SOURCE_DIR}/include)
add_library(queue STATIC queue.c)
file(COPY ./queue.h DESTINATION ${CMAKE_SOURCE_DIR}/include)
install(TARGETS queue ARCHIVE DESTINATION ${CMAKE_SOURCE_DIR}/lib)

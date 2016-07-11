include_directories(.)
install(FILES list.h DESTINATION ${CMAKE_SOURCE_DIR}/include)
add_library(list STATIC list.c)
install(TARGETS list ARCHIVE DESTINATION ${CMAKE_SOURCE_DIR}/lib)

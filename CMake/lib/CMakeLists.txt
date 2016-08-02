ADD_LIBRARY(geometria STATIC triangulo.c quadrado.c)
install (TARGETS geometria ARCHIVE DESTINATION ${CMAKE_SOURCE_DIR}/lib)
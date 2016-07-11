CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
project ("ED1" C)

#set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall")

LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/lib)

add_subdirectory(Listas)
add_subdirectory(Utils)
add_subdirectory(Exemplos)
add_subdirectory(Vetores)

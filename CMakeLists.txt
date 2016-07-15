CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
project ("ED1" C)

#set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall")

LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/lib)

add_subdirectory(Listas)
add_subdirectory(Pilha)
add_subdirectory(Filas)
add_subdirectory(Utils)
add_subdirectory(Exemplos)
add_subdirectory(Vetores)
add_subdirectory(Vector)
add_subdirectory(Árvores)
add_subdirectory(Sorting)

add_library(ed1 STATIC Filas/queue.c Filas/deque.c Filas/priority_queue.c
    Listas/dlist.c Listas/list.c Pilha/stack.c Sorting/bubble_sort.c
    Sorting/counting_sort.c Sorting/heap_sort.c Sorting/insertion_sort.c
    Sorting/merge_sort.c Sorting/quick_sort.c Sorting/radix_sort.c
    Utils/alloc.c Vector/vector.c Árvores/bst.c)



install(TARGETS ed1 ARCHIVE DESTINATION ${CMAKE_SOURCE_DIR}/lib)

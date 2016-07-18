CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT ("ED1" C)

SET(CMAKE_VERBOSE_MAKEFILE on)
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall")

LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/lib)


MESSAGE(STATUS "Lib files: ${lib_files}")

FILE (COPY ./Sorting/insertion_sort.h
	./Sorting/sorting.h
	./Sorting/ordenacao.h
	./Sorting/heap_sort.h
	./Sorting/counting_sort.h
	./Sorting/radix_sort.h
	./Sorting/bubble_sort.h
	./Sorting/quick_sort.h
	./Sorting/merge_sort.h
	./Utils/alloc.h
	./Vector/vector.h
	./Stack/stack.h
	./Queue/queue.h
	./Queue/priority_queue.h
	./Queue/deque.h
	./Tree/bst.h
	./List/list.h
	./List/dlist.h 
	DESTINATION ${CMAKE_SOURCE_DIR}/include) 

ADD_LIBRARY(ed1 ./Sorting/merge_sort.c
	./Sorting/quick_sort.c
	./Sorting/bubble_sort.c
	./Sorting/heap_sort.c
	./Sorting/counting_sort.c
	./Sorting/radix_sort.c
	./Sorting/insertion_sort.c
	./Utils/alloc.c
	./CMakeFiles/2.8.12.2/CompilerIdC/CMakeCCompilerId.c
	./Array/alocacao_vetor_1.c
	./Array/alocacao_matriz_1.c
	./Vector/vector.c
	./Stack/stack.c
	./Queue/queue.c
	./Queue/priority_queue.c
	./Queue/deque.c
	./Tree/bst.c
	./List/list.c
	./List/dlist.c) 

INSTALL(TARGETS ed1 ARCHIVE DESTINATION ${CMAKE_SOURCE_DIR}/lib)

ADD_SUBDIRECTORY(Examples)

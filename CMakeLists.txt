CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT ("ED1" C)

SET(CMAKE_VERBOSE_MAKEFILE on)
if(CMAKE_BUILD_TYPE MATCHES DEBUG)
	MESSAGE(STATUS "Debug mode")
	SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall")
else()
	MESSAGE(STATUS "Release mode")
	set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}  -Wall")
endif(CMAKE_BUILD_TYPE MATCHES DEBUG)


LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/lib)


MESSAGE(STATUS "Lib files: ${lib_files}")

LIST(APPEND header_list
	./Sorting/insertion_sort.h
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
)


#cópia dos cabeçalhos para o diretório include
foreach(header ${header_files})
	FILE(COPY ${header} DESTINATION ${CMAKE_SOURCE_DIR}/include)
endforeach(header ${header_files})


#compilação dos arquivos da biblioteca ed1.a
ADD_LIBRARY(ed1 STATIC ./Sorting/merge_sort.c
	./Sorting/quick_sort.c
	./Sorting/bubble_sort.c
	./Sorting/heap_sort.c
	./Sorting/counting_sort.c
	./Sorting/radix_sort.c
	./Sorting/insertion_sort.c
	./Utils/alloc.c
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

#Compilação dos executáveis
ADD_SUBDIRECTORY(Examples)

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


LIST(APPEND header_list
	./Ordenacao/insertion_sort.h
	./Ordenacao/sorting.h
	./Ordenacao/ordenacao.h
	./Ordenacao/heap_sort.h
	./Ordenacao/counting_sort.h
	./Ordenacao/radix_sort.h
	./Ordenacao/bubble_sort.h
	./Ordenacao/quick_sort.h
	./Ordenacao/merge_sort.h
	./Lista/list.h
	./Lista/dlist.h
	./Utils/alloc.h
	./Arvore/bst.h
	./Vector/vector.h
	./Fila/queue.h
	./Fila/priority_queue.h
	./Fila/deque.h
	./Pilha/stack.h
)


#cópia dos cabeçalhos para o diretório include
foreach(header ${header_list})
	FILE(COPY ${header} DESTINATION ${CMAKE_SOURCE_DIR}/include)
endforeach(header ${header_list})


#compilação dos arquivos da biblioteca ed1.a
ADD_LIBRARY(ed1 STATIC
	./Ordenacao/merge_sort.c
	./Ordenacao/quick_sort.c
	./Ordenacao/bubble_sort.c
	./Ordenacao/heap_sort.c
	./Ordenacao/counting_sort.c
	./Ordenacao/radix_sort.c
	./Ordenacao/insertion_sort.c
	./Lista/list.c
	./Lista/dlist.c
	./Utils/alloc.c
	./Arvore/bst.c
	./Vector/vector.c
	./Fila/queue.c
	./Fila/priority_queue.c
	./Fila/deque.c
	./Pilha/stack.c
)
INSTALL(TARGETS ed1 ARCHIVE DESTINATION ${CMAKE_SOURCE_DIR}/lib)

#Compilação dos executáveis
ADD_SUBDIRECTORY(Exemplos)

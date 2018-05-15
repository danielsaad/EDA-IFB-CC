
include_directories(${CMAKE_SOURCE_DIR}/include)
LIST(APPEND src_list
	./bst_exemplo_1.c
	./passagem_por_valor_exemplo_1.c
	./memory_leak_exemplo_2.c
	./alocacao_ponteiro_exemplo_1.c
	./passagem_por_referencia_exemplo_3.c
	./alocacao_vetor_exemplo_1.c
	./ordenacao_exemplo_1.c
	./alocacao_ponteiro_exemplo_2.c
	./priority_queue_crud.c
	./ponteiro_vetor_exemplo_1.c
        ./ponteiro_vetor_exemplo_2.c
	./passagem_por_referencia_exemplo_2.c
	./stack_crud.c
	./funcoes_exemplo_1.c
	./ponteiro_exemplo_1.c
        ./ponteiro_exemplo_2.c
	./queue_crud.c
	./list_crud.c
	./bst_crud.c
	./dlist_crud.c
	./memory_leak_exemplo_1.c
	./deque_crud.c
        ./passagem_por_referencia_exemplo_1.c
        ./alocacao_matrix_exemplo_1.c
        ./wild_pointer_exemplo_1.c
        ./wild_pointer_exemplo_2.c
        ./ponteiro_para_funcao_exemplo_1.c
        ./ponteiro_para_funcao_exemplo_2.c
        ./qsort_bsearch_exemplo.c
        ./busca_binaria_exemplo.c
        ./busca_binaria_recursiva_exemplo.c
	./list_filter.c
	./list_quicksort.c
    ./exemplo_fila_cantina.c
    ./exemplo_fila_de_prioridade_cantina.c
)

foreach(src ${src_list})
	string(REPLACE ".c" "" executable ${src})
	add_executable(${executable} ${src})
	target_link_libraries(${executable} ed1)
    install (TARGETS ${executable} RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/bin)
endforeach(src ${src_files})

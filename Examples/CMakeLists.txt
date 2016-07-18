
include_directories(${CMAKE_SOURCE_DIR}/include)
LIST(APPEND src_list
	./bst_example_1.c
	./funcoes_1.c
	./memory_leak_example_2.c
	./pointer_allocation_example_1.c
	./pass_by_value_example_1.c
	./priority_queue_crud.c
	./sort_example.c
	./pass_by_reference_example_1.c
	./pointer_array_example_1.c
	./stack_crud.c
	./pointer_example_1.c
	./pass_by_reference_example_3.c
	./queue_crud.c
	./list_crud.c
	./bst_crud.c
	./pass_by_reference_example_2.c
	./pointer_example_2.c
	./dlista_cruc.c
	./deque_crud.c
	./pointer_allocation_example_2.c
	./memory_leak_example_1.c
)

foreach(src ${src_list})
	string(REPLACE ".c" "" executable ${src})
	add_executable(${executable} ${src})
	target_link_libraries(${executable} ed1)
endforeach(src ${src_files})

include(ExternalProject)
ExternalProject_Add(check
  URL https://github.com/libcheck/check/archive/master.zip
  INSTALL_COMMAND ""
)

ExternalProject_Get_Property(check binary_dir)
add_library(libcheck UNKNOWN IMPORTED)
set_target_properties(libcheck PROPERTIES
  IMPORTED_LOCATION ${binary_dir}/src/libcheck.a)

add_dependencies(libcheck check)

message(STATUS "Check = ${binary_dir}")

include_directories(${binary_dir}/src)
include_directories(${binary_dir})

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(teste_main teste_main.c
    teste_stack.c
    teste_queue.c
    teste_priority_queue.c
    teste_deque.c
    teste_list.c
    teste_dlist.c
    teste_ordenacao.c
    teste_bst.c
    teste_avl_tree.c
    teste_treap.c
)

target_link_libraries(teste_main libcheck ed1 m rt pthread)

install(TARGETS teste_main RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/bin)


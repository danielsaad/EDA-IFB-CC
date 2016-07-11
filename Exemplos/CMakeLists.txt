add_executable(lista_crud lista_crud.c)
add_executable(pilha_crud pilha_crud.c)
add_executable(fila_crud fila_crud.c)

include_directories(${CMAKE_SOURCE_DIR}/include)
target_link_libraries(lista_crud list alloc)
target_link_libraries(pilha_crud stack alloc)
target_link_libraries(fila_crud queue alloc)

install(TARGETS lista_crud RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/bin)
install(TARGETS fila_crud RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/bin)
install(TARGETS pilha_crud RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/bin)

add_executable(alocacao_matriz_1 alocacao_matriz_1.c)
add_executable(alocacao_vetor_1 alocacao_vetor_1.c)

include_directories(${CMAKE_SOURCE_DIR}/include)
target_link_libraries(alocacao_matriz_1 alloc)
target_link_libraries(alocacao_vetor_1 alloc)

install(TARGETS alocacao_matriz_1 alocacao_vetor_1 RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/bin)

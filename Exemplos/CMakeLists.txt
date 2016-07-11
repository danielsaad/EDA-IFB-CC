add_executable(lista_crud lista_crud.c)
include_directories(${CMAKE_SOURCE_DIR}/include)
target_link_libraries(lista_crud list alloc)
install(TARGETS lista_crud RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/bin)

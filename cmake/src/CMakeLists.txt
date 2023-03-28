#instruções para compilar o executável
add_executable(main main.c)
#indica quais bibliotecas devemos ligar com o executável
target_link_libraries(main geometria m)
#instala o executável na pasta bin
install (TARGETS main RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/bin)
include(ExternalProject)
ExternalProject_Add(check
  URL https://github.com/libcheck/check/archive/master.zip
  INSTALL_COMMAND ""
)

ExternalProject_Get_Property(check binary_dir)
add_library(libcheck UNKNOWN IMPORTED)
set_target_properties(libcheck PROPERTIES IMPORTED_LOCATION ${binary_dir}/src/libcheck.a)

add_dependencies(libcheck check)
include_directories(${binary_dir}/src)
include_directories(${binary_dir})
include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(teste_main
    teste_main.c
    teste_triangulo.c
    teste_quadrado.c
)

target_link_libraries(teste_main libcheck geometria m rt)

install(TARGETS teste_main RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/bin)


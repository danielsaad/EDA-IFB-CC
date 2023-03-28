CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT ("Geometria" C)

#Se a opção for DEBUG, algumas flags do compilador são setadas (-g por exemplo)
#Se a opção for RELEASE, algumas flags de otimização são setadas (-O2 -NDEBUG).
SET(CMAKE_VERBOSE_MAKEFILE on)
if(CMAKE_BUILD_TYPE MATCHES DEBUG)
	MESSAGE(STATUS "Debug mode")
	SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall")
else()
	MESSAGE(STATUS "Release mode")
	set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}  -Wall")
endif(CMAKE_BUILD_TYPE MATCHES DEBUG)

#Diretórios onde estarão nossas bibliotecas
LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/lib)

#Diretórios onde estão nossos cabeçalhos
INCLUDE_DIRECTORIES(./include)

#Compilação de nossa biblioteca
ADD_SUBDIRECTORY(lib)

#Compilação do executável
ADD_SUBDIRECTORY(src)

#Compilação dos arquivos de teste
ADD_SUBDIRECTORY(test)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT ("ED1" C)

SET(CMAKE_VERBOSE_MAKEFILE on)
if(CMAKE_BUILD_TYPE MATCHES DEBUG)
	MESSAGE(STATUS "Debug mode")
	SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g3 -Wall")
else()
	MESSAGE(STATUS "Release mode")
	add_definitions(-NDEBUG)
	set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O2 -Wall")
endif(CMAKE_BUILD_TYPE MATCHES DEBUG)


LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/lib)


MESSAGE(STATUS "Lib files: ${lib_files}")


FILE (GLOB header_files
	${CMAKE_SOURCE_DIR}/Sorting/*.h
	${CMAKE_SOURCE_DIR}/Utils/*.h
	${CMAKE_SOURCE_DIR}/Vector/*.h
	${CMAKE_SOURCE_DIR}/Stack/*.h
	${CMAKE_SOURCE_DIR}/Queue/*.h
	${CMAKE_SOURCE_DIR}/Tree/*.h
	${CMAKE_SOURCE_DIR}/List/*.h
)

foreach(header ${header_files})
	FILE(COPY ${header} DESTINATION ${CMAKE_SOURCE_DIR}/include)
endforeach(header ${header_files})


FILE (GLOB lib_srcs
	${CMAKE_SOURCE_DIR}/Sorting/*.c
	${CMAKE_SOURCE_DIR}/Utils/*.c
	${CMAKE_SOURCE_DIR}/Vector/*.c
	${CMAKE_SOURCE_DIR}/Stack/*.c
	${CMAKE_SOURCE_DIR}/Queue/*.c
	${CMAKE_SOURCE_DIR}/Tree/*.c
	${CMAKE_SOURCE_DIR}/List/*.c
)

ADD_LIBRARY(ed1 STATIC ${lib_srcs})
INSTALL(TARGETS ed1 ARCHIVE DESTINATION ${CMAKE_SOURCE_DIR}/lib)

ADD_SUBDIRECTORY(Examples)

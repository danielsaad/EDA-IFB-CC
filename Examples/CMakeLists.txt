
include_directories(${CMAKE_SOURCE_DIR}/include)
FILE( GLOB src_files  *.cpp )
foreach(src ${src_files})
	string(REPLACE ".c" "" executable ${src})
	add_executable(${executable} ${src})
	target_link_libraries(${executable} ed1)
endforeach(src ${src_files})

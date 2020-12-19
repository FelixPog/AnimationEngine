#LIBMATHS

cmake_minimum_required(VERSION 3.16)

include(${CMAKE_CURRENT_SOURCE_DIR}/CMake/CMakeLists_sources.cmake)

message(${libMaths_SOURCES})
add_library(${LIB_MATHS} STATIC ${libMaths_SOURCES})

set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${${LIB_MATHS}_SOURCES})
		
if(MSVC)
	target_compile_options(${LIB_MATHS} PRIVATE /W4 /WX)
endif()

target_include_directories(${LIB_MATHS} PUBLIC ${LIB_DIR})


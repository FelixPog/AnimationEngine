# TEST

cmake_minimum_required(VERSION 3.16)

set(TEST unitTest)

include(${CMAKE_CURRENT_SOURCE_DIR}/CMake/CMakeLists_sources.cmake)

set(TARGET_SOURCE_DIR ${PROJECT_SOURCE_DIR}/unitTest)

add_executable(${TEST} ${unitTest_SOURCES})

set(SOURCE_DIR ${TARGET_SOURCE_DIR}/source)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${${TEST}_SOURCES})

set(SCRIPT_SOURCE ${TARGET_SOURCE_DIR}/_scripts/generate_cmake_sources.sh)

set(VENDOR_DIR ${PROJECT_SOURCE_DIR}/vendor)
set(GLM_DIR ${VENDOR_DIR}/glm/)

# Link library
target_include_directories(${TEST} PRIVATE
							${SOURCE_DIR}
							${GLM_DIR})
							
target_sources(${TEST} PRIVATE ${SCRIPT_SOURCE})
target_sources(${TEST} PRIVATE ${GLM_DIR}util/glm.natvis)

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v2.13.1)

FetchContent_MakeAvailable(Catch2)

target_link_libraries(${TEST} PRIVATE 	${LIB_MATHS}
					Catch2::Catch2)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${TEST})
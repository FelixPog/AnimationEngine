#ROOT
cmake_minimum_required(VERSION 3.16)

# set a variable name for the project
set(PROJECT_NAME "LibMaths")
# create a project with a name and language CXX = C++ and C = C
project(${PROJECT_NAME} C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set project name 
set(TEST unitTest)
set(LIB_MATHS libMaths)

#Call a sub CMakeLists
add_subdirectory(${PROJECT_SOURCE_DIR}/unitTest)

#Call a sub CMakeLists
add_subdirectory(${PROJECT_SOURCE_DIR}/libMaths)

include(CheckIPOSupported)
check_ipo_supported(RESULT ipo_supported OUTPUT output)
if(ipo_supported)
    message("-- IPO is supported!")
    set_property(GLOBAL PROPERTY INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)
else()
    message(WARNING "IPO is not supported: ${output}")
endif()
#!/bin/sh

WORKING_DIR=${1:-..}
TARGET_NAME=${2:-DemoLibMaths}
SOURCES_VAR=${TARGET_NAME}_SOURCES

cd "$WORKING_DIR"
mkdir CMake

# Using sed to escape filenames with spaces in them.
BASE_SOURCES=$( find demo/ -type f -name "*.cpp" -or -name "*.h" -or -name "*.hpp" -or -name "*.inl" -or -name "*.txt" | sed 's/ /\\ /g')

SHADER_SOURCES=$( find demo/ -type f -name "*.frag" -or -name "*.geom" -or -name "*.vert" | sed 's/ /\\ /g')

echo "

set($SOURCES_VAR
	$BASE_SOURCES
	$SHADER_SOURCES
	)" > CMake/CMakeLists_demo_sources.cmake
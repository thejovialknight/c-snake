#Minimum version of CMake that can run this script
cmake_minimum_required(VERSION 3.12)

# Project name and version
project(csnake VERSION 1.0)
find_package(SDL2 REQUIRED)

# Request c++11 standard features
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

# Export compile commands for code completion
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Compile the passed source files into an executable
add_executable(csnake
	"${CMAKE_CURRENT_SOURCE_DIR}/src/color.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/game.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/game.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/input.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/main.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/platform.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/platform.h"
	)

# Reference include directory
target_include_directories(csnake PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}/include"
	"${SDL2_INCLUDE_DIRS}"
	)

target_link_libraries(csnake ${SDL2_LIBRARIES})

# Set the output directory for executables
set_target_properties(csnake
	PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

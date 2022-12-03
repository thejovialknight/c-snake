#Minimum version of CMake that can run this script
cmake_minimum_required(VERSION 3.12)

# Project name and version
project(Boilerplate VERSION 1.0)

# Request c++11 standard features
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Export compile commands for code completion
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set up configuration header file
configure_file(include/Config.h.in
	"${CMAKE_CURRENT_SOURCE_DIR}/include/Config.h")

# Compile the passed source files into an executable
add_executable(Boilerplate
	"${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/test.cpp"
	)

# Reference include directory
target_include_directories(Boilerplate PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}/include")

# Set the output directory for executables
set_target_properties(Boilerplate
	PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

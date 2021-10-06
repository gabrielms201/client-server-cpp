# CMakeList.txt : CMake project for FirstExample, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project("FirstExample")
# Add source to this project's executable.
add_executable("${PROJECT_NAME}")
# Boost Options
set(Boost_USE_STATIC_LIBS        ON) 
set(Boost_USE_MULTITHREADED      ON)
# Find Boost dependencies
find_package(Boost 1.72.0 EXACT REQUIRED COMPONENTS date_time filesystem system thread program_options regex)

# Include dir
target_include_directories("${PROJECT_NAME}" PRIVATE ${Boost_INCLUDE_DIRS})
# Link Libraries
target_link_libraries("${PROJECT_NAME}" PRIVATE
        ${Boost_LIBRARIES})

# Source Code
target_sources("${PROJECT_NAME}" PRIVATE
	"FirstExample.cpp"
	"FirstExample.h")
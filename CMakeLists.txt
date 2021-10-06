# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)
project ("Networking")

# Static Lib On
set(Boost_USE_STATIC_LIBS   ON)

# Include sub-projects.
add_subdirectory ("FirstExample")
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# LIB BOOST: 
if(WIN32)
    find_package(Boost 1.72.0 EXACT)
   if(NOT Boost_FOUND)
        message(FATAL_ERROR "Can't find Boost. Download Link: https://sourceforge.net/projects/boost/files/boost-binaries/1.72.0/boost_1_72_0-msvc-14.1-64.exe/download%22")
   endif()
endif()
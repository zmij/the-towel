#    CMakeLists.txt for the-towel project
#    The Towel project is a bunch of code for the
#    "Hitchhiker's Guide to C++ Metaprogramming" videocourse,
#    ISBN 978-1-78712-891-0
#
#    @author zmij
#    @date Jan 25, 2017

cmake_minimum_required(VERSION 2.6)

# Set library name here
set(lib_name the-towel)
string(TOUPPER ${lib_name} LIB_NAME)

set(PROJECT_PREFIX hgcm)
set(_pname ${PROJECT_PREFIX}-${lib_name})
if (PROJECT_VERSION)
    set(_pversion ${PROJECT_VERSION})
else()
    set(_pversion 0.1.0)
endif()

if (${CMAKE_VERSION} VERSION_GREATER "3.0")
    cmake_policy(SET CMP0048 NEW)
    project(${_pname} VERSION ${_pversion})
else()
    project(${_pname})
    set(PROJECT_VERSION ${_pversion})
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_definitions("-std=c++17")

set(TIP_${LIB_NAME}_LIB ${PROJECT_PREFIX}-${lib_name})

enable_testing()

# Add subdirectories here
add_subdirectory(experimental)

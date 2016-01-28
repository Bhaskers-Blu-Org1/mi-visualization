# Project name
project(MIVisualization CXX)

#  Set current version number.
set (MIVisualization_VERSION_MAJOR 1)
set (MIVisualization_VERSION_MINOR 0)
set (MIVisualization_VERSION_PATCH 0)
set (MIVisualization_VERSION ${MIVisualization_VERSION_MAJOR}.${MIVisualization_VERSION_MINOR}.${MIVisualization_VERSION_PATCH})

# CMake required version.
cmake_minimum_required(VERSION 3.2)

# Add C++11 dependency.
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -Wall")


# =======================================================================
# Find required packages
# =======================================================================
# Add path to cmake dir.
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

# Find Boost package
find_package(Boost 1.58 REQUIRED COMPONENTS system thread random)
# Try to include Boost as system directory to suppress it's warnings
include_directories(SYSTEM ${Boost_INCLUDE_DIR})

# Find OpenBLAS package
find_package( OpenBLAS REQUIRED )
include_directories(${OpenBLAS_INCLUDE_DIR})

# Find GLUT package
find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})
link_directories(${GLUT_LIBRARY_DIRS})
add_definitions(${GLUT_DEFINITIONS})
if(NOT GLUT_FOUND)
    message(ERROR " GLUT not found!")
endif(NOT GLUT_FOUND)

# Find OPENGL package
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

# Find MIC Toolchain
find_package(MIToolchain REQUIRED)
message("Found MI Toolchain libs: ${MIToolchain_LIBRARIES} ")

# Find MIC Algorithms
find_package(MIAlgorithms REQUIRED)
message("Found MI Algorithms libs: ${MIAlgorithms_LIBRARIES} ")

# =======================================================================
# RPATH settings
# =======================================================================
# use, i.e. don't skip the full RPATH for the build tree
SET(CMAKE_SKIP_BUILD_RPATH  FALSE)

# when building, use the install RPATH already
# (but later on when installing)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE) 

SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")

# add the automatically determined parts of the RPATH
# which point to directories outside the build tree to the install RPATH
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

add_subdirectory(src)

add_subdirectory(configs)

# =======================================================================
# MIVisualizationConfig.cmake preparation
# =======================================================================

# include directories
set(CMAKE_INCLUDE_DIRS_CONFIGCMAKE "${CMAKE_INSTALL_PREFIX}/include")

# lib directory

set(CMAKE_LIB_DIRS_CONFIGCMAKE "${CMAKE_INSTALL_PREFIX}/lib")

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/MIVisualizationConfig.cmake.in" "${CMAKE_BINARY_DIR}/MIVisualizationConfig.cmake" IMMEDIATE @ONLY)

install(FILES ${CMAKE_BINARY_DIR}/MIVisualizationConfig.cmake DESTINATION ${CMAKE_INSTALL_PREFIX}/share/MIVisualization/)

# =======================================================================
# CPack: binary installer generator
# =======================================================================

# CPack variables used when generating binary installer
set(CPACK_PACKAGE_NAME "MIVisualization")
set(CPACK_PACKAGE_VENDOR "MIVisualization")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "MIVisualization - Machine Intelligence Toolchain")
set(CPACK_PACKAGE_VERSION ${MIVisualization_VERSION})
set(CPACK_PACKAGE_VERSION_MAJOR ${MIVisualization_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${MIVisualization_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${MIVisualization_VERSION_PATCH})
set(CPACK_PACKAGE_INSTALL_DIRECTORY "MIVisualization")

# License file
#set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")

# Tell CPack all of the components to install. The "ALL"
# refers to the fact that this is the set of components that
# will be included when CPack is instructed to put everything
# into the binary installer (the default behavior).
set(CPACK_COMPONENTS_ALL system_utils logger configuration application)

# This must always be last!
include(CPack)

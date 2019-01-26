# Copyright (C) tkornuta, IBM Corporation 2015-2019
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# Project name
project(MIVisualization CXX C)

#  Set current version number.
set (MIVisualization_MAJOR_VERSION 1)
set (MIVisualization_MINOR_VERSION 2)
set (MIVisualization_PATCH_VERSION 2)
set (MIVisualization_VERSION ${MIVisualization_MAJOR_VERSION}.${MIVisualization_MINOR_VERSION}.${MIVisualization_PATCH_VERSION})

# CMake required version.
cmake_minimum_required(VERSION 2.8)

# Add C++11 dependency.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")


# =======================================================================
# Find required packages
# =======================================================================
# Add path to cmake dir.
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

# Find Boost package
find_package(Boost 1.54 REQUIRED COMPONENTS system thread random)
# Try to include Boost as system directory to suppress it's warnings
include_directories(SYSTEM ${Boost_INCLUDE_DIR})

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
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
elsif(NOT OPENGL_FOUND)
	include_directories(${OpenGL_INCLUDE_DIRS})
	link_directories(${OpenGL_LIBRARY_DIRS})
	add_definitions(${OpenGL_DEFINITIONS})
endif(NOT OPENGL_FOUND)

# Find Eigen package
find_package( Eigen3 REQUIRED )
include_directories( ${EIGEN3_INCLUDE_DIR} )

# Find MIC Toolchain
find_package(MIToolchain 1.1 REQUIRED)

# Find MIC Algorithms
find_package(MIAlgorithms 1.2 REQUIRED)

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

# =======================================================================
# Cmake configuration
# =======================================================================
# Create the cached variable for sstoring all library names.
set(MIVisualization_LIBRARIES "" CACHE INTERNAL "" FORCE)

# Add subdirectories.
add_subdirectory(src)

add_subdirectory(configs)

message ("-- Configured MI Visualization libraries:\n" "--   " "${MIVisualization_LIBRARIES}")

# Set include directory
set(CMAKE_INCLUDE_DIRS_CONFIGCMAKE "${CMAKE_INSTALL_PREFIX}/include")
# Set lib directory
set(CMAKE_LIB_DIRS_CONFIGCMAKE "${CMAKE_INSTALL_PREFIX}/lib")
# Set variable that will store generated libraries

# =======================================================================
# Preparation of cmake configs
# =======================================================================

# Configure *Config.cmake and *ConfigVersion.cmake
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/MIVisualizationConfig.cmake.in" "${CMAKE_BINARY_DIR}/MIVisualizationConfig.cmake" @ONLY)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/MIVisualizationConfigVersion.cmake.in" "${CMAKE_BINARY_DIR}/MIVisualizationConfigVersion.cmake" @ONLY)

# Install the *Config.cmake and *ConfigVersion.cmake
install(FILES
  "${CMAKE_BINARY_DIR}/MIVisualizationConfig.cmake"
  "${CMAKE_BINARY_DIR}/MIVisualizationConfigVersion.cmake"
  DESTINATION "${CMAKE_INSTALL_PREFIX}/share/MIVisualization/")
  

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

# Include current dir
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# =======================================================================
# Build opengl_visualization.
# =======================================================================

# =======================================================================
# Install includes related to OPENGL VISUALIZATION used by other libraries.

FILE(GLOB files *.hpp)
install(FILES ${files} DESTINATION include/opengl/visualization)

# Create shared library containing core type related classes and functions
file(GLOB opengl_visualization_src
	*.cpp
	)

add_library(opengl_visualization SHARED ${opengl_visualization_src})
target_link_libraries(opengl_visualization logger configuration application types data_utils  ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${Boost_LIBRARIES})

# Add to variable storing all libraries/targets.
set(MIVisualization_LIBRARIES ${MIVisualization_LIBRARIES} "opengl_visualization" CACHE INTERNAL "" FORCE)

# =======================================================================
# Install target libraries.
# =======================================================================

install(TARGETS opengl_visualization LIBRARY DESTINATION lib ARCHIVE DESTINATION lib RUNTIME DESTINATION bin)

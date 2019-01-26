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
# Build opengl_application.
# =======================================================================

# =======================================================================
# Install includes related to OPENGL VISUALIZATION used by other libraries.

FILE(GLOB files *.hpp)
install(FILES ${files} DESTINATION include/opengl/application)

# Create shared library containing core type related classes and functions
file(GLOB opengl_application_src
	*.cpp
	)

add_library(opengl_application SHARED ${opengl_application_src})
target_link_libraries(opengl_application 
	logger configuration application types data_utils  
	opengl_visualization
	${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${Boost_LIBRARIES}
	)

# Add to variable storing all libraries/targets.
set(MIVisualization_LIBRARIES ${MIVisualization_LIBRARIES} "opengl_application" CACHE INTERNAL "" FORCE)

# =======================================================================
# Install target libraries.
# =======================================================================

install(TARGETS opengl_application LIBRARY DESTINATION lib ARCHIVE DESTINATION lib RUNTIME DESTINATION bin)

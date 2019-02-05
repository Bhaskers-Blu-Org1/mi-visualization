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
# Build executables - grayscale image visualization test.
# =======================================================================

set(BUILD_TEST_GRAYSCALE_IMAGE_VISUALIZATION ON CACHE BOOL "Build the grayscale image visualization test application")

if(${BUILD_TEST_GRAYSCALE_IMAGE_VISUALIZATION})
	# Create executable.
	add_executable(window_grayscale_image_test window_grayscale_image_test.cpp)
	# Link it with shared libraries.
	target_link_libraries(window_grayscale_image_test 
		logger
		application
		data_io
		encoders
		configuration
		opengl_application
		opengl_visualization
		)
	
	# install test to bin directory
	install(TARGETS window_grayscale_image_test RUNTIME DESTINATION bin)
	
endif(${BUILD_TEST_GRAYSCALE_IMAGE_VISUALIZATION})

# =======================================================================
# Build executables - grayscale batch visualization test.
# =======================================================================

set(BUILD_TEST_GRAYSCALE_BATCH_VISUALIZATION ON CACHE BOOL "Build the grayscale batch visualization test application")

if(${BUILD_TEST_GRAYSCALE_BATCH_VISUALIZATION})
	# Create executable.
	add_executable(window_grayscale_batch_test window_grayscale_batch_test.cpp)
	# Link it with shared libraries.
	target_link_libraries(window_grayscale_batch_test 
		logger
		application
		data_io
		opengl_application
		opengl_visualization
		)
	
	# install test to bin directory
	install(TARGETS window_grayscale_batch_test RUNTIME DESTINATION bin)
	
endif(${BUILD_TEST_GRAYSCALE_BATCH_VISUALIZATION})

# =======================================================================
# Build executables - grayscale batch visualization test.
# =======================================================================

set(BUILD_TEST_RGB_IMAGE_VISUALIZATION ON CACHE BOOL "Build the RGB image visualization test application")

if(${BUILD_TEST_RGB_IMAGE_VISUALIZATION})
	# Create executable.
	add_executable(window_rgb_image_test window_rgb_image_test.cpp)
	# Link it with shared libraries.
	target_link_libraries(window_rgb_image_test 
		logger
		application
		data_io
		opengl_application
		opengl_visualization
		)
	
	# install test to bin directory
	install(TARGETS window_rgb_image_test RUNTIME DESTINATION bin)
	
endif(${BUILD_TEST_RGB_IMAGE_VISUALIZATION})

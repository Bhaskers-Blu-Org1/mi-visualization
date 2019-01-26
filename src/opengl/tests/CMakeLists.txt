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
		types
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
		types
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
		types
		data_io
		opengl_application
		opengl_visualization
		)
	
	# install test to bin directory
	install(TARGETS window_rgb_image_test RUNTIME DESTINATION bin)
	
endif(${BUILD_TEST_RGB_IMAGE_VISUALIZATION})

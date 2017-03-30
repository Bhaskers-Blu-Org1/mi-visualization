# Check compiler flags
include(CheckCXXCompilerFlag)

# Include current dir
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# =======================================================================
# Set compiler/linker flags.
# =======================================================================
if (WIN32)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/C/MinGW/GLUT/glut-3.7.6-bin -fopenmp -fpermissive -std=c++11")
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS}") 
else ()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
# Check, whether all necessary libraries are linked
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS}") 
endif ()

# =======================================================================
# Add CMAKE variables.
# =======================================================================

# Default length of SDR.
#set(DEFAULT_SDR_LENGTH 1024 CACHE STRING "Default length of SDR")
#add_definitions(-DDEFAULT_SDR_LENGTH=${DEFAULT_SDR_LENGTH})

# =======================================================================
# Build MI Visualization.
# =======================================================================

# =======================================================================
# Install includes related to OPENGL VISUALIZATION used by other libraries.
FILE(GLOB files opengl/application/*.hpp)
install(FILES ${files} DESTINATION include/opengl/application)

FILE(GLOB files opengl/visualization/*.hpp)
install(FILES ${files} DESTINATION include/opengl/visualization)

# Create shared library containing core type related classes and functions
file(GLOB visualization_opengl_src
	opengl/visualization/*.cpp
	opengl/application/*.cpp
	)

add_library(visualization_opengl SHARED ${visualization_opengl_src})
target_link_libraries(visualization_opengl logger configuration application types data_utils  ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${Boost_LIBRARIES})

# Add to variable storing all libraries/targets.
set(MIVisualization_LIBRARIES ${MIVisualization_LIBRARIES} "visualization_opengl" CACHE INTERNAL "" FORCE)

# =======================================================================
# Install target libraries.
# =======================================================================

install(TARGETS ${MIVisualization_LIBRARIES} LIBRARY DESTINATION lib ARCHIVE DESTINATION lib RUNTIME DESTINATION bin)

# =======================================================================
# Build executables - grayscale image visualization test.
# =======================================================================

set(BUILD_TEST_GRAYSCALE_IMAGE_VISUALIZATION ON CACHE BOOL "Build the grayscale image visualization test application")

if(${BUILD_TEST_GRAYSCALE_IMAGE_VISUALIZATION})
	# Create executable.
	add_executable(window_grayscale_image_test opengl/tests/window_grayscale_image_test.cpp)
	# Link it with shared libraries.
	target_link_libraries(window_grayscale_image_test 
		logger
		application
		types
		data_io
		encoders
		configuration
		visualization_opengl
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
	add_executable(window_grayscale_batch_test opengl/tests/window_grayscale_batch_test.cpp)
	# Link it with shared libraries.
	target_link_libraries(window_grayscale_batch_test 
		logger
		application
		types
		data_io
		encoders
		configuration
		visualization_opengl
		)
	
	# install test to bin directory
	install(TARGETS window_grayscale_batch_test RUNTIME DESTINATION bin)
	
endif(${BUILD_TEST_GRAYSCALE_BATCH_VISUALIZATION})

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

set(BUILD_TEST_IMAGE_ENCODER ON CACHE BOOL "Build the image encoder (with OpenGL-based visualization) test application")

# Default length of SDR.
set(DEFAULT_SDR_LENGTH 1024 CACHE STRING "Default length of SDR")
add_definitions(-DDEFAULT_SDR_LENGTH=${DEFAULT_SDR_LENGTH})

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

# =======================================================================
# Install target libraries.
# =======================================================================

install(TARGETS visualization_opengl LIBRARY DESTINATION lib ARCHIVE DESTINATION lib RUNTIME DESTINATION bin)

# =======================================================================
# Build executables - image encoder test.
# =======================================================================

if (WIN32)
set(VISUALIZATION_NAME "visualization_opengl.dll.a")
if(${BUILD_TEST_IMAGE_ENCODER})
	# Create exeutable.
	add_executable(image_encoder_test opengl/tests/image_encoder_test.cpp)
	# Link it with shared libraries.
	target_link_libraries(image_encoder_test 
		logger
		application
		types
		data_io
		auto_encoders
		configuration
    data_utils
    ${OPENGL_LIBRARIES} 
    ${GLUT_LIBRARY}
    "libvisualization_opengl.dll.a"
		)
	
	# install test to bin directory
	install(TARGETS image_encoder_test RUNTIME DESTINATION bin)
	
endif(${BUILD_TEST_IMAGE_ENCODER})
else ()
if(${BUILD_TEST_IMAGE_ENCODER})
	# Create exeutable.
	add_executable(image_encoder_test opengl/tests/image_encoder_test.cpp)
	# Link it with shared libraries.
	target_link_libraries(image_encoder_test 
		logger
		application
		types
		data_io
		auto_encoders
		configuration
		visualization_opengl
		)
	
	# install test to bin directory
	install(TARGETS image_encoder_test RUNTIME DESTINATION bin)
	
endif(${BUILD_TEST_IMAGE_ENCODER})
endif ()

# Check compiler flags
include(CheckCXXCompilerFlag)

# Include current dir
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# =======================================================================
# Set compiler flags.
# =======================================================================

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

# Check, whether all necessary libraries are linked
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl") 

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
target_link_libraries(visualization_opengl logger configuration application core_types data_utils  ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})


# =======================================================================
# Install target libraries.
# =======================================================================

install(TARGETS visualization_opengl LIBRARY DESTINATION lib)

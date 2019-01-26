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

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
target_link_libraries(opengl_application logger configuration application types data_utils  ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${Boost_LIBRARIES})

# Add to variable storing all libraries/targets.
set(MIVisualization_LIBRARIES ${MIVisualization_LIBRARIES} "opengl_application" CACHE INTERNAL "" FORCE)

# =======================================================================
# Install target libraries.
# =======================================================================

install(TARGETS opengl_application LIBRARY DESTINATION lib ARCHIVE DESTINATION lib RUNTIME DESTINATION bin)

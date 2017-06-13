/*!
 * \file Window.cpp
 * \brief Definition of glWindow methods.
 * \author tkornuta
 * \date Nov 18, 2015
 */

#include <opengl/visualization/Window.hpp>
#include <opengl/visualization/WindowManager.hpp>

namespace mic {
namespace opengl {
namespace visualization {

Window::Window(std::string name_, unsigned int position_x_, unsigned int position_y_, unsigned int width_, unsigned int height_) :
		name(name_), position_x(position_x_), position_y(position_y_), width(width_), height(height_)
{
	// Initialize window and display modes.
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(position_x, position_y);

    // Create window.
    id = glutCreateWindow(name.c_str());

    // Note: glutSetOption is only available with freeglut
    // glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

    // Register main handlers.
    glutDisplayFunc(VGL_MANAGER->displayHandler);
    glutReshapeFunc(VGL_MANAGER->reshapeHandler);
    glutKeyboardFunc(VGL_MANAGER->keyboardHandler);
    glutMouseFunc(VGL_MANAGER->mouseHandler);
    
    // Set OpenGl antialiasing parameters.
    glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
#ifndef _WIN32 // glBlendColor NOT SUPPORTED on windows GLUT
	glBlendColor(1.0f, 1.0f, 1.0f, 0.6f);
	glDisable(GL_MULTISAMPLE);
#endif  

	// Set fullscreen mode to off.
	fullscreen_mode = false;

	// Register default key handlers.
	REGISTER_KEY_HANDLER('f', "f - toggles fullscreen on/off", &Window::keyhandlerFullscreen);

	// Register window!
	VGL_MANAGER->registerWindow(this);
}

Window::~Window() {
	// TODO Auto-generated destructor stub
}


unsigned int Window::getId() const {
	return id;
}

std::string Window::getName() const {
	return name;
}

void Window::reshapeHandler(int width_, int height_){
//	printf("Window::reshapeHandler handler of %d window!\n", glutGetWindow());

	// Remember new width and height.
	height = height_;
	width = width_;

	// Change window size.
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Set the coordinate system, with the origin in the top left.
    gluOrtho2D(0, width, height, 0);
    glMatrixMode(GL_MODELVIEW);
}


void Window::keyhandlerFullscreen(void) {
	if (!fullscreen_mode) {
		// Remember window size.
		previous_height = height;
		previous_width = width;
		// Read current window position.
		position_x = glutGet((GLenum)GLUT_WINDOW_X);
		position_y = glutGet((GLenum)GLUT_WINDOW_Y);
		// Enter full screen.
		glutFullScreen();
	} else if (fullscreen_mode){
		// Restore previous window size.
		height = previous_height;
		width = previous_width;
		// Resize window.
		glutReshapeWindow(width, height);
		// Place it in the previous position.
		glutPositionWindow(position_x, position_y);
	}//: if
	fullscreen_mode = !fullscreen_mode;
}


} /* namespace visualization */
} /* namespace opengl */
} /* namespace mic */

/*!
 * \file WindowImage2D.cpp
 * \brief Contains declaration of the WindowImage2D class methods.
 * \author tkornuta
 * \date Nov 19, 2015
 */

#include <opengl/visualization/WindowImage2D.hpp>
#include <opengl/visualization/WindowManager.hpp>

#include <application/ApplicationState.hpp>

namespace mic {
namespace opengl {
namespace visualization {



WindowImage2D::WindowImage2D(std::string name_, unsigned int height_, unsigned int width_, unsigned int position_x_, unsigned int position_y_) :
	Window(name_, height_, width_, position_x_, position_y_)
{
	// NULL pointer.
	displayed_image = nullptr;
}


WindowImage2D::~WindowImage2D() {
	// TODO Auto-generated destructor stub
}


void WindowImage2D::displayHandler(void){
	LOG(LTRACE) << "WindowImage2D::Display handler of window " << glutGetWindow();
	// Enter critical section.
//	APP_DATA_SYNCHRONIZATION_SCOPED_LOCK();

	// Clear buffer.
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw image.
	if (displayed_image != nullptr){
		display_image(displayed_image.get(), width, height);
		draw_grid(0.5f, 0.3f, 0.3f, 0.3f, displayed_image.get()->width, displayed_image.get()->height);
	}

    // Swap buffers.
	glutSwapBuffers();

	// End of critical section.
}

void WindowImage2D::setImagePointer(image_ptr_t displayed_image_) {
	// Enter critical section.
	APP_DATA_SYNCHRONIZATION_SCOPED_LOCK();

    displayed_image = displayed_image_;
	// End of critical section.
}



} /* namespace visualization */
} /* namespace opengl */
} /* namespace mic */

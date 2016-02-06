/*!
 * \file WindowMatrix2D.cpp
 * \brief 
 * \author tkornut
 * \date Dec 22, 2015
 */

#include <opengl/visualization/WindowMatrix2D.hpp>
#include <opengl/visualization/WindowManager.hpp>

namespace mic {
namespace opengl {
namespace visualization {

WindowMatrix2D::WindowMatrix2D(std::string name_, unsigned int height_, unsigned int width_, unsigned int position_x_, unsigned int position_y_) :
	Window(name_, height_, width_, position_x_, position_y_)
{
	// NULL pointer.
	displayed_matrix = nullptr;
}


WindowMatrix2D::~WindowMatrix2D() {
	// TODO Auto-generated destructor stub
}


void WindowMatrix2D::displayHandler(void){
	LOG(LTRACE) << "WindowMatrix2D::Display handler of window " << glutGetWindow();
	// Enter critical section.
	APP_DATA_SYNCHRONIZATION_SCOPED_LOCK();

	// Clear buffer.
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw matrix 2d.
	if (displayed_matrix != nullptr){

		// Compute scale.
    	float scale_x = (float)glutGet(GLUT_WINDOW_HEIGHT)/(float)(displayed_matrix->rows());
    	float scale_y = (float)glutGet(GLUT_WINDOW_WIDTH)/(float)(displayed_matrix->cols());

    	// Iterate through matrix elements.
		for (unsigned y = 0; y < displayed_matrix->rows(); y++) {
			for (unsigned x = 0; x < displayed_matrix->cols(); x++) {
				// Get value.
				float val = (*displayed_matrix)(y, x);

				// Draw rectangle.
		        draw_filled_rectangle(float(x) * scale_y, float(y) * scale_x, scale_x, scale_y,
		        (float)val,
		        (float)val,
		        (float)val,
		        (float)1.0f);

			}//: for
		}//: for

		draw_grid(0.5f, 0.3f, 0.3f, 0.3f, displayed_matrix->cols(), displayed_matrix->rows());
	}//: if !null

	// Swap buffers.
	glutSwapBuffers();

	// End of critical section.
}

void WindowMatrix2D::setMatrixPointer(matrixd_ptr_t displayed_matrix_) {
	// Enter critical section.
	APP_DATA_SYNCHRONIZATION_SCOPED_LOCK();

	displayed_matrix = displayed_matrix_;
	// End of critical section.
}

} /* namespace visualization */
} /* namespace opengl */
} /* namespace mic */

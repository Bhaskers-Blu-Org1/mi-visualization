/*!
 * @file: WindowProbability.cpp
 * @Author: Tomasz Kornuta <tkornut@us.ibm.com>
 * @Date:   28-03-2017
 *
 * Copyright (c) 2017, Tomasz Kornuta, IBM Corporation. All rights reserved.
 *
 */

#include <opengl/visualization/WindowProbability.hpp>
#include <opengl/visualization/WindowManager.hpp>

namespace mic {
namespace opengl {
namespace visualization {


WindowProbability::WindowProbability(std::string name_,
		unsigned int position_x_, unsigned int position_y_,
		unsigned int width_ , unsigned int height_) :
	Window(name_, position_x_, position_y_, width_, height_)
{
	// NULL pointer.
	displayed_matrix1 = nullptr;
	displayed_matrix2 = nullptr;
}


WindowProbability::~WindowProbability() {
	// TODO Auto-generated destructor stub
}


void WindowProbability::displayHandler(void){
	LOG(LTRACE) << "WindowProbability::Display handler of window " << glutGetWindow();
	// Enter critical section.
	APP_DATA_SYNCHRONIZATION_SCOPED_LOCK();

	// Clear buffer.
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw chart boundary.
	glLineWidth(1.0f);
	draw_rectangle(1.0f, 1.0f, (float)glutGet(GLUT_WINDOW_HEIGHT)*0.9, (float)glutGet(GLUT_WINDOW_WIDTH)-2.0f, 0.7f, 0.7f, 0.7f, 1.0f);

	if (displayed_matrix1 != nullptr){
		// Assume vector (1d matrix).
		assert(displayed_matrix1->cols() == 1);

/*		std::cout << "Drawing matrix: r =" << displayed_matrix1->rows() << " c=" << displayed_matrix1->cols() << std::endl;
		std::cout << displayed_matrix1->transpose() << std::endl;*/
		size_t elements = displayed_matrix1->rows();
    	float* data_ptr = displayed_matrix1->data();

		// Compute scale.
    	float scale_x = (float)glutGet(GLUT_WINDOW_WIDTH)/(float)(elements);
    	float scale_y = (float)glutGet(GLUT_WINDOW_HEIGHT) * 0.9 - 1.0f;

    	// Iterate through elements of the vector.
		for (size_t x = 0; x < elements; x++) {
			// Get value.
			float val = data_ptr[x];

			glColor4f(1.0, 0.5, 0.5, 1.0);
			glLineWidth(5.0);
			glBegin(GL_LINES);
			  glVertex2i(((float) (x+0.4) * scale_x), scale_y);
			  glVertex2i(((float) (x+0.4) * scale_x), (float) (1.0-val) * scale_y);
			glEnd();

		}//: for

		// Print labels.
		scale_y = (float)glutGet(GLUT_WINDOW_HEIGHT) * 0.97;
		for (size_t x = 0; x < elements; x++) {
			char* str_value = (char*)std::to_string(x).c_str();
			draw_text((float) (x+0.45) * scale_x, scale_y, str_value, 1.0f, 1.0f, 1.0f, 1.0f, GLUT_BITMAP_HELVETICA_10);
		}//: for

	}//: if !null

	if (displayed_matrix2 != nullptr){
		// Assume vector (1d matrix).
		assert(displayed_matrix2->cols() == 1);

		size_t elements = displayed_matrix2->rows();
    	float* data_ptr = displayed_matrix2->data();

		// Compute scale.
    	float scale_x = (float)glutGet(GLUT_WINDOW_WIDTH)/(float)(elements);
    	float scale_y = (float)glutGet(GLUT_WINDOW_HEIGHT) * 0.9 - 1.0f;

    	// Iterate through elements of the vector.
		for (size_t x = 0; x < elements; x++) {
			// Get value.
			float val = data_ptr[x];

			glColor4f(0.5, 1.0, 0.5, 1.0);
			glLineWidth(5.0);
			glBegin(GL_LINES);
			  glVertex2i(((float) (x+0.6) * scale_x), scale_y);
			  glVertex2i(((float) (x+0.6) * scale_x), (float) (1.0-val) * scale_y);
			glEnd();

		}//: for

		// Print labels.
		scale_y = (float)glutGet(GLUT_WINDOW_HEIGHT) * 0.97;
		for (size_t x = 0; x < elements; x++) {
			char* str_value = (char*)std::to_string(x).c_str();
			draw_text((float) (x+0.45) * scale_x, scale_y, str_value, 1.0f, 1.0f, 1.0f, 1.0f, GLUT_BITMAP_HELVETICA_10);
		}//: for

	}//: if !null

	// Swap buffers.
	glutSwapBuffers();

	// End of critical section.
}

void WindowProbability::setMatrixPointer1(mic::types::MatrixXfPtr displayed_matrix_) {
	// Enter critical section.
	APP_DATA_SYNCHRONIZATION_SCOPED_LOCK();

	displayed_matrix1 = displayed_matrix_;
	// End of critical section.
}

void WindowProbability::setMatrixPointer2(mic::types::MatrixXfPtr displayed_matrix_) {
	// Enter critical section.
	APP_DATA_SYNCHRONIZATION_SCOPED_LOCK();

	displayed_matrix2 = displayed_matrix_;
	// End of critical section.
}

} /* namespace visualization */
} /* namespace opengl */
} /* namespace mic */

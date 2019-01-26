/*!
 * Copyright (C) tkornuta, IBM Corporation 2015-2019
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
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

WindowMatrix2D::WindowMatrix2D(std::string name_,
		unsigned int position_x_, unsigned int position_y_,
		unsigned int width_ , unsigned int height_) :
	Window(name_, position_x_, position_y_, width_, height_)
{
	// NULL pointer.
	displayed_matrix_ptr = nullptr;
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
	if (displayed_matrix_ptr != nullptr){
		// Set temporal variables.
		size_t rows = displayed_matrix_ptr->rows();
		size_t cols = displayed_matrix_ptr->cols();
    	float* data_ptr = displayed_matrix_ptr->data();

		// Compute scale.
    	float scale_x = (float)glutGet(GLUT_WINDOW_HEIGHT)/(float)(rows);
    	float scale_y = (float)glutGet(GLUT_WINDOW_WIDTH)/(float)(cols);

    	// Iterate through matrix elements.
		for (size_t y = 0; y < rows; y++) {
			for (size_t x = 0; x < cols; x++) {
				// Get value - REVERSED! as Eigen::Matrix by default is column-major!!
				float val = data_ptr[x*rows + y];

				// Draw rectangle.
		        draw_filled_rectangle(float(x) * scale_y, float(y) * scale_x, scale_x, scale_y,
		        (float)val,
		        (float)val,
		        (float)val,
		        (float)1.0f);

			}//: for
		}//: for

		draw_grid(0.5f, 0.3f, 0.3f, 0.3f, cols, rows);
	}//: if !null

	// Swap buffers.
	glutSwapBuffers();

	// End of critical section.
}



void WindowMatrix2D::setMatrixSynchronized(mic::types::MatrixXf & displayed_matrix_) {
	// Enter critical section.
	APP_DATA_SYNCHRONIZATION_SCOPED_LOCK();

	// Initialize the pointer.
	if (displayed_matrix_ptr == nullptr) // int Rows_, int Cols_
		displayed_matrix_ptr = MAKE_MATRIX_PTR(float, displayed_matrix_);
	else
		*displayed_matrix_ptr = displayed_matrix_;
	// End of critical section.
}

void WindowMatrix2D::setMatrixUnsynchronized(mic::types::MatrixXf & displayed_matrix_) {
	// Initialize the pointer.
	if (displayed_matrix_ptr == nullptr) // int Rows_, int Cols_
		displayed_matrix_ptr = MAKE_MATRIX_PTR(float, displayed_matrix_);
	else
		*displayed_matrix_ptr = displayed_matrix_;
}



void WindowMatrix2D::setMatrixPointerSynchronized(mic::types::MatrixXfPtr displayed_matrix_ptr_) {
	// Enter critical section.
	APP_DATA_SYNCHRONIZATION_SCOPED_LOCK();

	displayed_matrix_ptr = displayed_matrix_ptr_;
	// End of critical section.
}

void WindowMatrix2D::setMatrixPointerUnsynchronized(mic::types::MatrixXfPtr displayed_matrix_ptr_) {
	displayed_matrix_ptr = displayed_matrix_ptr_;
}


} /* namespace visualization */
} /* namespace opengl */
} /* namespace mic */

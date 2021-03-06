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
 * \file WindowMNISTDigit.cpp
 * \brief 
 * \author tkornut
 * \date Jun 8, 2016
 */

#include <opengl/visualization/WindowMNISTDigit.hpp>
#include <opengl/visualization/WindowManager.hpp>

namespace mic {
namespace opengl {
namespace visualization {

WindowMNISTDigit::WindowMNISTDigit(std::string name_,
		unsigned int position_x_, unsigned int position_y_,
		unsigned int width_ , unsigned int height_) :
	Window(name_, position_x_, position_y_, width_, height_)
{
	// NULL pointer.
	displayed_digit = nullptr;
}


WindowMNISTDigit::~WindowMNISTDigit() {
	// TODO Auto-generated destructor stub
}


void WindowMNISTDigit::displayHandler(void){
	LOG(LTRACE) << "WindowMNISTDigit::Display handler of window " << glutGetWindow();

	// Enter critical section.
	APP_DATA_SYNCHRONIZATION_SCOPED_LOCK();

	// Clear buffer.
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw matrix 2d.
	if (displayed_digit != nullptr){
		// Get dimensions.
		size_t w_tensor = displayed_digit->dim(0);
		size_t h_tensor = displayed_digit->dim(1);
		//size_t d_tensor = displayed_digit->dim(2);
		size_t w_window = glutGet(GLUT_WINDOW_WIDTH);
		size_t h_window = glutGet(GLUT_WINDOW_HEIGHT);

		// Compute scales.
		float w_scale = (float) w_window / w_tensor;
		float h_scale = (float) h_window / h_tensor;
    	float scale_min = (w_scale < h_scale) ? w_scale : h_scale;

/*		std::cout<< " width_tensor= "<< w_tensor << " height_tensor= "<< h_tensor<<std::endl;
		std::cout<< " width_window= "<< w_window<< " height_window= "<< h_window <<std::endl;
		std::cout<< " w_scale= "<< w_scale << " h_scale= "<< h_scale<< std::endl;*/


    	// Iterate through maze of digits elements.
		for (size_t y = 0; y < h_tensor; y++) {
			for (size_t x = 0; x < w_tensor; x++) {

				// Get value.
				float r, g, b;
				r = g = b = (*displayed_digit)({x,y, (size_t)MNISTDigitChannels::Pixels});

				// Draw rectangle.
		        draw_filled_rectangle(float(x) * w_scale, float(y) * h_scale, h_scale, w_scale, r, g, b, (float)1.0f);

		        // Draw goal.
				if ((*displayed_digit)({x,y, (size_t)MNISTDigitChannels::Goals})) {
					// Draw circle.
					r = 0.0; g = 0.0; b = 0.0;
					draw_cross((float(x) + 0.5)* w_scale, (float(y) + 0.5)* h_scale, scale_min/4, 4.0, r, g, b, (float)1.0f);
					r = 1.0; g = 0.0; b = 0.0;
					draw_cross((float(x) + 0.5)* w_scale, (float(y) + 0.5)* h_scale, scale_min/4, 2.0, r, g, b, (float)1.0f);
				}

		        // Draw agent.
				if ((*displayed_digit)({x,y, (size_t)MNISTDigitChannels::Agent})) {
					// Draw circle.
					r = 0.0; g = 0.0; b = 0.0;
					draw_circle((float(x) + 0.5)* w_scale, (float(y) + 0.5)* h_scale, scale_min/4, 4.0, r, g, b, (float)1.0f);
					r = 1.0; g = 1.0; b = 1.0;
					draw_circle((float(x) + 0.5)* w_scale, (float(y) + 0.5)* h_scale, scale_min/4, 2.0, r, g, b, (float)1.0f);
				}

			}//: for
		}//: for

		// Draw grid on top.
		draw_grid(0.5f, 0.3f, 0.3f, 0.3f, w_tensor, h_tensor);

		// Draw saccadic path.
		if ((saccadic_path != nullptr) && (saccadic_path->size() > 1)){

			draw_circle((float((*saccadic_path)[0].x) + 0.5)* w_scale, (float((*saccadic_path)[0].y) + 0.5)* h_scale, 2.0, 1.0, 1.0, 1.0, 1.0, 1.0);

			// White contour.
			for(size_t i=1; i <saccadic_path->size(); i++) {
				// Get points.
				Position2D prev = (*saccadic_path)[i-1];
				Position2D next = (*saccadic_path)[i];

				// Draw line between those two.
				glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
				glLineWidth(4.0);
				glBegin(GL_LINES);
				glVertex2i((float(prev.x) + 0.5) * w_scale, (float(prev.y) + 0.5) * h_scale);
				glVertex2i((float(next.x) + 0.5) * w_scale, (float(next.y) + 0.5) * h_scale);
				glEnd();

				//if (i != saccadic_path->size()-1)
				draw_circle((float(next.x) + 0.5)* w_scale, (float(next.y) + 0.5)* h_scale, 2.0, 1.0, 1.0, 1.0, 1.0, 1.0);

			}//: for

			// Green path.
			glLineWidth(2.0);
			glBegin(GL_LINES);
			for(size_t i=1; i <saccadic_path->size(); i++) {
				// Get points.
				Position2D prev = (*saccadic_path)[i-1];
				Position2D next = (*saccadic_path)[i];

				// Draw line between those two.
				float g = 0.1 + 0.9*((float)i/saccadic_path->size());
				glColor4f(0.0f, g, 0.0f, 1.0f);
				glVertex2i((float(prev.x) + 0.5) * w_scale, (float(prev.y) + 0.5) * h_scale);
				glVertex2i((float(next.x) + 0.5) * w_scale, (float(next.y) + 0.5) * h_scale);

				//if (i != saccadic_path->size()-1)
				//	draw_circle((float(next.x) + 0.5)* w_scale, (float(next.y) + 0.5)* h_scale, 1.0, 1.0, 0.0, g, 0.0, 1.0);

			}//: for
			glEnd();

		}//: if !null
	}//: if !null


	// Swap buffers.
	glutSwapBuffers();

	// End of critical section.
}

void WindowMNISTDigit::setDigitPointer(mic::types::TensorXfPtr displayed_digit_) {
	// Enter critical section.
	APP_DATA_SYNCHRONIZATION_SCOPED_LOCK();

	(displayed_digit) = (displayed_digit_);
	// End of critical section.
}

void WindowMNISTDigit::setPathPointer(std::shared_ptr<std::vector <mic::types::Position2D> > saccadic_path_) {
	// Enter critical section.
	APP_DATA_SYNCHRONIZATION_SCOPED_LOCK();

	saccadic_path = saccadic_path_;
	// End of critical section.
}

} /* namespace visualization */
} /* namespace opengl */
} /* namespace mic */

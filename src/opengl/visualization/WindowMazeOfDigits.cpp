/*!
 * \file WindowMazeOfDigits.cpp
 * \brief 
 * \author tkornut
 * \date May 9, 2016
 */


#include <opengl/visualization/WindowMazeOfDigits.hpp>
#include <opengl/visualization/WindowManager.hpp>

namespace mic {
namespace opengl {
namespace visualization {

WindowMazeOfDigits::WindowMazeOfDigits(std::string name_, unsigned int height_, unsigned int width_, unsigned int position_x_, unsigned int position_y_) :
	Window(name_, height_, width_, position_x_, position_y_)
{
	// NULL pointer.
	displayed_maze = nullptr;
}


WindowMazeOfDigits::~WindowMazeOfDigits() {
	// TODO Auto-generated destructor stub
}


void WindowMazeOfDigits::displayHandler(void){
	LOG(LTRACE) << "WindowMazeOfDigits::Display handler of window " << glutGetWindow();

	// Enter critical section.
	APP_DATA_SYNCHRONIZATION_SCOPED_LOCK();

	// Clear buffer.
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw matrix 2d.
	if (displayed_maze != nullptr){
		// Get dimensions.
		size_t w_tensor = displayed_maze->dim(0);
		size_t h_tensor = displayed_maze->dim(1);
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

				// Check cell.
				if ((*displayed_maze)({x,y, (size_t)MazeOfDigitsChannels::Walls})) {
					r = 0.0; g = 0.0; b = 0.0;
				} else {
					unsigned short digit = (*displayed_maze)({x,y, (size_t)MazeOfDigitsChannels::Digits});
					switch(digit){
					case 0: r = 0.0; g = 0.0; b = 0.3; break;
					case 1: r = 0.0; g = 0.0; b = 0.6; break;
					case 2: r = 0.0; g = 0.0; b = 0.9; break;
					case 3: r = 0.0; g = 0.3; b = 1.0; break;
					case 4: r = 0.0; g = 0.6; b = 0.6; break;
					case 5: r = 0.0; g = 0.9; b = 0.3; break;
					case 6: r = 1.0; g = 0.75; b = 0.0; break;
					case 7: r = 1.0; g = 0.5; b = 0.0; break;
					case 8: r = 1.0; g = 0.25; b = 0.0; break;
					case 9: r = 1.0; g = 1.0; b = 1.0; break;
					}
				}//: else

				// Draw rectangle.
		        draw_filled_rectangle(float(x) * w_scale, float(y) * h_scale, h_scale, w_scale, r,g, b, (float)1.0f);

		        // Check agent position.
				if ((*displayed_maze)({x,y, (size_t)MazeOfDigitsChannels::Agent})) {
					// Draw circle.
					r = 0.0; g = 0.0; b = 0.0;
					draw_circle((float(x) + 0.5)* w_scale, (float(y) + 0.5)* h_scale, scale_min/4, 4.0, r, g, b, (float)1.0f);
					r = 1.0; g = 1.0; b = 1.0;
					draw_circle((float(x) + 0.5)* w_scale, (float(y) + 0.5)* h_scale, scale_min/4, 2.0, r, g, b, (float)1.0f);
				}


			}//: for
		}//: for

		draw_grid(0.5f, 0.3f, 0.3f, 0.3f, w_tensor, h_tensor);
	}//: if !null

	// Swap buffers.
	glutSwapBuffers();

	// End of critical section.
}

void WindowMazeOfDigits::setMazePointer(mic::types::TensorXfPtr displayed_maze_) {
	// Enter critical section.
	APP_DATA_SYNCHRONIZATION_SCOPED_LOCK();

	(displayed_maze) = (displayed_maze_);
	// End of critical section.
}

} /* namespace visualization */
} /* namespace opengl */
} /* namespace mic */

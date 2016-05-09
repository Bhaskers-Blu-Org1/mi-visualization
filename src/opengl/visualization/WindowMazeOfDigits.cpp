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
		// Set temporal variables.
		int cols = displayed_maze->dim(0);
		int rows = displayed_maze->dim(1);
    	//float* data_ptr = displayed_maze->data();

		// Compute scale.
    	float scale_x = (float)glutGet(GLUT_WINDOW_HEIGHT)/(float)(cols);
    	float scale_y = (float)glutGet(GLUT_WINDOW_WIDTH)/(float)(rows);

/*		// Check object occupancy.
		if ((*grid_)({x,y, (size_t)MazeOfDigitsChannels::Agent}) != 0) {
			// Display agent.
			s += "<A>";
		} else if ((*grid_)({x,y, (size_t)MazeOfDigitsChannels::Walls}) != 0) {
			// Display wall.
			s += " # ";
		} else
			// Display pit.
			s +=  " " + std::to_string((unsigned short)(*grid_)({x,y, (size_t)MazeOfDigitsChannels::Digits})) + " ";
*/

    	// Iterate through maze of ditigs elements.
		for (size_t y = 0; y < rows; y++) {
			for (size_t x = 0; x < cols; x++) {
				// Get value.
//				float val = data_ptr[x*rows + y ] * 25;

//				LOG(LERROR) << " x= " << x << " y= " << y << " cols= " << cols << " rows= " << rows;
//				LOG(LERROR) << " dims(0)= " << displayed_maze->dim(0) << " dims(1)= " << displayed_maze->dim(1);

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
					case 9: r = 1.0; g = 0.0; b = 0.0; break;
					}
				}//: else

				// Draw rectangle.
		        draw_filled_rectangle(float(x) * scale_y, float(y) * scale_x, scale_x, scale_y, r,g, b, (float)1.0f);

		        // Check agent position.
				if ((*displayed_maze)({x,y, (size_t)MazeOfDigitsChannels::Agent})) {
					r = 0.0; g = 0.0; b = 0.0;
					draw_circle((float(x) + 0.5)* scale_y, (float(y) + 0.5)* scale_x, scale_x/4, 4.0, r, g, b, (float)1.0f);
					r = 1.0; g = 1.0; b = 1.0;
					draw_circle((float(x) + 0.5)* scale_y, (float(y) + 0.5)* scale_x, scale_x/4, 2.0, r, g, b, (float)1.0f);
				}


			}//: for
		}//: for

		draw_grid(0.5f, 0.3f, 0.3f, 0.3f, cols, rows);
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

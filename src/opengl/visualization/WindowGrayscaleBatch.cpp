/*!
 * @file: WindowGrayscaleBatch.cpp
 * @Author: Tomasz Kornuta <tkornut@us.ibm.com>
 * @Date:   30-03-2017
 *
 * Copyright (c) 2017, Tomasz Kornuta, IBM Corporation. All rights reserved.
 *
 */


#include <opengl/visualization/WindowGrayscaleBatch.hpp>
#include <opengl/visualization/WindowManager.hpp>

#include <cmath>

namespace mic {
namespace opengl {
namespace visualization {

WindowGrayscaleBatch::WindowGrayscaleBatch(std::string name_, unsigned int height_, unsigned int width_, unsigned int position_x_, unsigned int position_y_) :
	Window(name_, height_, width_, position_x_, position_y_)
{
	// NULL batch.
	batch_ptr = nullptr;
}


WindowGrayscaleBatch::~WindowGrayscaleBatch() {
	// TODO Auto-generated destructor stub
}


void WindowGrayscaleBatch::displayHandler(void){
	LOG(LTRACE) << "WindowGrayscaleBatch::Display handler of window " << glutGetWindow();
	// Enter critical section.
	APP_DATA_SYNCHRONIZATION_SCOPED_LOCK();

	// Clear buffer.
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw batch - vector of 2d matrices.
	if ((batch_ptr != nullptr) && (batch_ptr->size() > 0)){
		// Calculate batch "dimensions".
		size_t batch_width = ceil(sqrt(batch_ptr->size()));
		size_t batch_height = ceil((float)batch_ptr->size()/batch_width);

		// Get vector.
		auto batch_data = batch_ptr->data();

		// Get image sizes.
		size_t rows = batch_data[0]->rows();
		size_t cols = batch_data[0]->cols();

		// Set opengl scale related variables.
    	float scale_x = (float)glutGet(GLUT_WINDOW_WIDTH)/(float)(cols * batch_width);
    	float scale_y = (float)glutGet(GLUT_WINDOW_HEIGHT)/(float)(rows * batch_height);

    	// Iterate through batch elements.
		for (size_t by=0; by < batch_height; by++)
			for (size_t bx=0; bx < batch_width; bx++) {
				// Check if we do not excess size.
				if ((by*batch_width + bx) >= batch_data.size())
					break;
				// Get pointer to given image.
				float* data_ptr = batch_data[by*batch_width + bx]->data();

			   	// Iterate through matrix elements.
				for (size_t y = 0; y < rows; y++) {
					for (size_t x = 0; x < cols; x++) {
						// Get value - REVERSED! as Eigen::Matrix by default is column-major!!
						float val = data_ptr[x*rows + y];

						// Draw rectangle - (x, y, height, width, color)!!
						draw_filled_rectangle(float(bx*cols+x) * scale_x, float(by*rows+y) * scale_y, scale_y, scale_x,
						(float)val,
						(float)val,
						(float)val,
						(float)1.0f);

					}//: for
				}//: for

			}//: for images in batch

		// Draw grids dividing the cells and batch samples.
		draw_grid(0.5f, 0.3f, 0.3f, 0.3f, batch_width * cols, batch_height * rows);
		draw_grid(0.8f, 0.3f, 0.3f, 0.3f, batch_width, batch_height);
	}//: if !null

	// Swap buffers.
	glutSwapBuffers();

	// End of critical section.
}


void WindowGrayscaleBatch::setBatchSynchronized(mic::types::MNISTBatch & batch_) {
	// Enter critical section.
	APP_DATA_SYNCHRONIZATION_SCOPED_LOCK();

	// Initialize the pointer if required.
	if (batch_ptr == nullptr)
		batch_ptr = std::make_shared<mic::types::MNISTBatch >(batch_);
	else
		*batch_ptr = batch_;

	// End of critical section.
}

void WindowGrayscaleBatch::setBatchUnsynchronized(mic::types::MNISTBatch & batch_) {
	// Initialize the pointer if required.
	if (batch_ptr == nullptr)
		batch_ptr = std::make_shared<mic::types::MNISTBatch >(batch_);
	else
		*batch_ptr = batch_;
}


void WindowGrayscaleBatch::setBatchPtrSynchronized(mic::types::MNISTBatchPtr batch_ptr_) {
	// Enter critical section.
	APP_DATA_SYNCHRONIZATION_SCOPED_LOCK();

	batch_ptr = batch_ptr_;
	// End of critical section.
}

void WindowGrayscaleBatch::setBatchPtrUnsynchronized(mic::types::MNISTBatchPtr batch_ptr_) {
	batch_ptr = batch_ptr_;
}

} /* namespace visualization */
} /* namespace opengl */
} /* namespace mic */

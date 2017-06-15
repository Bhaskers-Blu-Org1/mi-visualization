/*!
 * @file: WindowRGBTensor.hpp
 * @Author: Tomasz Kornuta <tkornut@us.ibm.com>
 * @Date:   14-06-2017
 *
 * Copyright (c) 2017, Tomasz Kornuta, IBM Corporation. All rights reserved.
 *
 */

#ifndef WINDOWGRAYSCALEBATCH_H_
#define WINDOWGRAYSCALEBATCH_H_

#include <opengl/visualization/Window.hpp>
#include <opengl/visualization/WindowManager.hpp>

// Dependencies on core types.
#include <types/TensorTypes.hpp>

namespace mic {
namespace opengl {
namespace visualization {

/*!
 * Class containing enumerators used in windows displaying RGB images (tensors).
 */
class RGB {
public:

	/*!
	 * Display mode.
	 */
	enum ChannelDisplay {
		Chan_Separate, //< Displays separate channels.
		Chan_RGB //< Displays RGB image.
	};

	/*!
	 * Normalization of the RGB (three channel) images.
	 */
	enum Normalization {
		Norm_None, //< Displays original image(s), without any normalization (negative values simply won't be visible).
		Norm_Positive //< Displays image(s) normalized to <0,1>.
	};

	/*!
	 * Types of grids to be displayed.
	 */
	enum Grid {
		Grid_None, //< No grid
		Grid_Sample, //< Displays only grid dividing sample cells.
		Grid_Batch, //< Displays grid dividing samples.
		Grid_Both //< Displays both sample and batch grids.
	};


};

/*!
 * \brief OpenGL-based window responsible for displaying RGB (three channel) batch in a window.
 * \author tkornuta
 * \@tparam eT Precission (float/double) (DEFAULT=float).
 */
template <typename eT=float>
class WindowRGBTensor: public Window, public RGB {
public:

	/*!
	 * Constructor. Sets window position (x,y), size (width, height) and display properties (normalization, grid).
	 */
	WindowRGBTensor(std::string name_ = "WindowRGBTensor",
			ChannelDisplay channel_display_ = Chan_Separate, Normalization normalization_ = Norm_None, Grid grid_ = Grid_Batch,
			unsigned int position_x_ = 0, unsigned int position_y_ = 0,
			unsigned int width_ = 512,unsigned int height_ = 512,
			bool draw_batch_grid_ = true, bool draw_sample_grid_ = false) :
		Window(name_, position_x_, position_y_, width_, height_),
		channel_display(channel_display_),
		normalization(normalization_ ),
		grid(grid_)
	{

	}

	/*!
	 * Virtual destructor - empty.
	 */
	virtual ~WindowRGBTensor() { }


	/*!
	 * Refreshes the content of the window.
	 */
	void displayHandler(void){
		LOG(LTRACE) << "WindowRGBTensor::Display handler of window " << glutGetWindow();
		// Enter critical section.
		APP_DATA_SYNCHRONIZATION_SCOPED_LOCK();

		// Clear buffer.
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Draw batch - vector of 2d matrices.
		if (batch_data.size() > 0){
			// Calculate batch "dimensions".
			size_t batch_width = ceil(sqrt(batch_data.size()));
			size_t batch_height = ceil((eT)batch_data.size()/batch_width);

			// Get vector.
			//auto batch_data = batch_ptr->data();

			// Get image sizes.
			size_t rows = batch_data[0]->dim(0);
			size_t cols = batch_data[0]->dim(1);

			// Set opengl scale related variables.
	    	eT scale_x = (eT)glutGet(GLUT_WINDOW_WIDTH)/(eT)(cols * batch_width);
	    	eT scale_y = (eT)glutGet(GLUT_WINDOW_HEIGHT)/(eT)(rows * batch_height);

	    	// Iterate through batch elements.
			for (size_t by=0; by < batch_height; by++)
				for (size_t bx=0; bx < batch_width; bx++) {
					// Check if we do not excess size.
					if ((by*batch_width + bx) >= batch_data.size())
						break;
					// Get pointer to a given image.
					eT* data_ptr = batch_data[by*batch_width + bx]->data();

					//eT ultimate_max= (max > -min) ? max : -min;

				   	// Iterate through matrix elements.
					for (size_t y = 0; y < rows; y++) {
						for (size_t x = 0; x < cols; x++) {
							// Get value - REVERSED! as Eigen::Matrix by default is column-major!!
							//eT val = data_ptr[x*rows + y];
							eT red = data_ptr[x*rows + y]; // first channel
							eT green = data_ptr[x*rows + y + (rows*cols)];
							eT blue = data_ptr[x*rows + y + 2*(rows*cols)];

							// Draw rectangle - (x, y, height, width, color)!!
							draw_filled_rectangle(eT(bx*cols+x) * scale_x, eT(by*rows+y) * scale_y, scale_y, scale_x,
							(eT)red,
							(eT)green,
							(eT)blue,
							(eT)1.0f);

						}//: for
					}//: for

				}//: for images in batch

			// Draw grids dividing the cells and batch samples.
			switch(grid) {
			case Grid::Grid_Sample :
				draw_grid(0.3f, 0.8f, 0.3f, 0.3f, batch_width * cols, batch_height * rows);
				break;
			case Grid::Grid_Batch:
				draw_grid(0.8f, 0.3f, 0.3f, 0.4f, batch_width, batch_height, 4.0);
				break;
			case Grid::Grid_Both:
				draw_grid(0.3f, 0.8f, 0.3f, 0.3f, batch_width * cols, batch_height * rows);
				draw_grid(0.8f, 0.3f, 0.3f, 0.4f, batch_width, batch_height, 4.0);
				break;
			// None is default.
			case Grid::Grid_None:
			default:
				break;
			}//: switch
		}//: if !null

		// Swap buffers.
		glutSwapBuffers();

		// End of critical section.
	}

	/*!
	 * Sets pointer to displayed sample.
	 * @param sample_ptr_ Pointer to a sample (3D tensor) to be displayed.
	 */
	void setSampleSynchronized(mic::types::TensorPtr<eT> sample_ptr_) {
		// Enter critical section.
		APP_DATA_SYNCHRONIZATION_SCOPED_LOCK();

		// Clear - just in case.
		batch_data.clear();
		// Add sample.
		batch_data.push_back(sample_ptr_);

		// End of critical section.
	}

	/*!
	 * Sets pointer to displayed sample. Unsynchronized i.e. must be used inside of manually synchronized section.
	 * @param sample_ptr_ Pointer to a sample (3D tensor) to be displayed.
	 */
	void setSampleUnsynchronized(mic::types::TensorPtr<eT> sample_ptr_) {
		// Clear - just in case.
		batch_data.clear();
		// Add sample.
		batch_data.push_back(sample_ptr_);
	}

	/*!
	 * Sets displayed batch.
	 * @param batch_data_ Pointer to a batch (of pointers to 3D tensors) to be displayed.
	 */
	void setBatchSynchronized(std::vector <mic::types::TensorPtr<eT> >  & batch_data_) {
		// Enter critical section.
		APP_DATA_SYNCHRONIZATION_SCOPED_LOCK();

		batch_data = batch_data_;

		// End of critical section.
	}

	/*!
	 * Sets displayed batch. Unsynchronized i.e. must be used inside of manually synchronized section.
	 * @param batch_data_ Pointer to a batch  (of pointers to 3D tensors) to be displayed.
	 */
	void setBatchUnsynchronized(std::vector <mic::types::TensorPtr<eT> > & batch_data_) {
		batch_data = batch_data_;
	}


private:

	/*!
	 * Pointer to displayed batch.
	 */
	std::vector <mic::types::TensorPtr<eT> > batch_data;

	/// Normalization mode.
	Normalization normalization;

	/// Grid display mode.
	ChannelDisplay channel_display;

	/// Grid display mode.
	Grid grid;
};

} /* namespace visualization */
} /* namespace opengl */
} /* namespace mic */

#endif /* WINDOWGRAYSCALEBATCH_H_ */

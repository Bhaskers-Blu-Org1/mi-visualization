/*!
 * @file: WindowGrayscaleBatch.hpp
 * @Author: Tomasz Kornuta <tkornut@us.ibm.com>
 * @Date:   30-03-2017
 *
 * Copyright (c) 2017, Tomasz Kornuta, IBM Corporation. All rights reserved.
 *
 */

#ifndef WINDOWGRAYSCALEBATCH_H_
#define WINDOWGRAYSCALEBATCH_H_

#include <opengl/visualization/Window.hpp>
#include <opengl/visualization/WindowManager.hpp>

// Dependencies on core types.
#include <types/MNISTTypes.hpp>

namespace mic {
namespace opengl {
namespace visualization {

/*!
 * \brief OpenGL-based window responsible for displaying grayscale (singlechannel) batch in a window.
 * \author tkornuta
 * \@tparam eT Precission (float/double) (DEFAULT=float).
 */

template <typename eT=float>
class WindowGrayscaleBatch: public Window {
public:

	/*!
	 * Display mode of the grayscale (singlechannel) window.
	 */
	enum Normalization {
		Norm_None, //< Displays original image(s) (negative values simply won't be visible).
		Norm_Positive, //< Displays image(s) normalized to <0,1>.
		Norm_HotCold //< Displays image(s) in a hot-cold normalization <-1,1>.
	};

	/*!
	 *
	 */
	enum Grid {
		Grid_None,
		Grid_Sample,
		Grid_Batch,
		Grid_Both
	};

	/*!
	 * Constructor. Sets window position (x,y), size (width, height) and display properties (normalization, grid).
	 */
	WindowGrayscaleBatch(std::string name_ = "WindowGrayscaleBatch",
			Normalization normalization_ = Norm_None, Grid grid_ = Grid_Batch,
			unsigned int position_x_ = 0, unsigned int position_y_ = 0,
			unsigned int width_ = 512,unsigned int height_ = 512,
			bool draw_batch_grid_ = true, bool draw_sample_grid_ = false) :
		Window(name_, position_x_, position_y_, width_, height_),
		normalization(normalization_ ),
		grid(grid_)
	{

	}

	/*!
	 * Virtual destructor - empty.
	 */
	virtual ~WindowGrayscaleBatch() { }


	/*!
	 * Refreshes the content of the window.
	 */
	void displayHandler(void){
		LOG(LTRACE) << "WindowGrayscaleBatch::Display handler of window " << glutGetWindow();
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
			size_t rows = batch_data[0]->rows();
			size_t cols = batch_data[0]->cols();

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

					// Calculate mins and max - for visualization.
					eT min =  std::numeric_limits<double>::max();
					eT max =  std::numeric_limits<double>::min();
					// Find min and max.
					for(size_t i=0; i< rows*cols; i++) {
						min = (min > data_ptr[i]) ? data_ptr[i] : min;
						max = (max < data_ptr[i]) ? data_ptr[i] : max;
					}//: for
					// Check whether we can normalize.
					eT diff = max - min;
					if (diff == 0.0f) {
						min = max = 0.0;
					}

					//eT ultimate_max= (max > -min) ? max : -min;

				   	// Iterate through matrix elements.
					for (size_t y = 0; y < rows; y++) {
						for (size_t x = 0; x < cols; x++) {
							// Get value - REVERSED! as Eigen::Matrix by default is column-major!!
							eT val = data_ptr[x*rows + y];
							eT red, green, blue;

							// Color depending on the visualization.
							switch(normalization) {
							case Normalization::Norm_None:
								red = green = blue = val;
								break;
							case Normalization::Norm_Positive:
								red = green = blue = (val - min)/diff;
								break;
							case Normalization::Norm_HotCold:
								red = (val > 0.0) ? val/max : 0.0f;
								green = 0.0f;
								blue = (val < 0.0) ? val/min : 0.0f;
							}//: switch

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
			case Grid::Grid_None:
				break;
			}//: switch
		}//: if !null

		// Swap buffers.
		glutSwapBuffers();

		// End of critical section.
	}

	/*!
	 * Sets displayed batch.
	 * @param batch_data_ Pointer to a batch to be displayed.
	 */
	void setBatchDataSynchronized(std::vector <std::shared_ptr<mic::types::Matrix<eT> > >  & batch_data_) {
		// Enter critical section.
		APP_DATA_SYNCHRONIZATION_SCOPED_LOCK();

		batch_data = batch_data_;

		// End of critical section.
	}

	/*!
	 * Sets displayed batch. Unsynchronized i.e. must be used inside of manually synchronized section.
	 * @param batch_data_ Pointer to a batch to be displayed.
	 */
	void setBatchDataUnsynchronized(std::vector <std::shared_ptr<mic::types::Matrix<eT> > > & batch_data_) {
		batch_data = batch_data_;
	}


private:

	/*!
	 * Pointer to displayed batch.
	 */
	std::vector <std::shared_ptr<mic::types::Matrix<eT> > > batch_data;

	/// Flag determining whether or what kind of normalization to use.
	Normalization normalization;

	/// Flag determining whether or what kind of grid to draw.
	Grid grid;
};

} /* namespace visualization */
} /* namespace opengl */
} /* namespace mic */

#endif /* WINDOWGRAYSCALEBATCH_H_ */

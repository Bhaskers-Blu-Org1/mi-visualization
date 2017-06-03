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

// Dependencies on core types.
#include <types/MNISTTypes.hpp>

namespace mic {
namespace opengl {
namespace visualization {

/*!
 * \brief OpenGL-based window responsible for displaying 2D matrices.
 * \author tkornuta/krocki
 */
class WindowGrayscaleBatch: public Window {
public:
	/*!
	 * Constructor. Sets window width, height and position (x,y).
	 */
	WindowGrayscaleBatch(std::string name_ = "WindowGrayscaleBatch", unsigned int height_ = 512, unsigned int width_ = 512, unsigned int position_x_ = 0, unsigned int position_y_ = 0, bool draw_batch_grid_ = true, bool draw_sample_grid_ = false);

	/*!
	 * Destructor.
	 */
	virtual ~WindowGrayscaleBatch();


	/*!
	 * Refreshes the content of the window.
	 */
	void displayHandler(void);

	/*!
	 * Sets displayed batch.
	 * @param displayed_matrix_
	 */
	void setBatchDataSynchronized(std::vector <std::shared_ptr<mic::types::MatrixXf> >  & batch_data_);

	/*!
	 * Sets displayed batch. Unsynchronized i.e. must be used inside of manually synchronized section.
	 * @param displayed_matrix_
	 */
	void setBatchDataUnsynchronized(std::vector <std::shared_ptr<mic::types::MatrixXf> > & batch_);


private:

	/*!
	 * Pointer to displayed batch.
	 */
	std::vector <std::shared_ptr<mic::types::MatrixXf> > batch_data;

	/// Flag determining whether to draw batch grid.
	bool draw_batch_grid;

	/// Flag determining whether to draw sample grid.
	bool draw_sample_grid;
};

} /* namespace visualization */
} /* namespace opengl */
} /* namespace mic */

#endif /* WINDOWGRAYSCALEBATCH_H_ */

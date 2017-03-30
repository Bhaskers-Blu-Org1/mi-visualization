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
	 * Constructor. NULLs the image pointer.
	 */
	WindowGrayscaleBatch(std::string name_ = "WindowGrayscaleBatch", unsigned int height_ = 512, unsigned int width_ = 512, unsigned int position_x_ = 0, unsigned int position_y_ = 0);

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
	void setBatchSynchronized(mic::types::MNISTBatch & batch_);

	/*!
	 * Sets displayed batch. Unsynchronized i.e. must be used inside of manually synchronized section.
	 * @param displayed_matrix_
	 */
	void setBatchUnsynchronized(mic::types::MNISTBatch & batch_);


	/*!
	 * Sets pointer to displayed batch.
	 * @param displayed_matrix_
	 */
	void setBatchPtrSynchronized(mic::types::MNISTBatchPtr batch_ptr_);

	/*!
	 * Sets pointer to displayed batch. Unsynchronized i.e. must be used inside of manually synchronized section.
	 * @param displayed_matrix_
	 */
	void setBatchPtrUnsynchronized(mic::types::MNISTBatchPtr batch_ptr_);

private:

	/*!
	 * Pointer to displayed batch.
	 */
	mic::types::MNISTBatchPtr batch_ptr;
};

} /* namespace visualization */
} /* namespace opengl */
} /* namespace mic */

#endif /* WINDOWGRAYSCALEBATCH_H_ */

/*!
 * @file: WindowProbability.h
 * @Author: Tomasz Kornuta <tkornut@us.ibm.com>
 * @Date:   28-03-2017
 *
 * Copyright (c) 2016, IBM Corporation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 *
 */

#ifndef WINDOWPROBABILITY_H_
#define WINDOWPROBABILITY_H_

#include <opengl/visualization/Window.hpp>

// Dependencies on core types.
#include <types/MatrixTypes.hpp>
using namespace mic::types;

namespace mic {
namespace opengl {
namespace visualization {

/*!
 * \brief
 * \author tkornuta
 */
class WindowProbability: public Window {
public:
	/*!
	 * Constructor. NULLs the pointer to probability data.
	 */
	WindowProbability(std::string name_ = "WindowProbability", unsigned int height_ = 512, unsigned int width_ = 512, unsigned int position_x_ = 0, unsigned int position_y_ = 0);

	/*!
	 * Destructor.
	 */
	virtual ~WindowProbability();


	/*!
	 * Refreshes the content of the window.
	 */
	void displayHandler(void);

	/*!
	 * Sets pointer to first displayed matrix with probability distribution.
	 * @param displayed_matrix_
	 */
	void setMatrixPointer1(mic::types::MatrixXfPtr displayed_matrix_);

	/*!
	 * Sets pointer to second displayed matrix with probability distribution.
	 * @param displayed_matrix_
	 */
	void setMatrixPointer2(mic::types::MatrixXfPtr displayed_matrix_);

private:

	/*!
	 * Pointer to first displayed matrix with probabilities.
	 */
	mic::types::MatrixXfPtr displayed_matrix1;

	/*!
	 * Pointer to second displayed matrix with probabilities.
	 */
	mic::types::MatrixXfPtr displayed_matrix2;
};

} /* namespace visualization */
} /* namespace opengl */
} /* namespace mic */

#endif /* WINDOWPROBABILITY_H_ */

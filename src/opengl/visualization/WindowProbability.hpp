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
 * @file: WindowProbability.h
 * @Author: Tomasz Kornuta <tkornut@us.ibm.com>
 * @Date:   28-03-2017
 *
 * Copyright (c) 2017, Tomasz Kornuta, IBM Corporation. All rights reserved.
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
	WindowProbability(std::string name_ = "WindowProbability",
			unsigned int position_x_ = 0, unsigned int position_y_ = 0,
			unsigned int width_ = 512, unsigned int height_ = 512);

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

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
 * \file WindowImage2D.hpp
 * \brief Contains definition of the WindowImage2D class responsible for displaying images.
 * \author tkornuta
 * \date Nov 19, 2015
 */

#ifndef SRC_VISUALIZATION_OPENGL_WINDOWIMAGE2D_HPP_
#define SRC_VISUALIZATION_OPENGL_WINDOWIMAGE2D_HPP_

#include <opengl/visualization/Window.hpp>

// Dependencies on core types.
#include <types/image_types.hpp>
using namespace mic::types;

namespace mic {
namespace opengl {
namespace visualization {


/*!
 * \brief OpenGL-based window responsible for displaying images.
 * \author tkornuta/krocki
 */
class WindowImage2D: public Window {
public:

	/*!
	 * Constructor. NULLs the image pointer.
	 */
	WindowImage2D(std::string name_ = "Image2D",
			unsigned int position_x_ = 0, unsigned int position_y_ = 0,
			unsigned int width_ = 512, unsigned int height_ = 512);

	/*!
	 * Destructor.
	 */
	virtual ~WindowImage2D();


	/*!
	 * Refreshes the content of the window.
	 */
	void displayHandler(void);

	/*!
	 * Sets pointer to displayed image.
	 * @param displayed_image_
	 */
	void setImagePointer(image_ptr_t displayed_image_);

private:

	/*!
	 * Pointer to displayed image.
	 */
	image_ptr_t displayed_image;
};

} /* namespace visualization */
} /* namespace opengl */
} /* namespace mic */

#endif /* SRC_VISUALIZATION_OPENGL_WINDOWIMAGE2D_HPP_ */

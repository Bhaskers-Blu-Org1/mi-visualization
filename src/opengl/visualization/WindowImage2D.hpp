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

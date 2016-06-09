/*!
 * \file WindowMNISTDigit.hpp
 * \brief 
 * \author tkornut
 * \date Jun 8, 2016
 */

#ifndef SRC_OPENGL_VISUALIZATION_WINDOWMNISTDIGIT_HPP_
#define SRC_OPENGL_VISUALIZATION_WINDOWMNISTDIGIT_HPP_

#include <opengl/visualization/Window.hpp>

// Dependencies on core types.
#include <types/TensorTypes.hpp>
using namespace mic::types;

namespace mic {
namespace opengl {
namespace visualization {

/*!
 * \brief MNIST Digit environment channels
 * \author tkornuta
 */
enum class MNISTDigitChannels : std::size_t
{
	Pixels = 0, ///< Channel storing image intensities (this is a grayscale image)
	Goals = 1, ///< Channel storing goal(s)
	Agent = 2, ///< Channel storing the agent position
	Count = 3 ///< Number of channels
};


/*!
 * \brief OpenGL-based window responsible for displaying a MNIST digit with a moving agent on top.
 * \author tkornuta
 */
class WindowMNISTDigit: public Window {
public:
	/*!
	 * Constructor. NULLs the image pointer.
	 */
	WindowMNISTDigit(std::string name_ = "MNISTDigit", unsigned int height_ = 512, unsigned int width_ = 512, unsigned int position_x_ = 0, unsigned int position_y_ = 0);

	/*!
	 * Destructor.
	 */
	virtual ~WindowMNISTDigit();


	/*!
	 * Refreshes the content of the window.
	 */
	void displayHandler(void);

	/*!
	 * Sets pointer to displayed digit.
	 */
	void setDigitPointer(mic::types::TensorXfPtr displayed_digit_);

private:

	/*!
	 * Pointer to displayed matrix.
	 */
	mic::types::TensorXfPtr displayed_digit;
};

} /* namespace visualization */
} /* namespace opengl */
} /* namespace mic */

#endif /* SRC_OPENGL_VISUALIZATION_WINDOWMNISTDIGIT_HPP_ */

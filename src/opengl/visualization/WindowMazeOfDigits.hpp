/*!
 * \file WindowMazeOfDigits.hpp
 * \brief 
 * \author tkornut
 * \date May 9, 2016
 */

#ifndef SRC_OPENGL_VISUALIZATION_WINDOWMAZEOFDIGITS_HPP_
#define SRC_OPENGL_VISUALIZATION_WINDOWMAZEOFDIGITS_HPP_

#include <opengl/visualization/Window.hpp>

// Dependencies on core types.
#include <types/TensorTypes.hpp>
using namespace mic::types;

namespace mic {
namespace opengl {
namespace visualization {

/*!
 * \brief MazeOfDigits channels
 * \author tkornuta
 */
enum class MazeOfDigitsChannels : std::size_t
{
	Goals = 0, ///< Channel storing goal(s)
	Digits = 1, ///< Channel storing digits
	Walls = 2, ///< Channel storing walls(s)
	Agent = 3, ///< Channel storing the agent position
	Count = 4 ///< Number of channels
};

/*!
 * \brief OpenGL-based window responsible for displaying maze of digits (0-9) in a heat map-like form.
 * \author tkornuta
 */
class WindowMazeOfDigits: public Window {
public:
	/*!
	 * Constructor. NULLs the image pointer.
	 */
	WindowMazeOfDigits(std::string name_ = "MazeOfDigits", unsigned int height_ = 512, unsigned int width_ = 512, unsigned int position_x_ = 0, unsigned int position_y_ = 0);

	/*!
	 * Destructor.
	 */
	virtual ~WindowMazeOfDigits();


	/*!
	 * Refreshes the content of the window.
	 */
	void displayHandler(void);

	/*!
	 * Sets pointer to displayed matrix.
	 * @param displayed_matrix_
	 */
	void setMazePointer(mic::types::TensorXfPtr displayed_maze_);

private:

	/*!
	 * Pointer to displayed matrix.
	 */
	mic::types::TensorXfPtr displayed_maze;
};

} /* namespace visualization */
} /* namespace opengl */
} /* namespace mic */

#endif /* SRC_OPENGL_VISUALIZATION_WINDOWMAZEOFDIGITS_HPP_ */

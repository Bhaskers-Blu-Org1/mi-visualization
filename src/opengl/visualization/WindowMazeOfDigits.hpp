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
#include <types/Position2D.hpp>
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
	Digits = 0, ///< Channel storing digits
	Goals = 1, ///< Channel storing goal(s)
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
	WindowMazeOfDigits(std::string name_ = "MazeOfDigits",
			unsigned int position_x_ = 0, unsigned int position_y_ = 0,
			unsigned int width_ = 512, unsigned int height_ = 512);

	/*!
	 * Destructor.
	 */
	virtual ~WindowMazeOfDigits();


	/*!
	 * Refreshes the content of the window.
	 */
	void displayHandler(void);

	/*!
	 * Sets pointer to displayed maze.
	 */
	void setMazePointer(mic::types::TensorXfPtr displayed_maze_);

	/*!
	 * Sets pointer to displayed digit.
	 */
	void setPathPointer(std::shared_ptr<std::vector <mic::types::Position2D> > saccadic_path_);

private:

	/*!
	 * Pointer to displayed matrix.
	 */
	mic::types::TensorXfPtr displayed_maze;

	/// Saccadic path to be displayed - a sequence of consecutive agent positions.
	std::shared_ptr<std::vector <mic::types::Position2D> > saccadic_path;

};

} /* namespace visualization */
} /* namespace opengl */
} /* namespace mic */

#endif /* SRC_OPENGL_VISUALIZATION_WINDOWMAZEOFDIGITS_HPP_ */

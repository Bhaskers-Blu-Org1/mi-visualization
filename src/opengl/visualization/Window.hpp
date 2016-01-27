/*!
 * \file Window.hpp
 * \brief Contains declaration of parent class of all OpenGL-based windows.
 * \author tkornuta
 * \date Nov 18, 2015
 */

#ifndef SRC_VISUALIZATION_OPENGL_WINDOW_HPP_
#define SRC_VISUALIZATION_OPENGL_WINDOW_HPP_

#include <application/KeyHandlerRegistry.hpp>
#include <opengl/visualization/DrawingUtils.hpp>


namespace mic {

/*!
 * \brief Contains classess and tools related to visualization with OpenGl.
 * \author tkornuta
 * \date Nov 18, 2015
 */
namespace opengl {

/*!
 * \brief Contains classess and tools related to visualization of input data, SDRs etc.
 * \author tkornuta
 * \date Nov 18, 2015
 */
namespace visualization {


/*!
 * \brief Parent class of all OpenGL-based windows (abstract).
 * \author tkornuta
 */
class Window : public mic::application::KeyHandlerRegistry, public mic::opengl::visualization::DrawingUtils {
public:

	/*!
	 * Public constructor. Initializes GLUT window, sets window parameters (size, position, name), sets OpenGL parameters (e.g. antialiasing), registers FullWindow key handler and registers the window in manager.
	 * @param name_ Window name. As default set to "OpenGlWindow".
	 * @param height_ Window height. As default set to 512.
	 * @param width_ Window width. As default set to 512.
	 * @param position_x_ X coordinate of the upper left window corner.
	 * @param position_y_ Y coordinate of the upper left window corner.
	 */
	Window(std::string name_ = "OpenGlWindow", unsigned int height_ = 512, unsigned int width_ = 512, unsigned int position_x_ = 0, unsigned int position_y_ = 0);

	/*!
	 * Destructor.
	 */
	virtual ~Window();

	/*!
	 * Returns id of the window.
	 * @return Window id.
	 */
	unsigned int getId() const;

	/*!
	 * Returns name of the window.
	 * @return Window name.
	 */
	std::string getName() const;


	/*!
	 * Refreshes the content of the window - abstract method.
	 */
	virtual void displayHandler(void) = 0;

	/*!
	 * Changes size of the window.
	 * @param width_ New width.
	 * @param height_ New height.
	 */
	virtual void reshapeHandler(int width_, int height_);

protected:
	/*!
	 * Name of the window.
	 */
	std::string name;

	/*!
	 * Window height.
	 */
	unsigned int height;

	/*!
	 * Window width.
	 */
	unsigned int width;

	/*!
	 * Window height before entered the full-screen mode.
	 */
	unsigned int previous_height;

	/*!
	 * Window width before entered the full-screen mode.
	 */
	unsigned int previous_width;

	/*!
	 * Window left corner position x.
	 */
	unsigned int position_x;

	/*!
	 * Window left corner position y.
	 */
	unsigned int position_y;

	/*!
	 * Window ID assigned by OpenGl.
	 */
	unsigned int id;

	/*!
	 * Full screen mode.
	 */
	bool fullscreen_mode;

	/*!
	 *  Keyhandler: toggles fullscreen on/off.
	 */
	void keyhandlerFullscreen(void);


};


} /* namespace opengl */
} /* namespace visualization */
} /* namespace mic */

#endif /* SRC_VISUALIZATION_OPENGL_WINDOW_HPP_ */

/*!
 * \file WindowManager.hpp
 * \brief Declaration of WindowManager class along with a bunch of helpful types and macros.
 * \author tkornuta
 * \date Nov 19, 2015
 */

#ifndef SRC_VISUALIZATION_OPENGL_WINDOWMANAGER_HPP_
#define SRC_VISUALIZATION_OPENGL_WINDOWMANAGER_HPP_

#include <boost/atomic.hpp>
#include <boost/thread/mutex.hpp>

#include <iostream>


namespace mic {
namespace opengl {
namespace visualization {

// Forward declaration of class window, to avoid circular window-manager references.
class Window;

/*!
 * \brief Type used in adding windows to registry.
 * \author tkornuta
 */
typedef std::pair<unsigned int, mic::opengl::visualization::Window*> id_win_pair_t;


/*!
 * \brief Type used in iterating/searching for windows in registry.
 * \author tkornuta
 */
typedef std::map<unsigned int, mic::opengl::visualization::Window*>::iterator id_win_it_t;



/*!
 * \brief Class responsible for management of all OpenGL windows - defined in the form of a singleton, with double-checked locking pattern (DCLP) based access to instance.
 * \author tkornuta
 */
class WindowManager {
public:

	/*!
	 * Virtual destructor.
	 */
	virtual ~WindowManager();

	/*!
	 * Method for accessing the object instance, with double-checked locking optimization.
	 * @return Instance of the WindowManager singleton.
	 */
	static WindowManager* getInstance();

	/*!
	 * Adds window to registry.
	 * @param window_ Pointer to the registered window.
	 */
	void registerWindow(mic::opengl::visualization::Window* window_);

	/*!
	 * Finds window in the registry.
	 * @param id_ Window id.
	 * @return Pointer to the window object or NULL if window id was not found.
	 */
	mic::opengl::visualization::Window* findWindow(unsigned int id_);

	/*!
	 * Refreshes the content of the window.
	 */
	static void displayHandler(void);

	/*!
	 * Changes size of the window.
	 * @param width_ New width.
	 * @param height_ New height.
	 */
	static void reshapeHandler(int width_, int height_);

	/*!
	 * Handles the keypressed event.
	 * @param key_ Pressed key.
	 * @param x_ X coodrinate (unused).
	 * @param y_ Y coordinate (unused).
	 */
	static void keyboardHandler(unsigned char key_, int x_, int y_);

	/*!
	 * Idle function. Iterates through the window registry and updates all windows.
	 */
	static void idle(void);

	/*!
	 * Initializes GLUT.
	 * @param argc
	 * @param argv
	 */
	static void initializeGLUT(int argc, char *argv[]);

	/*!
	 * \brief Runs the main GL loop.
	 *
	 * It must be executed in the main thread (!!) and it is an infinite loop (!!), so the proper application must be executed in a separate thread.
	 */
	void startVisualizationLoop();

private:
    /*!
     * Private instance - accessed as atomic operation.
     */
	static boost::atomic<WindowManager*> instance_;

	/*!
	 * Mutex used for instantiation of the instance.
	 */
	static boost::mutex instantiation_mutex;

	/*!
	 * Private constructor. Initializes GLUT!
	 */
	WindowManager();

	/*!
	 * Window dispatcher, storing pointers to all OpenGL windows.
	 */
	std::map<unsigned int, mic::opengl::visualization::Window*>  window_registry;

};


/*!
 * \brief Macro returning OpenGL window manager instance.
 * \author tkornuta
 */
#define VGL_MANAGER mic::opengl::visualization::WindowManager::getInstance()


} /* namespace visualization */
} /* namespace opengl */
} /* namespace mic */

#endif /* SRC_VISUALIZATION_OPENGL_WINDOWMANAGER_HPP_ */

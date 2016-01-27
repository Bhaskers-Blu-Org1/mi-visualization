/*!
 * \file ConsoleOpenGLApplication.hpp
 * \brief 
 * \author tkornut
 * \date Dec 30, 2015
 */

#ifndef SRC_APPLICATIONS_CONSOLEOPENGLAPPLICATION_HPP_
#define SRC_APPLICATIONS_CONSOLEOPENGLAPPLICATION_HPP_

#include <logger/Log.hpp>
using namespace mic::logger;

#include <application/Application.hpp>
#include <opengl/visualization/WindowManager.hpp>

namespace mic {
namespace opengl {
namespace application {

/*!
 * \brief An abstract class implementing basic functions for two-threaded, OpenGL-based applications.
 * Introduces the execution phases that are typical for all learning/classification applications, imposes fine code granulation.
 * \author tkornuta
 */
class ConsoleOpenGLApplication: public mic::application::Application {
public:

	/*!
	 * Default Constructor. Sets the application/node name.
	 * @param node_name_ Name of the application/node (in configuration file).
	 */
	ConsoleOpenGLApplication(std::string node_name_);

	/*!
	 * Virtual destructor. Empty for now.
	 */
	virtual ~ConsoleOpenGLApplication() { };

	/*!
	 * Initializes application. Abstract method. By default it should: initialize GLUT and all required OpenGL windows.
	 * (Note: all OpenGL windows  - they must be created in the main application thread :])
	 * @param argc Number of application parameters.
	 * @param argv Array of application parameters.
	 */
	virtual void initialize(int argc, char* argv[]) = 0;

	/*!
	 * Runs the application - the processing in an external thread and OpenGL in the main thread.
	 */
	virtual void run();

protected:

	/*!
	 * \brief Function realizing the processing thread. Now empty - but will be overridden by derived classes!
	 * \author tkornuta
	 */
	virtual void processingThread(void) { };

};

} /* namespace application */
} /* namespace opengl */
} /* namespace mic */

#endif /* SRC_APPLICATIONS_CONSOLEOPENGLAPPLICATION_HPP_ */

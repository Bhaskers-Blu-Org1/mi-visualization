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
 * \file ConsoleOpenGLApplication.hpp
 * \brief 
 * \author tkornut
 * \date Dec 30, 2015
 */

#ifndef SRC_APPLICATIONS_CONSOLEOPENGLAPPLICATION_HPP_
#define SRC_APPLICATIONS_CONSOLEOPENGLAPPLICATION_HPP_

#include <application/Application.hpp>
#include <opengl/visualization/WindowManager.hpp>

namespace mic {
namespace opengl {

/*!
 * \brief Namespace contains classess useful for creation of OpenGL-based applications.
 * \author tkornuta
 * \date Jan 11, 2016
 */
namespace application {

/*!
 * \brief An abstract class implementing basic functions for two-threaded, OpenGL-based applications.
 * Introduces the execution phases that are typical for all learning/classification applications, imposes fine code granulation.
 * \author tkornuta
 */
class OpenGLApplication: public mic::application::Application {
public:

	/*!
	 * Default Constructor. Sets the application/node name.
	 * @param node_name_ Name of the application/node (in configuration file).
	 */
	OpenGLApplication(std::string node_name_);

	/*!
	 * Virtual destructor. Empty for now.
	 */
	virtual ~OpenGLApplication() { };

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
	 * \brief Function realizing the processing thread. Implements basic quit/pause/single step functionality. In each step it calls the performSingleStep() method. Can be overridden by derived classes.
	 * \author tkornuta
	 */
	virtual void processingThread(void);

	/*!
	 * \brief The initial step - empty, to be overridden.
	 * \author gwburr
	 */
	virtual void performInitialStep(void) { };

	/*!
	 * \brief The initial step - empty, to be overridden.
	 * \author gwburr
	 */
	virtual void performFinalStep(void) { };

};

} /* namespace application */
} /* namespace opengl */
} /* namespace mic */

#endif /* SRC_APPLICATIONS_CONSOLEOPENGLAPPLICATION_HPP_ */

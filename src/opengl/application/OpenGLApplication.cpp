/*!
 * \file ConsoleOpenGLApplication.cpp
 * \brief 
 * \author tkornut
 * \date Dec 30, 2015
 */

#include <iostream>
#include <fstream>

#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <opengl/application/OpenGLApplication.hpp>

namespace mic {
namespace opengl {
namespace application {

OpenGLApplication::OpenGLApplication(std::string node_name_) : Application(node_name_)
{
	// Empty for now.
}


void OpenGLApplication::run() {
	// Run the processing thread.
	boost::thread processing_thread(boost::bind(&OpenGLApplication::processingThread, this));

	// Start main OpenGL loop.
	VGL_MANAGER->startVisualizationLoop();
	LOG(LINFO) << "OpenGL thread terminated...";

	// Wait for the processing thread to end.
	processing_thread.join();
  std::cout << "Processing thread done" << std::endl;
	LOG(LINFO) << "Processing thread terminated...";

}


void OpenGLApplication::processingThread(void) {

	// Start from learning.
	APP_STATE->setLearningModeOn();

 	// Main application loop.
	while (!APP_STATE->Quit()) {

		// If not paused.
		if (!APP_STATE->isPaused()) {
			// If single step mode - pause after the step.
			if (APP_STATE->isSingleStepModeOn())
				APP_STATE->pressPause();

			// Enter critical section - with the use of scoped lock from AppState!
			APP_DATA_SYNCHRONIZATION_SCOPED_LOCK();

			// Perform single step and - if required - break the loop.
			iteration++;
			if (!performSingleStep()) {
				LOG(LINFO) << "Terminating application...";
				APP_STATE->setQuit();
				break;
			} else if (((long)number_of_iterations > 0) && ( iteration >= (long) number_of_iterations)) {
				LOG(LINFO) << "Reached last Iteration. Terminating application...";
				APP_STATE->setQuit();
				break;
			}//: else if

		} //: if! is paused & end of critical section

		// Sleep.
		APP_SLEEP();
	}//: while
	LOG(LINFO) << "We're outside the processing loop now...";
}


} /* namespace applications */
} /* namespace opengl */
} /* namespace mic */

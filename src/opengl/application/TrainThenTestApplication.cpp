/*!
 * \file TrainThenTestApplication.cpp
 * \brief 
 * \author tkornut
 * \date Jan 15, 2016
 */

#include "TrainThenTestApplication.hpp"

namespace mic {
namespace opengl {
namespace application {


TrainThenTestApplication::TrainThenTestApplication(std::string node_name_) : ConsoleOpenGLApplication(node_name_)
{
	// Empty for now.
}

void TrainThenTestApplication::processingThread(void) {

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

			// If learning mode.
			if (APP_STATE->isLearningModeOn())  {
				// Perform learning - until there is something to learn.
				if (!performLearningStep()) {
					APP_STATE->setLearningModeOff();
				}
			} else {
				// Perform testing - until there is something to test.
				if (!performTestingStep())
					break;
			}//: else

		 	iteration++;
		} //: if! is paused & end of critical section

		// Sleep.
		APP_SLEEP();
	}//: while
}




} /* namespace application */
} /* namespace opengl */
} /* namespace mic */

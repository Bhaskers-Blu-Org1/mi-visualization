/*!
 * \file ContinuousLearningApplication.cpp
 * \brief 
 * \author tkornut
 * \date Jan 15, 2016
 */

#include <opengl/application/ContinuousLearningApplication.hpp>

namespace mic {
namespace opengl {
namespace application {

ContinuousLearningApplication::ContinuousLearningApplication(std::string node_name_) : ConsoleOpenGLApplication(node_name_),
		learning_iterations_to_test_ratio("learning_iterations_to_test_ratio", 50),
		number_of_averaged_test_measures("number_of_averaged_test_measures", 5)
{
	// Register properties - so their values can be overridden (read from the configuration file).
	registerProperty(learning_iterations_to_test_ratio);
	registerProperty(number_of_averaged_test_measures);

	// Reset learning iteration counter.
	learning_iteration = 0;
}

void ContinuousLearningApplication::processingThread(void) {

 	// Main application loop.
	while (!APP_STATE->Quit()) {

		// If not paused.
		if (!APP_STATE->isPaused()) {
			// If single step mode - pause after the step.
			if (APP_STATE->isSingleStepModeOn())
				APP_STATE->pressPause();

			// Enter critical section - with the use of scoped lock from AppState!
			APP_DATA_SYNCHRONIZATION_SCOPED_LOCK();

			// Check iteration number.
			if ((iteration % learning_iterations_to_test_ratio) == 0) {
				APP_STATE->setLearningModeOff();
			} else {
				APP_STATE->setLearningModeOn();
			}//: else

			// If learning mode.
			if (APP_STATE->isLearningModeOn())  {
				// Perform learning.
				performLearning();
			} else {
				// Perform testing.
				performTesting();
			}//: else

		 	iteration++;
		} //: if! is paused & end of critical section

		// Sleep.
		APP_SLEEP();
	}//: while
}

void ContinuousLearningApplication::performTesting() {

	// Perform testing - two phases.
	collectTestStatistics();

	// If a given number of measures were collected - average them and populate (i.e. visualize).
	if (learning_iteration % number_of_averaged_test_measures == 0) {

		populateTestStatistics();
		// Reset learning iteration counter.
		learning_iteration=0;
	}//: if iteration

	learning_iteration++;
} //: if test mode (!learning)


} /* namespace application */
} /* namespace opengl */
} /* namespace mic */

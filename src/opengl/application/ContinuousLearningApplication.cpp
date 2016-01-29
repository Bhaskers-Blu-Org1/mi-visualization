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

ContinuousLearningApplication::ContinuousLearningApplication(std::string node_name_) : OpenGLApplication(node_name_),
		learning_iterations_to_test_ratio("learning_iterations_to_test_ratio", 50),
		number_of_averaged_test_measures("number_of_averaged_test_measures", 5)
{
	// Register properties - so their values can be overridden (read from the configuration file).
	registerProperty(learning_iterations_to_test_ratio);
	registerProperty(number_of_averaged_test_measures);

	// Reset learning iteration counter.
	learning_iteration = 0;
}

bool ContinuousLearningApplication::performSingleStep(void) {

	// Check the iteration number.
	if ((iteration % learning_iterations_to_test_ratio) == 0) {
		APP_STATE->setLearningModeOff();
	} else {
		APP_STATE->setLearningModeOn();
	}//: else

	// If learning mode.
	if (APP_STATE->isLearningModeOn())  {
		// Perform learning.
		 return performLearningStep();
	} else {
		// Perform testing.
		return performTestingStep();
	}//: else

	//return true;
}

bool ContinuousLearningApplication::performTestingStep() {

	// Perform testing - two phases.
	collectTestStatistics();

	// If a given number of measures were collected - average them and populate (i.e. visualize).
	if (learning_iteration % number_of_averaged_test_measures == 0) {

		populateTestStatistics();
		// Reset learning iteration counter.
		learning_iteration=0;
	}//: if iteration

	learning_iteration++;

	return true;
} //: if test mode (!learning)


} /* namespace application */
} /* namespace opengl */
} /* namespace mic */

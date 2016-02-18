/*!
 * \file ContinuousLearningApplication.cpp
 * \brief 
 * \author tkornut
 * \date Jan 15, 2016
 */

#include <opengl/application/OpenGLContinuousLearningApplication.hpp>

namespace mic {
namespace opengl {
namespace application {

OpenGLContinuousLearningApplication::OpenGLContinuousLearningApplication(std::string node_name_) : OpenGLApplication(node_name_),
		learning_iterations_to_test_ratio("learning_iterations_to_test_ratio", 50),
		number_of_averaged_test_measures("number_of_averaged_test_measures", 5)
{
	// Register properties - so their values can be overridden (read from the configuration file).
	registerProperty(learning_iterations_to_test_ratio);
	registerProperty(number_of_averaged_test_measures);

	// Reset learning iteration counter.
	learning_iteration = 0;
}

bool OpenGLContinuousLearningApplication::performSingleStep(void) {
	// Increment iteration number - at START!
	iteration++;

	// Check the iteration number and settings.
	// If learning is on AND (NOT equal to learning_iterations_to_test_ratio) - learn!
	if (((iteration % learning_iterations_to_test_ratio) != 0) && APP_STATE->isLearningModeOn()) {
		// Perform learning.
		 return performLearningStep();
	} else { // Else - test
		// Perform testing.
		return performTestingStep();
	}//: else
}

bool OpenGLContinuousLearningApplication::performTestingStep() {
	// Increment iteration number - at START!
	learning_iteration++;

	LOG(LDEBUG) << "iteration=" << iteration << "learning_iteration=" << learning_iteration << " learning_iteration % number_of_averaged_test_measures =" << learning_iteration % number_of_averaged_test_measures;

	// Perform testing - two phases.
	collectTestStatistics();

	// If a given number of measures were collected - average them and populate (i.e. visualize).
	if (learning_iteration % number_of_averaged_test_measures == 0) {

		populateTestStatistics();
		// Reset learning iteration counter.
		learning_iteration=0;
	}//: if iteration

	return true;
} //: if test mode (!learning)


} /* namespace application */
} /* namespace opengl */
} /* namespace mic */

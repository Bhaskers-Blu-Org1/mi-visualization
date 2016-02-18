/*!
 * \file TrainThenTestApplication.cpp
 * \brief 
 * \author tkornut
 * \date Jan 15, 2016
 */

#include <opengl/application/OpenGLTrainThenTestApplication.hpp>

namespace mic {
namespace opengl {
namespace application {


OpenGLTrainThenTestApplication::OpenGLTrainThenTestApplication(std::string node_name_) : OpenGLApplication(node_name_)
{
	// Start from learning.
	APP_STATE->setLearningModeOn();
}

bool OpenGLTrainThenTestApplication::performSingleStep(void) {
	// Increment iteration number - at START!
	iteration++;

	// If learning mode.
	if (APP_STATE->isLearningModeOn())  {
		// Perform learning - until there is something to learn.
		if (!performLearningStep()) {
			APP_STATE->setLearningModeOff();
		}
	} else {
		// Perform testing - until there is something to test.
		if (!performTestingStep())
			return false;
	}//: else

	return true;
}




} /* namespace application */
} /* namespace opengl */
} /* namespace mic */

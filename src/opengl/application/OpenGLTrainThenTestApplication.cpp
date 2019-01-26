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

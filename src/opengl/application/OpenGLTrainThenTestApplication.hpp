/*!
 * \file TrainThenTestApplication.hpp
 * \brief 
 * \author tkornut
 * \date Jan 15, 2016
 */

#ifndef SRC_OPENGL_APPLICATION_OPENGLTRAINTHENTESTAPPLICATION_HPP_
#define SRC_OPENGL_APPLICATION_OPENGLTRAINTHENTESTAPPLICATION_HPP_

#include <opengl/application/OpenGLApplication.hpp>

namespace mic {
namespace opengl {
namespace application {

class OpenGLTrainThenTestApplication : public opengl::application::OpenGLApplication {
public:
	/*!
	 * Default constructor. Sets the application/node name and registers properties.
	 * @param node_name_ Name of the application/node (in configuration file).
	 */
	OpenGLTrainThenTestApplication(std::string node_name_);

	/*!
	 * Default destructor - empty.
	 */
	virtual ~OpenGLTrainThenTestApplication() { };

protected:
	/*!
	 * Performs single step of computations. Depending on the state, calls learning or testing step - switches from learning to testing then learning return false.
	 */
	virtual bool performSingleStep();

	/*!
	 * Perform learning step - abstract, to be overridden.
	 * @return Returns false when test learning is completed.
	 */
	virtual bool performLearningStep() = 0;

	/*!
	 * Perform testing step - abstract, to be overridden.
	 * @return Returns false when test learning is completed.
	 */
	virtual bool performTestingStep() = 0;

};

} /* namespace application */
} /* namespace opengl */
} /* namespace mic */

#endif /* SRC_OPENGL_APPLICATION_OPENGLTRAINTHENTESTAPPLICATION_HPP_ */

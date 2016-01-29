/*!
 * \file TrainThenTestApplication.hpp
 * \brief 
 * \author tkornut
 * \date Jan 15, 2016
 */

#ifndef SRC_OPENGL_APPLICATION_TRAINTHENTESTAPPLICATION_HPP_
#define SRC_OPENGL_APPLICATION_TRAINTHENTESTAPPLICATION_HPP_

#include <opengl/application/OpenGLApplication.hpp>

namespace mic {
namespace opengl {

/*!
 * \brief Contains classess useful for creation of OpenGL-based applications.
 * \author tkornuta
 * \date Jan 11, 2016
 */
namespace application {

class TrainThenTestApplication : public opengl::application::OpenGLApplication {
public:
	/*!
	 * Default constructor. Sets the application/node name and registers properties.
	 * @param node_name_ Name of the application/node (in configuration file).
	 */
	TrainThenTestApplication(std::string node_name_);

	/*!
	 * Default destructor - empty.
	 */
	virtual ~TrainThenTestApplication() { };

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

#endif /* SRC_OPENGL_APPLICATION_TRAINTHENTESTAPPLICATION_HPP_ */

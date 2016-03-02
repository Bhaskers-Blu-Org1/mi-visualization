/*!
 * \file OpenGLEpisodicApplication.hpp
 * \brief 
 * \author tkornut
 * \date Feb 19, 2016
 */

#ifndef SRC_OPENGL_APPLICATION_OPENGLEPISODICAPPLICATION_HPP_
#define SRC_OPENGL_APPLICATION_OPENGLEPISODICAPPLICATION_HPP_

#include <opengl/application/OpenGLApplication.hpp>

namespace mic {
namespace opengl {
namespace application {

/*!
 * \brief Parent class for all applications basing on episodes, without distinguising learning and training phases.
 * Each episode will end when step will return false.
 *
 * \author tkornuta
 * \date Feb 19, 2016
 */
class OpenGLEpisodicApplication: public mic::opengl::application::OpenGLApplication {
public:
	/*!
	 * Default constructor. Sets the application/node name and registers properties.
	 * @param node_name_ Name of the application/node (in configuration file).
	 */
	OpenGLEpisodicApplication(std::string node_name_);

	/*!
	 * Default destructor - empty.
	 */
	virtual ~OpenGLEpisodicApplication() { };

	/*!
	 * \brief Function realizing the processing thread. Implements basic quit/pause/single step functionality. In each step it calls the performSingleStep() method. Can be overridden by derived classes.
	 * \author tkornuta
	 */
	virtual void processingThread(void);

protected:

	/*!
	 * Method called at the beginning of new episode (goal: to reset the statistics etc.) - abstract, to be overridden.
	 */
	virtual void startNewEpisode() = 0;

	/*!
	 * Method called when given episode ends (goal: export collected statistics to file etc.) - abstract, to be overridden.
	 */
	virtual void finishCurrentEpisode() = 0;


	/// Episode counter.
	unsigned long episode;

	/*!
	 * Property: number of episodes, after which the application will end. 0 (default value) deactivates terminal condition (unlimited number of episodes).
	 */
	mic::configuration::Property<long> number_of_episodes;

};


} /* namespace application */
} /* namespace opengl */
} /* namespace mic */

#endif /* SRC_OPENGL_APPLICATION_OPENGLEPISODICAPPLICATION_HPP_ */

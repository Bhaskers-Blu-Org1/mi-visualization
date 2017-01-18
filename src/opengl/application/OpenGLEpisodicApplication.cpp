/*!
 * \file OpenGLEpisodicApplication.cpp
 * \brief 
 * \author tkornut
 * \date Feb 19, 2016
 */

#include <opengl/application/OpenGLEpisodicApplication.hpp>

namespace mic {
namespace opengl {
namespace application {

OpenGLEpisodicApplication::OpenGLEpisodicApplication(std::string node_name_) : mic::opengl::application::OpenGLApplication(node_name_),
		episode(0),
		number_of_episodes("number_of_episodes", 0)
{
	// Register properties - so their values can be overridden (read from the configuration file).
	registerProperty(number_of_episodes);

}


void OpenGLEpisodicApplication::processingThread(void) {

	// Start a new episode.
	startNewEpisode();

 	// Main application loop.
	while (!APP_STATE->Quit()) {

		// If not paused.
		if (!APP_STATE->isPaused()) {
			// If single step mode - pause after the step.
			if (APP_STATE->isSingleStepModeOn())
				APP_STATE->pressPause();

			// Enter critical section - with the use of scoped lock from AppState!
			APP_DATA_SYNCHRONIZATION_SCOPED_LOCK();

			// Increment iteration number - at START!
			iteration++;
			// Perform single step and - if required - break the loop.
			if (!performSingleStep()) {
				// Finish the current episode.
				episode++;
				finishCurrentEpisode();

				// Check terminal condition.
				if (((long)number_of_episodes > 0) && ( (long)episode >= (long) number_of_episodes)) {
					APP_STATE->setQuit();
					LOG(LINFO) << "Reached last episode (" << episode << "). Terminating application...";
				} else {
					// Else - start a new episode.
					startNewEpisode();
					iteration=0;
				}//: else
			}//: if singleStep

		} //: if! is paused & end of critical section

		// Sleep.
		APP_SLEEP();
	}//: while
}


} /* namespace application */
} /* namespace opengl */
} /* namespace mic */

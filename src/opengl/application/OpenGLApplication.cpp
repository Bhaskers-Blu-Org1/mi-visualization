/*!
 * \file ConsoleOpenGLApplication.cpp
 * \brief 
 * \author tkornut
 * \date Dec 30, 2015
 */

#include <iostream>
#include <fstream>

#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <opengl/application/OpenGLApplication.hpp>
//#include <opengl/visualization/WindowManager.hpp>

namespace mic {
  namespace opengl {
    namespace application {

      OpenGLApplication::OpenGLApplication(std::string node_name_) : Application(node_name_) {
        // Empty for now.
      }

      void OpenGLApplication::run() {
        // Run the processing thread.
        boost::thread processing_thread(boost::bind(&OpenGLApplication::processingThread, this));

        // Start main OpenGL loop.
        VGL_MANAGER->startVisualizationLoop();
        LOG(LINFO) << "OpenGL thread terminated. Waiting for the threads to join...";

        // Wait for the processing thread to end.
        processing_thread.join();
        LOG(LINFO) << "Threads joined";

      }

      void OpenGLApplication::processingThread(void) {

        // Start from learning.
        APP_STATE->setLearningModeOn();

        // Perform the initial step.
        LOG(LINFO) << "Performing the initial step...";
        performInitialStep();

        // Main application loop.
        LOG(LINFO) << "Starting the main loop...";
        while (!APP_STATE->Quit()) {

          // If not paused.
          if (!APP_STATE->isPaused()) {
            // If single step mode - pause after the step.
            if (APP_STATE->isSingleStepModeOn())
              APP_STATE->pressPause();

            // Enter critical section - with the use of scoped lock from AppState!
            APP_DATA_SYNCHRONIZATION_SCOPED_LOCK();

            // Perform single step and - if required - break the loop.
            iteration++;
            if (!performSingleStep()) {
              LOG(LINFO) << "Terminating application...";
              APP_STATE->setQuit();
              break;
            }
            else if (((long) number_of_iterations > 0) && ((long)iteration >= (long) number_of_iterations)) {
              LOG(LINFO) << "Reached last Iteration. Terminating application...";
              APP_STATE->setQuit();
              break;
            }//: else if

          } //: if! is paused & end of critical section

          // Sleep.
        }//: while

        LOG(LINFO) << "Performing the final step...";
        // Perform the final step.
        performFinalStep();
        LOG(LINFO) << "Final step complete";

        // Wait until OpenGL will "stop"...
//        while (APP_STATE->usingOpenGL())
//            APP_SLEEP();
        // ... and then quit - not required, because we will wait anyway at thread.join()
      }

    } /* namespace applications */
  } /* namespace opengl */
} /* namespace mic */

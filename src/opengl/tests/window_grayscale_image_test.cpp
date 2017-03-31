/*!
 * \file window_grayscale_image_test.cpp
 * \brief Program for testing ImageEncoder and Visualization.
 * \author tkornuta
 * \date Nov 20, 2015
 *
 * Copyright (c) 2017, Tomasz Kornuta, IBM Corporation. All rights reserved.
 *
 */

#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>

#include <types/MNISTTypes.hpp>

#include <logger/Log.hpp>
#include <logger/ConsoleOutput.hpp>
using namespace mic::logger;

#include <opengl/visualization/WindowManager.hpp>
#include <opengl/visualization/WindowMatrix2D.hpp>
using namespace mic::opengl::visualization;

/// Window displaying the image.
WindowMatrix2D* w_batch;

/*!
 * \brief Function for testing ImageEncoder/WindowImage2D classes.
 * \author tkornuta
 */
void test_thread_body (void) {

	// Generate a batch.
	mic::types::MNISTBatch batch;
	for(size_t i=0; i< 15; i++) {
		// Generate "data".
		MatrixXfPtr data (new MatrixXf(3, 5));
		data->setZero();
		(*data)(i)=1;
		batch.data().push_back(data);

		// Generate "label".
		batch.labels().push_back(std::make_shared<unsigned int>(i));

		// Add index.
		batch.indices().push_back(i);
	}//: for

 	// Main application loop.
	while (!APP_STATE->Quit()) {

		// If not paused.
		if (!APP_STATE->isPaused()) {

			// If single step mode - pause after the step.
			if (APP_STATE->isSingleStepModeOn())
				APP_STATE->pressPause();

			{ // Enter critical section - with the use of scoped lock from AppState!
				APP_DATA_SYNCHRONIZATION_SCOPED_LOCK();

				// Select random image-label pair.
				mic::types::MNISTSample sample = batch.getRandomSample();

				// Set sample to be displayed.
				w_batch->setMatrixPointerUnsynchronized(sample.data());
			}//: end of critical section

		}//: if

		// Sleep.
		APP_SLEEP();
	}//: while

}//: image_encoder_and_visualization_test



/*!
 * \brief Main program function. Runs two threads: main (for GLUT) and another one (for data processing).
 * \author tkornuta
 * @param[in] argc Number of parameters (not used).
 * @param[in] argv List of parameters (not used).
 * @return (not used)
 */
int main(int argc, char* argv[]) {
	// Set console output to logger.
	LOGGER->addOutput(new ConsoleOutput());
	LOG(LINFO) << "Logger initialized. Starting application";

	// Initialize GLUT! :]
	VGL_MANAGER->initializeGLUT(argc, argv);

	// Create two visualization windows - in the same, main thread :]
	w_batch = new WindowMatrix2D("Grayscale image", 512, 512, 0, 0);

	boost::thread test_thread(boost::bind(&test_thread_body));

	// Start visualization thread.
	VGL_MANAGER->startVisualizationLoop();

	LOG(LINFO) << "Waiting for threads to join...";
	// End test thread.
	test_thread.join();
	LOG(LINFO) << "Threads joined - ending application";
}//: main

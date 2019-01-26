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
 * @file window_batch_test.cpp
 * @brief Program for testing batch visualization.
 * @author tkornuta
 * @Date:   30-03-2017
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
#include <opengl/visualization/WindowGrayscaleBatch.hpp>
using namespace mic::opengl::visualization;

/// Window displaying the image.
WindowGrayscaleBatch<float>* w_batch;

/*!
 * \brief Function for testing ImageEncoder/WindowImage2D classes.
 * \author tkornuta
 */
void test_thread_body (void) {

	// Generate a batch that will be used for returning minibatches of size 5.
	mic::types::MNISTBatch<float> batch(6);
	for(size_t i=0; i< 18; i++) {
		// Generate "data".
		MatrixXfPtr data (new MatrixXf(3, 6));
		data->setZero();
		(*data)(i)=(float)(i-9.0)/18.0;
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

				// Retrieve the next minibatch.
				mic::types::MNISTBatch<float> bt = batch.getNextBatch();

				// Set sample to be displayed.
				w_batch->setBatchUnsynchronized(bt.data());
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

	// Create batch visualization window.
	w_batch = new WindowGrayscaleBatch<float>("Grayscale batch", Grayscale::Norm_HotCold, Grayscale::Grid_Both, 0, 0, 512, 512);

	boost::thread test_thread(boost::bind(&test_thread_body));

	// Start visualization thread.
	VGL_MANAGER->startVisualizationLoop();

	LOG(LINFO) << "Waiting for threads to join...";
	// End test thread.
	test_thread.join();
	LOG(LINFO) << "Threads joined - ending application";
}//: main

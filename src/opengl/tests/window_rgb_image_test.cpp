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

#include <fstream>

#include <types/MNISTTypes.hpp>
#include <types/TensorTypes.hpp>

#include <logger/Log.hpp>
#include <logger/ConsoleOutput.hpp>
using namespace mic::logger;

#include <data_io/CIFARImporter.hpp>
#include <data_io/BMPImporter.hpp>

#include <opengl/visualization/WindowManager.hpp>
#include <opengl/visualization/WindowRGBTensor.hpp>
using namespace mic::opengl::visualization;

/// Window displaying the image.
WindowRGBTensor<float>* w_batch;


/*!
 * \brief Function for testing ImageEncoder/WindowImage2D classes.
 * \author tkornuta
 */
void test_thread_body (void) {

	// Import exemplary BMPs.
	/*mic::data_io::BMPImporter<float> importer;
	importer.setDataFilename("../data/gigapan1.bmp");//../data/lena.bmp;../data/lena_eye.bmp;../data/lena_fovea.bmp;../data/rainbow.bmp");
	if (!importer.importData())
		return;*/

	mic::data_io::CIFARImporter<float> importer;
	importer.setDataFilename("../data/cifar-10-batches-bin/data_batch_1.bin;../data/cifar-10-batches-bin/data_batch_2.bin");
	if (!importer.importData())
		return;

	importer.setBatchSize(4);

 	// Main application loop.
	while (!APP_STATE->Quit()) {

		// If not paused.
		if (!APP_STATE->isPaused()) {

			// If single step mode - pause after the step.
			if (APP_STATE->isSingleStepModeOn())
				APP_STATE->pressPause();

			{ // Enter critical section - with the use of scoped lock from AppState!
				APP_DATA_SYNCHRONIZATION_SCOPED_LOCK();

				// Select random sample/batch.
				//mic::types::TensorSample<float> sample = importer.getRandomSample();
				mic::types::TensorBatch<float> batch = importer.getRandomBatch();

				// Set sample/batch to be displayed.
				w_batch->setBatchUnsynchronized(batch.data());
				//w_batch->setSampleUnsynchronized(sample.data());
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
	//LOGGER->setSeverityLevel(Debug);

	// Initialize GLUT! :]
	VGL_MANAGER->initializeGLUT(argc, argv);

	// Create two visualization windows - in the same, main thread :]
	w_batch = new WindowRGBTensor<float>("Batch", RGB::Chan_RGB, RGB::Norm_None, RGB::Grid_Batch, 0, 0, 3*512, 512);

	boost::thread test_thread(boost::bind(&test_thread_body));

	// Start visualization thread.
	VGL_MANAGER->startVisualizationLoop();

	LOG(LINFO) << "Waiting for threads to join...";
	// End test thread.
	test_thread.join();
	LOG(LINFO) << "Threads joined - ending application";
}//: main

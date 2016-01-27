/*!
 * \file image_encoder_test.cpp
 * \brief Program for testing ImageEncoder and Visualization.
 * \author tkornuta
 * \date Nov 20, 2015
 */

#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>

#include <data_utils/image_tools.hpp>
#include <data_utils/rand.hpp>
using namespace mic::data_utils;

#include <data_io/MNISTImageImporter.hpp>
#include <auto_encoders/DummyGrayscaleImageEncoder.hpp>

#include <logger/Log.hpp>
#include <logger/ConsoleOutput.hpp>
using namespace mic::logger;

#include <application/ApplicationState.hpp>

#ifdef USE_OPENGL
#include <opengl/visualization/WindowManager.hpp>
#include <opengl/visualization/WindowImage2D.hpp>
using namespace mic::opengl::visualization;

/// Window for displaying input image.
WindowImage2D* w2d_input;
/// Window for displaying input image reconstruction.
WindowImage2D* w2d_reconstruction;

#endif



/*!
 * \brief Function for testing ImageEncoder/WindowImage2D classes.
 * \author tkornuta
 */
void image_encoder_and_visualization_test (void) {
	// Create temp variables.
	image_ptr_t current_image (new image());
	image_ptr_t reconstructed_image (new image());

	alloc_image(current_image.get(), GRAYSCALE, 28, 28);
	alloc_image(reconstructed_image.get(), GRAYSCALE, 28, 28);

	mic::auto_encoders::DummyGrayscaleImageEncoder ie;
	mic::types::floatSDR image_sdr;

#ifdef USE_OPENGL
	// Set images to display.
	w2d_input->setImagePointer(current_image);
	w2d_reconstruction->setImagePointer(reconstructed_image);
#endif
	// Load dataset.
	mic::data_io::MNISTImageImporter importer;
	// Manually set paths. DEPRICATED!
	importer.setDataFilename("/Users/tkornut/Documents/workspace/machine-intelligence-core/data/mnist/train-images-idx3-ubyte");
	importer.setLabelsFilename("/Users/tkornut/Documents/workspace/machine-intelligence-core/data/mnist/train-labels-idx1-ubyte");

	if (!importer.importData())
		return;

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
				mnist_pair_t sample = importer.getRandomSample();

				// Copy image to pointer.
				copy_image( sample.first.get(), current_image.get());

				// Encode the selected image into SDR.
				ie.encode(*current_image, image_sdr);

				// Change a single element of SDR.
				image_sdr[0]=255;

				// Decode SDR.
				ie.decode(*reconstructed_image, image_sdr);

			}//: end of critical section

		}//: if

		// Sleep.
		APP_SLEEP();
	}//: while

	// Free memory.
	free_image(current_image.get());
	free_image(reconstructed_image.get());

}//: image_encoder_and_visualization_test



/*!
 * \brief Main program function. Runs two threads: main (for GLUT) and another one (for data processing).
 * \author tkornuta
 * @param[in] argc Number of parameters (passed to glManaged).
 * @param[in] argv List of parameters (passed to glManaged).
 * @return (not used)
 */
int main(int argc, char* argv[]) {
	// Set console output to logger.
	LOGGER->addOutput(new ConsoleOutput());
	LOG(LINFO) << "Logger initialized. Starting application";



#ifdef USE_OPENGL
	// Initialize GLUT! :]
	VGL_MANAGER->initializeGLUT(argc, argv);

	// Create two visualization windows - in the same, main thread :]
	w2d_input = new WindowImage2D("Input image", 512, 512, 0, 0);
	w2d_reconstruction = new WindowImage2D("Reconstructed image", 512, 512, 512, 0);
#endif

	boost::thread test_thread(boost::bind(&image_encoder_and_visualization_test));

#ifdef USE_OPENGL
	// Start visualization thread.
	VGL_MANAGER->startVisualizationLoop();
#endif

	// End test thread.
	test_thread.join();
	LOG(LINFO) << "Threads joined. Ending application";
}//: main

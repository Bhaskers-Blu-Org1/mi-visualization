/*!
 * \file image_encoder_test.cpp
 * \brief Program for testing ImageEncoder and Visualization.
 * \author tkornuta
 * \date Nov 20, 2015
 */

#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>

#include <data_io/MNISTMatrixImporter.hpp>
#include <encoders/MatrixXfMatrixXfEncoder.hpp>

#include <logger/Log.hpp>
#include <logger/ConsoleOutput.hpp>
using namespace mic::logger;

#include <application/ApplicationState.hpp>

#include <configuration/ParameterServer.hpp>

#include <opengl/visualization/WindowManager.hpp>
#include <opengl/visualization/WindowMatrix2D.hpp>
using namespace mic::opengl::visualization;

/// Window for displaying input image.
WindowMatrix2D* w2d_input;
/// Window for displaying input image reconstruction.
WindowMatrix2D* w2d_reconstruction;
/// MNIST importer.
mic::data_io::MNISTMatrixImporter* importer;


/*!
 * \brief Function for testing ImageEncoder/WindowImage2D classes.
 * \author tkornuta
 */
void image_encoder_and_visualization_test (void) {
	// Create temp variables.
	mic::types::MatrixXfPtr current_image (new mic::types::MatrixXf(28,28));
	mic::types::MatrixXfPtr reconstructed_image (new mic::types::MatrixXf(28,28));

	// Set images to display.
	w2d_input->setMatrixPointer(current_image);
	w2d_reconstruction->setMatrixPointer(reconstructed_image);

	mic::encoders::MatrixXfMatrixXfEncoder encoder(28*28, 28, 28);

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
				MatrixXfUintPair sample = importer->getRandomSample();

				// Copy to image pointer.
				(*current_image) = (*(sample.first));

				// Encode the selected image into SDR.
				mic::types::MatrixXfPtr sdr = encoder.encodeSample(sample.first);

				// Change a single element of SDR.
				(*sdr)(2)=1;

				// Decode SDR.
				mic::types::MatrixXfPtr decoded_sample = encoder.decodeSample(sdr);

				// Copy to image pointer.
				(*reconstructed_image) = (*(decoded_sample));

				// Change a single element of reconstruction.
				(*(reconstructed_image))(0)=1;

			}//: end of critical section

		}//: if

		// Sleep.
		APP_SLEEP();
	}//: while

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

	// Parse parameters.
	PARAM_SERVER->parseApplicationParameters(argc, argv);

	// Load dataset.
	importer = new mic::data_io::MNISTMatrixImporter();
	// Manually set paths. DEPRICATED!
	//importer->setDataFilename("/Users/tkornut/Documents/workspace/machine-intelligence-core/data/mnist/train-images-idx3-ubyte");
	//importer->setLabelsFilename("/Users/tkornut/Documents/workspace/machine-intelligence-core/data/mnist/train-labels-idx1-ubyte");

	// Set parameters of all property-tree derived objects - USER independent part.
	PARAM_SERVER->loadPropertiesFromConfiguration();

	// Initialize property-dependent variables of all registered property-tree objects - USER dependent part.
	PARAM_SERVER->initializePropertyDependentVariables();

	// Import data from datasets.
	if (!importer->importData())
		return -1;

	// Initialize GLUT! :]
	VGL_MANAGER->initializeGLUT(argc, argv);

	// Create two visualization windows - in the same, main thread :]
	w2d_input = new WindowMatrix2D("Input image", 512, 512, 0, 0);
	w2d_reconstruction = new WindowMatrix2D("Reconstructed image", 512, 512, 512, 0);

	boost::thread test_thread(boost::bind(&image_encoder_and_visualization_test));

	// Start visualization thread.
	VGL_MANAGER->startVisualizationLoop();

	// End test thread.
	test_thread.join();
	LOG(LINFO) << "Threads joined. Ending application";
}//: main

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

#include <opengl/visualization/WindowManager.hpp>
#include <opengl/visualization/WindowRGBTensor.hpp>
using namespace mic::opengl::visualization;

/// Window displaying the image.
WindowRGBTensor<float>* w_batch;

mic::types::TensorPtr<float> readBMP(const std::string& filename_)
{
	   static constexpr size_t HEADER_SIZE = 54;

	    std::ifstream bmp(filename_, std::ios::binary);

	    // Read the header.
	    std::array<char, HEADER_SIZE> header;
	    bmp.read(header.data(), header.size());

	    // Get parameters.
	    // https://www.gamedev.net/resources/_/technical/game-programming/how-to-load-a-bitmap-r1966
	    // From File information header.
	    uint32_t bfSize = *reinterpret_cast<uint32_t *>(&header[2]);
	    uint32_t bfOffBits = *reinterpret_cast<uint32_t *>(&header[10]);
	    // From Bitmap information header.
	    uint32_t biWidth = *reinterpret_cast<uint32_t *>(&header[18]);
	    uint32_t biHeight = *reinterpret_cast<uint32_t *>(&header[22]);
	    uint16_t biBitCount = *reinterpret_cast<uint16_t *>(&header[28]);


	    std::cout << "fileSize: " << bfSize << std::endl;
	    std::cout << "dataOffset: " << bfOffBits << std::endl;
	    std::cout << "width: " << biWidth << std::endl;
	    std::cout << "height: " << biHeight << std::endl;
	    std::cout << "depth: " << biBitCount << "-bit" << std::endl;

	    // Skip the rest of header.
	    std::vector<char> rest(bfOffBits - HEADER_SIZE);
	    bmp.read(rest.data(), rest.size());

	    // Read the "pixels".
	    std::vector<char> img(bfSize - bfOffBits);
	    bmp.read(img.data(), img.size());

	    // padWidth is the width of the image plus the extra padding.
	    // Initially set both to the width of the image.
	    size_t padWidth= (size_t)(3*biWidth);

	    // And add any extra space to bring each line to a DWORD boundary
	    while(padWidth%4!=0) {
	       padWidth++;
	    }
	    std::cout << "padWidth: " << padWidth << std::endl;

	    // Prepare output tensor.
	    mic::types::TensorPtr<float> ptr = MAKE_TENSOR_PTR(float, biHeight, biWidth, 3 );
	    ptr->zeros();
	    // Get data.
	    float* data_ptr = ptr->data();


	    char temp = 0;
	    // Iterate through rows...
	    for (size_t h =0; h < biHeight; h++){
	    	// ... and cols.
	        for (size_t w =0; w < padWidth; w+=3) {
	        	 // Skip the padding.
	        	 if (w >= 3*biWidth)
	        		 continue;
	        	size_t i = h*padWidth + w;
/*	 	    	std::cout << "h = " << h << "w = " << w << "i = " << i ;
	 	        std::cout << " R: " << int(img[i+2] & 0xff) << " G: " << int(img[i+1] & 0xff) << " B: " << int(img[i] & 0xff) << std::endl;
*/
	        	// Red
	           	//(*ptr)({biHeight - h,w/3,0}) = (int(img[i + 2] & 0xff)) / (255.0);
	        	data_ptr[biWidth - h + w * biHeight/3] = (int(img[i + 2] & 0xff)) / (255.0);
	           	// Green
	           	//(*ptr)({biHeight - h,w/3,1}) = (int(img[i + 1] & 0xff)) / (255.0);
	        	data_ptr[biWidth - h + w * biHeight/3 + 1*biWidth*biHeight] = (int(img[i + 1] & 0xff)) / (255.0);
	           	// Blue
	           	//(*ptr)({biHeight - h,w/3,2}) = (int(img[i] & 0xff)) / (255.0);
	        	data_ptr[biWidth - h + w * biHeight/3 + 2*biWidth*biHeight] = (int(img[i + 0] & 0xff)) / (255.0);

	        }
	    }

   // std::cout << "\n \n ptr = " << (*ptr) << std::endl;
    return ptr;
}

/*!
 * \brief Function for testing ImageEncoder/WindowImage2D classes.
 * \author tkornuta
 */
void test_thread_body (void) {

	mic::types::TensorPtr<float> ptr = readBMP("../data/lena.bmp");


	// Generate a batch.
	/*mic::types::MNISTBatch batch;
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
	}//: for*/

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
				//mic::types::MNISTSample sample = batch.getRandomSample();

				// Set sample to be displayed.
				w_batch->setSampleUnsynchronized(ptr);
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
	w_batch = new WindowRGBTensor<float>("Batch", RGB::Chan_RGB, RGB::Norm_None, RGB::Grid_Batch, 0, 0, 512, 512);

	boost::thread test_thread(boost::bind(&test_thread_body));

	// Start visualization thread.
	VGL_MANAGER->startVisualizationLoop();

	LOG(LINFO) << "Waiting for threads to join...";
	// End test thread.
	test_thread.join();
	LOG(LINFO) << "Threads joined - ending application";
}//: main

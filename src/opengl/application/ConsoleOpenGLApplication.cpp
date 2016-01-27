/*!
 * \file ConsoleOpenGLApplication.cpp
 * \brief 
 * \author tkornut
 * \date Dec 30, 2015
 */

#include <opengl/application/ConsoleOpenGLApplication.hpp>

#include <iostream>
#include <fstream>

#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>

namespace mic {
namespace opengl {
namespace application {

ConsoleOpenGLApplication::ConsoleOpenGLApplication(std::string node_name_) : Application(node_name_)
{

}


void ConsoleOpenGLApplication::run() {
	// Run the processing thread.
	boost::thread processing_thread(boost::bind(&ConsoleOpenGLApplication::processingThread, this));

	// Start main OpenGL loop.
	VGL_MANAGER->startVisualizationLoop();
	LOG(LINFO) << "OpenGL thread terminated...";

	// Wait for the processing thread to end.
	processing_thread.join();
	LOG(LINFO) << "Processing thread terminated...";

}


} /* namespace applications */
} /* namespace opengl */
} /* namespace mic */

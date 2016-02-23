/*!
 * \file WindowFloatCollectorChart.cpp
 * \brief 
 * \author tkornut
 * \date Feb 22, 2016
 */

#include <opengl/visualization/WindowManager.hpp>
#include <logger/Log.hpp>
#include <opengl/visualization/WindowFloatCollectorChart.hpp>


namespace mic {
namespace opengl {
namespace visualization {

WindowFloatCollectorChart::WindowFloatCollectorChart(std::string name_, unsigned int height_, unsigned int width_, unsigned int position_x_ , unsigned int position_y_) :
	Window(name_, height_, width_, position_x_, position_y_),
	collector_ptr(nullptr)
{
	// Set default values of variables.
	zoom_factor = 1.0f;

	chart_width = 0.9;
	chart_height = 0.45;
	label_offset_x = 50;
	label_offset_y = 20;
	number_of_horizontal_bars = 10;

	// Reset data.
	//...

	// Register key handlers.
	registerKeyhandler('<', "< - zoom in (upscale chart)", &WindowFloatCollectorChart::keyhandlerZoomIn, this);
	registerKeyhandler('>', "> - zoom out (downscale chart)", &WindowFloatCollectorChart::keyhandlerZoomOut, this);
	registerKeyhandler('/', "/ - reset zoom (set zoom_factor to default: 1.0)", &WindowFloatCollectorChart::keyhandlerZoomReset, this);

	// Register window!
	VGL_MANAGER->registerWindow(this);
}



void WindowFloatCollectorChart::displayHandler(void) {
	LOG(LTRACE) << "WindowFloatCollectorChart::Display handler of window " << glutGetWindow();
	// Enter critical section.
//	APP_DATA_SYNCHRONIZATION_SCOPED_LOCK();

	// Clear buffer.
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Check whether the collector pointer is set.
	if (collector_ptr != nullptr){

		// Refresh the chart window.
		redrawMainChartWindow();

		// Get access to data containers.
		mic::data_io::DataContainers<std::string, float> containers = collector_ptr->getContainers();

		std::cout << "containers.size =" << containers.size();
		// Refresh charts one by one.
		unsigned int label_x_offset = 10;
		unsigned int label_y_offset = 15;
		// Iterate through the data containers and display them 1 by 1.
		for(mic::data_io::DataContainerIt<std::string, float> it = containers.begin(); it != containers.end(); it++, label_y_offset+=15) {
			// Get vector.
			std::string l =  it->first;
			// Get data.
			std::vector<float> v = (it->second)->data;
			// Get display properties.
			color_rgba c = (it->second)->color;
			float line_width = (it->second)->line_width;
			// Draw chart associated with given data container.
			redrawSingleContainer(l, v, c, line_width, label_x_offset, label_y_offset);
		}//: end
	}//: if !null

	// Swap buffers.
	glutSwapBuffers();

	// End of critical section.
}


void WindowFloatCollectorChart::setDataCollectorPtr(mic::data_io::DataCollectorPtr<std::string, float> collector_ptr_) {
	// Enter critical section.
	APP_DATA_SYNCHRONIZATION_SCOPED_LOCK();

	collector_ptr = collector_ptr_;
	// End of critical section.
}


void WindowFloatCollectorChart::redrawMainChartWindow() {
	LOG(LTRACE)<< "WindowFloatCollectorChart::refreshChart";

	int acc_x = (int)(width * ((1.0 - chart_width)/2.0));
	int acc_y = (int)(label_offset_y);
	int acc_w = (int)(width * chart_width);
	int acc_h = (int)(height * chart_height);

	// Draw chart boundary.
	glLineWidth(1.0f);
	draw_rectangle(acc_x, acc_y, acc_h, acc_w, 0.7f, 0.7f, 0.7f, 1.0f);
	draw_rectangle(acc_x, acc_y + acc_h, acc_h, acc_w, 0.7f, 0.7f, 0.7f, 1.0f);

	// Draw  horizontal bars and print labels on both sides..
	for (int i = -number_of_horizontal_bars; i <= number_of_horizontal_bars; i++) {
		float h = (float)i/(float)number_of_horizontal_bars;
		// Print labels.
		char value[10];
		sprintf(value, "%d%%", (unsigned)(float)round((100.0 * h)));
		draw_text(acc_x - 30, acc_y + acc_h - (int)(h * acc_h) + 2, value, 1.0f, 1.0f, 1.0f, 0.5f, GLUT_BITMAP_HELVETICA_10);
		draw_text(acc_x + acc_w + 5, acc_y + acc_h - (int)(h * acc_h) + 2, value, 1.0f, 1.0f, 1.0f, 0.5f, GLUT_BITMAP_HELVETICA_10);
		// Draw horizontal lines.
		glColor4f(0.5f, 0.5f, 0.5f, 0.5f);
		glBegin(GL_LINES);
		glVertex2i(acc_x, acc_y + acc_h - (int)(h * acc_h));
		glVertex2i(acc_x + acc_w, acc_y + acc_h - (int)(h * acc_h));
		glEnd();
	}//: for
}


void WindowFloatCollectorChart::redrawSingleContainer(std:: string & label_, std::vector<float> & data_, mic::types::color_rgba color_, float line_width_, unsigned short label_x_offset_, unsigned short label_y_offset_) {
	LOG(LTRACE)<< "WindowFloatCollectorChart::refreshSingleChart";

	int acc_x = (int)(width * ((1.0 - chart_width)/2.0));
	int acc_y = (int)(label_offset_y);
	int acc_w = (int)(width * chart_width);
	int acc_h = (int)(height * chart_height);

	// Set line width.
	glLineWidth(line_width_);
	glBegin(GL_LINE_STRIP);
	// Draw data.
	for (int i = 0; i < chart_width * (width); i++) {

		if (data_.size() - 1 - (unsigned)(int)round(i * zoom_factor) < data_.size()) {

			//color_rgba c = map_value_to_color((float)(data_[data_.size() - 1 - (unsigned)(int)round(i * zoom_factor)]), 0.0f, 1.0f, COLORMAP_SEISMIC);
			glColor4f(color_.r/255.0f, color_.g/255.0f, color_.b/255.0f, color_.a/255.0f);
			glVertex2i(acc_x + acc_w - (int)(i), acc_y + acc_h - (int)(data_[data_.size() - 1 - (unsigned)(int)(i * zoom_factor)] * acc_h));
		}

	}
	glEnd();

	// Print label.
	char value[100];
	if (data_.size() > 0) {
		sprintf(value, "%s: %.1f%%", label_.c_str(), (float)((100.0 * data_[data_.size() - 1])));
	} else {
		// If there are no data.
		sprintf(value, "%s: -", label_.c_str());
	}
	draw_text(acc_x + label_x_offset_, acc_y + acc_h + label_y_offset_, value, color_.r/255.0f, color_.g/255.0f, color_.b/255.0f, color_.a/255.0f, GLUT_BITMAP_HELVETICA_10);
}

} /* namespace visualization */
} /* namespace opengl */
} /* namespace mic */

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
 * \file WindowDataCollectorChart.hpp
 * \brief 
 * \author tkornut
 * \date Feb 22, 2016
 */

#ifndef SRC_OPENGL_VISUALIZATION_WINDOWFLOATCOLLECTORCHART_HPP_
#define SRC_OPENGL_VISUALIZATION_WINDOWFLOATCOLLECTORCHART_HPP_

#include <opengl/visualization/Window.hpp>

#include <types/image_types.hpp>

#include <data_io/DataCollector.hpp>

namespace mic {
namespace opengl {
namespace visualization {

/*!
 * \brief OpenGL-based window responsible for displaying data collected in DataCollector objects in the form of a chart.
 * \tparam LABEL_TYPE Template parameter denoting the label type.
 * \@tparam eT Precission (float/double) (DEFAULT=float).
 * \author tkornuta
 */
template <typename eT=float>
class WindowCollectorChart: public Window {
public:
	/*!
	 * Constructor.
	 */
	WindowCollectorChart(std::string name_ = "Chart",
			unsigned int position_x_ = 0, unsigned int position_y_ = 0,
			unsigned int width_ = 1024, unsigned int height_ = 256) :
		Window(name_, position_x_, position_y_, width_, height_),
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
		registerKeyhandler('<', "< - zoom in (upscale chart)", &WindowCollectorChart::keyhandlerZoomIn, this);
		registerKeyhandler('>', "> - zoom out (downscale chart)", &WindowCollectorChart::keyhandlerZoomOut, this);
		registerKeyhandler('/', "/ - reset zoom (set zoom_factor to default: 1.0)", &WindowCollectorChart::keyhandlerZoomReset, this);

		// Register window!
		VGL_MANAGER->registerWindow(this);
	}


	/*!
	 * Destructor. Empty for now.
	 */
	virtual ~WindowCollectorChart() { }

	/*!
	 * Refreshes the content of the window.
	 */
	void displayHandler(void) {
		LOG(LTRACE) << "WindowFloatCollectorChart::Display handler of window " << glutGetWindow();
		// Enter critical section.
		APP_DATA_SYNCHRONIZATION_SCOPED_LOCK();

		// Clear buffer.
	    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Check whether the collector pointer is set.
		if (collector_ptr != nullptr){

			// Refresh the chart window.
			redrawMainChartWindow();

			// Get access to data containers.
			mic::data_io::DataContainers<std::string, eT> containers = collector_ptr->getContainers();

			// Refresh charts one by one.
			unsigned int label_x_offset = 10;
			unsigned int label_y_offset = 15;
			// Iterate through the data containers and display them 1 by 1.
			for(mic::data_io::DataContainerIt<std::string, eT> it = containers.begin(); it != containers.end(); it++, label_y_offset+=15) {
				// Get vector.
				std::string l =  it->first;

				// Get data.
				std::vector<eT> vector = (it->second)->data;
				// Get min-max values.
				eT min_value = (it->second)->min_value;
				eT max_value = (it->second)->max_value;

				// Get display properties.
				color_rgba c = (it->second)->color;
				eT line_width = (it->second)->line_width;

				// If do not fits in image - Move labels to next "column".
				//std::cout << glutGet((GLenum) GLUT_WINDOW_HEIGHT) << std::endl;
				//std::cout << label_y_offset << std::endl;
				int acc_y = (int)(label_offset_y);
				int acc_h = (int)(height * chart_height);
				//std::cout << acc_y + acc_h + label_y_offset << std::endl;
				if (acc_y + acc_h + label_y_offset > (unsigned int) glutGet((GLenum) GLUT_WINDOW_HEIGHT)) {
					label_y_offset = 15;
					label_x_offset += 200;
				}//: if

				// Draw chart associated with given data container.
				redrawSingleContainer(l, vector, min_value, max_value, c, line_width, label_x_offset, label_y_offset);
			}//: end
		}//: if !null

		// Swap buffers.
		glutSwapBuffers();

		// End of critical section.
	}

	/*!
	 * Sets data collector.
	 * @param collector_ptr_ Data collector.
	 */
	void setDataCollectorPtr(mic::data_io::DataCollectorPtr<std::string, eT> collector_ptr_) {
		// Enter critical section.
		APP_DATA_SYNCHRONIZATION_SCOPED_LOCK();

		collector_ptr = collector_ptr_;
		// End of critical section.
	}

	/*!
	 * Redraws main chart window.
	 */
	void redrawMainChartWindow() {
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
		for (int i = 0; i <= number_of_horizontal_bars; i++) {
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

	/*!
	 * Redraws single container.
	 * @param label_ Label of data.
	 * @param data_ Vector containing data.
	 * @param min_value_ Min value.
	 * @param max_value_ Max value.
	 * @param color_ Colour of line/label.
	 * @param line_width_ Line width.
	 * @param label_x_offset_ Label x offset.
	 * @param label_y_offset_ Label y offset.
	 */
	void redrawSingleContainer(std:: string & label_, std::vector<eT> & data_, eT min_value_, eT max_value_, mic::types::color_rgba color_, eT line_width_, unsigned short label_x_offset_, unsigned short label_y_offset_) {
		LOG(LTRACE)<< "WindowFloatCollectorChart::refreshSingleChart";

		int acc_x = (int)(width * ((1.0 - chart_width)/2.0));
		int acc_y = (int)(label_offset_y);
		int acc_w = (int)(width * chart_width);
		int acc_h = (int)(height * chart_height);

		// Set line width.
		glLineWidth(line_width_);
		glBegin(GL_LINE_STRIP);
		eT value;
		// Special case: division by 0. Place values in the "middle" (0.5).
		eT diff = max_value_ - min_value_;
		if (diff == 0.0){
			diff = 0.5;
			min_value_ = 0.0;
		}
		// Draw data.
		for (int i = 0; i < chart_width * (width); i++) {

			if (data_.size() - 1 - (size_t)round(i * zoom_factor) < data_.size()) {
				value = data_[data_.size() - 1 - (size_t)(i * zoom_factor)];
				// Scale the value.
				value = (value - min_value_)/(diff);
				glColor4f(color_.r/255.0f, color_.g/255.0f, color_.b/255.0f, color_.a/255.0f);
				glVertex2i(acc_x + acc_w - (int)(i), acc_y + acc_h - (int)(value * acc_h));
			}

		}
		glEnd();

		// Print label.
		char str_value[100] = "-";
		if (data_.size() > 0) {
			value = data_[data_.size() - 1];
			sprintf(str_value, "%s: %.2f  (%.2f : %.2f)", label_.c_str(), value, min_value_, max_value_);
		} else {
			// If there are no data.
			sprintf(str_value, "%s: -", label_.c_str());
		}
		draw_text(acc_x + label_x_offset_, acc_y + acc_h + label_y_offset_, str_value, color_.r/255.0f, color_.g/255.0f, color_.b/255.0f, color_.a/255.0f, GLUT_BITMAP_HELVETICA_10);
	}

private:

	/// Data collector associated with .
	mic::data_io::DataCollectorPtr<std::string, eT> collector_ptr;

	/// Zoom factor - used for zoomin in and out in the chart window.
	float zoom_factor;

	/// Chart width.
	double chart_width;

	/// Chart width.
	double chart_height;

	/// Label offset x.
	double label_offset_x;

	/// Label offset y.
	double label_offset_y;

	/// Number of horizontal bars in chart.
	double number_of_horizontal_bars;

	/*!
	 *  Keyhandler: zoom in (upscale chart).
	 */
	void keyhandlerZoomIn(void) {
		zoom_factor = zoom_factor / 1.1f;
	}

	/*!
	 *  Keyhandler: zoom out (downscale chart).
	 */
	void keyhandlerZoomOut(void) {
		zoom_factor = zoom_factor * 1.1f;
	}

	/*!
	 *  Keyhandler: reset zoom (set zoom_factor to default: 1.0).
	 */
	void keyhandlerZoomReset(void) {
		zoom_factor = 1.0f;
	}

};

// Typedef for compatibility.
//typedef WindowCollectorChart<float> WindowCollectorFloatChart;


} /* namespace visualization */
} /* namespace opengl */
} /* namespace mic */

#endif /* SRC_OPENGL_VISUALIZATION_WINDOWFLOATCOLLECTORCHART_HPP_ */

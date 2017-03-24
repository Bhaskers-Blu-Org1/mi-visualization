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

#include <data_utils/colormap.hpp>
using namespace mic::data_utils;

#include <data_io/DataCollector.hpp>

namespace mic {
namespace opengl {
namespace visualization {

/*!
 * \brief OpenGL-based window reposponsible for displaying data collected in DataCollector objects in the form of a chart.
 * \tparam LABEL_TYPE Template parameter denoting the label type.
 * \tparam DATA_TYPE Template parameter denoting basic used datatype.
 * \author tkornuta
 */
//template <class LABEL_TYPE, class DATA_TYPE>
class WindowFloatCollectorChart: public Window {
public:
	/*!
	 * Constructor.
	 */
	WindowFloatCollectorChart(std::string name_ = "Chart", unsigned int height_ = 256, unsigned int width_ = 1024, unsigned int position_x_ = 0, unsigned int position_y_ = 0);

	/*!
	 * Destructor. Empty for now.
	 */
	virtual ~WindowFloatCollectorChart() { }

	/*!
	 * Refreshes the content of the window.
	 */
	void displayHandler(void);

	/*!
	 * Sets data collector.
	 * @param collector_ptr_ Data collector.
	 */
	void setDataCollectorPtr(mic::data_io::DataCollectorPtr<std::string, float> collector_ptr_);

	/*!
	 * Redraws main chart window.
	 */
	void redrawMainChartWindow();

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
	void redrawSingleContainer(std:: string & label_, std::vector<float> & data_, float min_value_, float max_value_, mic::types::color_rgba color_, float line_width_, unsigned short label_x_offset_, unsigned short label_y_offset_);

private:

	/// Data collector associated with .
	mic::data_io::DataCollectorPtr<std::string, float> collector_ptr;

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

//typedef WindowDataCollectorChart<std::string, float> WindowFloatCollectorChart;


} /* namespace visualization */
} /* namespace opengl */
} /* namespace mic */

#endif /* SRC_OPENGL_VISUALIZATION_WINDOWFLOATCOLLECTORCHART_HPP_ */

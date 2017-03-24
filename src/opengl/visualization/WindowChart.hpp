/*!
 * \file WindowChart.hpp
 * \brief Contains declaration of class responsible for displaying charts.
 * \author tkornuta
 * \date Nov 23, 2015
 */

#ifndef SRC_VISUALIZATION_OPENGL_WINDOWCHART_HPP_
#define SRC_VISUALIZATION_OPENGL_WINDOWCHART_HPP_

#include <opengl/visualization/Window.hpp>

#include <types/image_types.hpp>

#include<vector>
#include <string>
#include <map>

#include <boost/tuple/tuple.hpp>

namespace mic {
namespace opengl {
namespace visualization {

/*!
 * \brief Basic type storing <data, colour, line width>.
 * \author tkornuta
 */
typedef boost::tuple<std::vector<float>, mic::types::color_rgba, float> dlc_t;

/*!
 * \brief Type used char registry.
 * \author tkornuta
 */
typedef std::map<std::string, dlc_t> chart_registry_t;


/*!
 * \brief Type used in iterating/searching for in chart registry.
 * \author tkornuta
 */
typedef chart_registry_t::iterator chart_registry_it_t;



/*!
 * \brief OpenGL-based window reposponsible for displaying charts.
 * \author tkornuta/krocki
 */
class WindowChart: public Window {
public:

	/*!
	 * Constructor.
	 */
	WindowChart(std::string name_ = "Chart", unsigned int height_ = 256, unsigned int width_ = 1024, unsigned int position_x_ = 0, unsigned int position_y_ = 0);

	/*!
	 * Destructor.
	 */
	virtual ~WindowChart();

	/*!
	 * Refreshes the content of the window.
	 */
	void displayHandler(void);

	/*!
	 * Data registry - map containing pairs of labels with touples: vector of data, line width and line/label colour.
	 * Each "pair" for a different data.
	 */
	chart_registry_t data_registry;

	/*!
	 * Creates new data container for given label
	 * @param label_ Name of the container.
	 */
	void createDataContainer(std::string label_, mic::types::color_rgba color_ = mic::types::color_rgba(255, 255, 255, 180), float line_width_ = 1.0f);

	/*!
	 * Adds new value to the container.
	 * @param label_ Name of the container.
	 * @param value_ Value to be added.
	 */
	void addDataToContainer(std::string label_, float value_);

	/*!
	 * Redraws main chart window.
	 */
	void redrawMainChartWindow();

	/*!
	 * Redraws single container.
	 * @param label_ Label of data.
	 * @param data_ Vector containing data.
	 * @param color_ Colour of line/label.
	 * @param line_width_ Line width.
	 * @param label_x_offset_ Label x offset.
	 * @param label_y_offset_ Label y offset.
	 */
	void redrawSingleContainer(std:: string & label_, std::vector<float> & data_, mic::types::color_rgba color_, float line_width_, unsigned short label_x_offset_, unsigned short label_y_offset_);

private:

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
	void keyhandlerZoomIn(void);

	/*!
	 *  Keyhandler: zoom out (downscale chart).
	 */
	void keyhandlerZoomOut(void);

	/*!
	 *  Keyhandler: reset zoom (set zoom_factor to default: 1.0).
	 */
	void keyhandlerZoomReset(void);

};

} /* namespace visualization */
} /* namespace opengl */
} /* namespace mic */

#endif /* SRC_VISUALIZATION_OPENGL_WINDOWCHART_HPP_ */

/*!
 * \file WindowSequence.cpp
 * \brief Contains declaraion of WindowSequence methods
 * \author tkornuta
 * \date Nov 30, 2015
 */

#include <opengl/visualization/WindowSequence.hpp>
#include <opengl/visualization/WindowManager.hpp>

namespace mic {
namespace opengl {
namespace visualization {

WindowSequence::WindowSequence(std::string name_, unsigned int height_, unsigned int width_, unsigned int position_x_, unsigned int position_y_) :
	Window(name_, height_, width_, position_x_, position_y_)
{
	// Set variables.
	alpha = 0.8f;
	text_alpha = 1.0f;
	graph_line_width = 1.0f;

	data_point_spacing_x = 17;
	t0_time_position = 0.7f;

	visible_min_range = 0.0f;
	visible_max_range = 1.0f;

	// Reset data.

	// Register window!
	VGL_MANAGER->registerWindow(this);

}

WindowSequence::~WindowSequence() {
	// TODO Auto-generated destructor stub
}

void WindowSequence::displayHandler(void){
	LOG(LTRACE) << "WindowSequence::Display handler of window " << glutGetWindow();
	// Enter critical section.
//	APP_DATA_SYNCHRONIZATION_SCOPED_LOCK();

	// Clear buffer.
    glClearColor(0.95f, 0.95f, 0.95f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Recalculate window-size dependent variables.
	range_main_x = width - (MAIN_FRAME_X_MARGIN * 2);
	absolute_t0_time_position = (int)(t0_time_position * range_main_x + MAIN_FRAME_X_MARGIN);

	// Draw sequence window.
    draw_outer_frame();
    draw_main_frame();

    draw_input_series(input_data, 0, true, 30, -3, 0.9f, 0.0f, 0.0f, alpha, PLUS);
    draw_input_series(predicted_data, 1, true, -10, -3, 0.0f, 0.0f, 0.9f, alpha, SQUARE);
    draw_input_series(reconstructed_data, 0, false, 0, -40, 0.0f, 0.4f, 0.0f, alpha, CIRCLE);

	//draw_error_labels();
	draw_error_series(spatial_error, 0.0f, 0.4f, 0.0f, alpha);
	draw_error_series(prediction_error, 0.0f, 0.0f, 0.5f, alpha);
/*	draw_error_details();

	draw_iteration_labels();
	draw_graph_labels();

	draw_statistics(&l0);
*/
    // Swap buffers.
	glutSwapBuffers();

	// End of critical section.
}

void WindowSequence::draw_outer_frame(void) {

    // outer frame
    draw_frame(MAIN_FRAME_X_MARGIN, MAIN_FRAME_Y_MARGIN, MAIN_FRAME_X_MARGIN + range_main_x, height - MAIN_FRAME_Y_MARGIN, 0.6f, 0.6f, 0.6f, alpha);
    // sequence frame
    draw_frame(MAIN_FRAME_X_MARGIN, MAIN_FRAME_Y_MARGIN, MAIN_FRAME_X_MARGIN + range_main_x, height - (MAIN_FRAME_Y_MARGIN + ERROR_FRAME_HEIGHT + GRAPH_0_FRAME_HEIGHT + GRAPH_1_FRAME_HEIGHT + GRAPH_2_FRAME_HEIGHT), 0.6f, 0.6f, 0.6f, alpha);
    // error frame
    draw_frame(MAIN_FRAME_X_MARGIN, MAIN_FRAME_Y_MARGIN + range_main_y, MAIN_FRAME_X_MARGIN + range_main_x, height - (MAIN_FRAME_Y_MARGIN + GRAPH_0_FRAME_HEIGHT + GRAPH_1_FRAME_HEIGHT + GRAPH_2_FRAME_HEIGHT), 0.6f, 0.6f, 0.6f, alpha);
    // graph 0 frame
    draw_frame(MAIN_FRAME_X_MARGIN, MAIN_FRAME_Y_MARGIN + range_main_y + ERROR_FRAME_HEIGHT, MAIN_FRAME_X_MARGIN + range_main_x, height - (MAIN_FRAME_Y_MARGIN + GRAPH_1_FRAME_HEIGHT + GRAPH_2_FRAME_HEIGHT), 0.6f, 0.6f, 0.6f, alpha);
    // graph 1 frame
    draw_frame(MAIN_FRAME_X_MARGIN, MAIN_FRAME_Y_MARGIN + range_main_y + ERROR_FRAME_HEIGHT + GRAPH_0_FRAME_HEIGHT, MAIN_FRAME_X_MARGIN + range_main_x, height - (MAIN_FRAME_Y_MARGIN + GRAPH_2_FRAME_HEIGHT), 0.6f, 0.6f, 0.6f, alpha);
    // graph 2 frame
    draw_frame(MAIN_FRAME_X_MARGIN, MAIN_FRAME_Y_MARGIN + range_main_y + ERROR_FRAME_HEIGHT + GRAPH_0_FRAME_HEIGHT + GRAPH_1_FRAME_HEIGHT, MAIN_FRAME_X_MARGIN + range_main_x, height - (MAIN_FRAME_Y_MARGIN), 0.6f, 0.6f, 0.6f, alpha);

}

void WindowSequence::draw_main_frame(void) {

    //y labels
    glLineWidth(0.2f);

    range_main_y = height - (MAIN_FRAME_Y_MARGIN * 2) - (ERROR_FRAME_HEIGHT + GRAPH_0_FRAME_HEIGHT + GRAPH_1_FRAME_HEIGHT + GRAPH_2_FRAME_HEIGHT);

    for (int i = 0; i <= MAIN_FRAME_Y_LABELS; i++) {

    	float current_label = (float)range_main_y/(float)MAIN_FRAME_Y_LABELS * (float)i;
    	char text_label[16];

    	visible_range = (float)(visible_max_range - visible_min_range);

		sprintf(text_label, "%.2f", visible_range/(float)MAIN_FRAME_Y_LABELS * (float)i + visible_min_range);

		draw_text(MAIN_FRAME_X_MARGIN - 30,
				height - (int)(current_label + MAIN_FRAME_Y_MARGIN +
				ERROR_FRAME_HEIGHT + GRAPH_0_FRAME_HEIGHT + GRAPH_1_FRAME_HEIGHT + GRAPH_2_FRAME_HEIGHT) + 4,
				text_label, 0.6f, 0.6f, 0.6f, text_alpha, GLUT_BITMAP_HELVETICA_10);

		glColor4f(0.8f, 0.8f, 0.8f, alpha);

    	glBegin(GL_LINES);
    	glVertex2i(MAIN_FRAME_X_MARGIN, height - (int)(current_label + MAIN_FRAME_Y_MARGIN + ERROR_FRAME_HEIGHT + GRAPH_0_FRAME_HEIGHT + GRAPH_1_FRAME_HEIGHT + GRAPH_2_FRAME_HEIGHT));
    	glVertex2i(MAIN_FRAME_X_MARGIN + range_main_x, height - (int)(current_label + MAIN_FRAME_Y_MARGIN + ERROR_FRAME_HEIGHT + GRAPH_0_FRAME_HEIGHT + GRAPH_1_FRAME_HEIGHT + GRAPH_2_FRAME_HEIGHT));
    	glEnd();

    }

	//x labels
    glLineWidth(0.2f);

    glBegin(GL_LINES);
    for (unsigned t = 0; t < input_data.size(); t++) {

    	if (absolute_t0_time_position - t * data_point_spacing_x > MAIN_FRAME_X_MARGIN) {

    		if (t % 2 == 0)
    			glColor4f(0.6f, 0.6f, 0.6f, alpha);
    		else
    			glColor4f(0.9f, 0.9f, 0.9f, alpha);

			glVertex2i((int)(absolute_t0_time_position - t * data_point_spacing_x), height - (int)(MAIN_FRAME_Y_MARGIN));
			glVertex2i((int)(absolute_t0_time_position - t * data_point_spacing_x), MAIN_FRAME_Y_MARGIN);
    	}

    }
    glEnd();
}


void WindowSequence::draw_error_series(std::vector<float> series, float r, float g, float b, float a) {


    //draw in the error frame
    glLineWidth(graph_line_width);
    glColor4f(r, g, b, a);
    glBegin(GL_LINE_STRIP);
    for (unsigned t = 0; t < series.size(); t++)
    	if (absolute_t0_time_position - t * data_point_spacing_x > MAIN_FRAME_X_MARGIN) {
    		glVertex2i((int)(absolute_t0_time_position - t * data_point_spacing_x), height - (int)(((series[series.size() - t - 1]) * ERROR_FRAME_HEIGHT) + MAIN_FRAME_Y_MARGIN + GRAPH_0_FRAME_HEIGHT + GRAPH_1_FRAME_HEIGHT + GRAPH_2_FRAME_HEIGHT));
    	}
    glEnd();

}

void WindowSequence::draw_input_series(std::vector<float> series, int x_offset, bool display_text, int text_offset_x, int text_offset_y, float r, float g, float b, float a, mark m) {

    //draw in the main frame
    glLineWidth(graph_line_width);

    glColor4f(r, g, b, a);

    glBegin(GL_LINE_STRIP);

    for (int t = 0; t < (int)series.size(); t++) {
    	if (absolute_t0_time_position - (t - x_offset) * data_point_spacing_x > MAIN_FRAME_X_MARGIN) {
    		glVertex2i((int)(absolute_t0_time_position - (t - x_offset) * data_point_spacing_x), height - (int)((series[series.size() - (unsigned)t - 1] - visible_min_range)/(visible_range) * range_main_y + MAIN_FRAME_Y_MARGIN + ERROR_FRAME_HEIGHT + GRAPH_0_FRAME_HEIGHT + GRAPH_1_FRAME_HEIGHT + GRAPH_2_FRAME_HEIGHT));
    	}
    }
    glEnd();

    char label_data[32];
    float data_point_size = data_point_spacing_x/4.0f + 1.0f;
    float line_width = (float)data_point_spacing_x/20.0f;

    for (int t = 0; t < (int)series.size(); t++) {

    	if (absolute_t0_time_position - (t - x_offset) * data_point_spacing_x > MAIN_FRAME_X_MARGIN) {

    		draw_mark(m, (int)(absolute_t0_time_position - (t - x_offset) * data_point_spacing_x),
    			height - (int)((series[series.size() - (unsigned)t - 1] - visible_min_range)/(visible_range) * range_main_y +
    			MAIN_FRAME_Y_MARGIN + ERROR_FRAME_HEIGHT + GRAPH_0_FRAME_HEIGHT + GRAPH_1_FRAME_HEIGHT + GRAPH_2_FRAME_HEIGHT),
    			data_point_size, line_width, r, g, b, a);
    		if (display_text) {
				sprintf(label_data, "%.2f", (float)series[series.size() - (unsigned)t - 1]);
	     		draw_text((int)(absolute_t0_time_position - (t - x_offset) * data_point_spacing_x) - text_offset_x,
	     		 	height - (int)((series[series.size() - (unsigned)t - 1] - visible_min_range)/(visible_range) * range_main_y +
	     		 	MAIN_FRAME_Y_MARGIN + ERROR_FRAME_HEIGHT + GRAPH_0_FRAME_HEIGHT + GRAPH_1_FRAME_HEIGHT + GRAPH_2_FRAME_HEIGHT + text_offset_y),
	     		 	label_data, r, g, b, a/2.0f, GLUT_BITMAP_HELVETICA_10);
     		}
    	}


    }

}


} /* namespace visualization */
} /* namespace opengl */
} /* namespace mic */

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
      Window(name_, height_, width_, position_x_, position_y_) {
        disabled = true; // make sure we don't draw anything until the parameters are self-consistent
        // Set variables.
        alpha = 0.8f;
        text_alpha = 1.0f;
        graph_line_width = 1.0f;

        data_point_spacing_x = 17;
        t0_time_position = 0.9f;

        visible_min_range = -0.1f;
        visible_max_range = 1.1f;

        // Reset data.

        // Register window!
        VGL_MANAGER->registerWindow(this);

      }

      WindowSequence::~WindowSequence() {
        // TODO Auto-generated destructor stub
      }

      void WindowSequence::displayHandler(void) {
        if (disabled) return; // don't let the windows get displayed until we set the RIGHT parameters!
        LOG(LTRACE) << "WindowSequence::Display handler of window " << glutGetWindow();
        // Enter critical section.
        //	APP_DATA_SYNCHRONIZATION_SCOPED_LOCK();

        // Clear buffer.
        glClearColor(0.95f, 0.95f, 0.95f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Recalculate window-size dependent variables.
        range_main_x = width - (MAIN_FRAME_X_MARGIN * 2);
        absolute_t0_time_position = (int) (t0_time_position * range_main_x + MAIN_FRAME_X_MARGIN);

        // Draw sequence window.
        draw_outer_frame();
        draw_main_frame();

        draw_iteration_labels();

        draw_input_series(input_data, 0, true, 30, -3, 0.9f, 0.0f, 0.0f, alpha, PLUS);
        draw_input_series(predicted_data, 1, true, -10, -3, 0.0f, 0.0f, 0.9f, alpha, SQUARE);
        draw_input_series(reconstructed_data, 0, false, 0, -40, 0.0f, 0.4f, 0.0f, alpha, CIRCLE);

        add_key_entry(0, "Input data", 0.0, -10, 0.9f, 0.0f, 0.0f, alpha, PLUS);
        add_key_entry(0, "Reconstructed data", 0.25, -10, 0.0f, 0.4f, 0.0f, alpha, CIRCLE);
        add_key_entry(0, "Predicted data", 0.55, -10, 0.0f, 0.0f, 0.9f, alpha, SQUARE);

        draw_error_series(spatial_error, 0.0f, 0.4f, 0.0f, alpha);
        draw_error_series(prediction_error, 0.0f, 0.0f, 0.5f, alpha);
        draw_error_labels();
        add_key_entry(1, "spatial error", 0.2, -10, 0.0f, 0.4f, 0.0f, alpha, NO_MARK);
        add_key_entry(1, "prediction error", 0.5, -10, 0.0f, 0.0f, 0.5f, alpha, NO_MARK);

        draw_reconstructions(alpha); //the very bottom one that represents the slider

        // Swap buffers.
        glutSwapBuffers();

        // End of critical section.
      }

      void WindowSequence::draw_outer_frame(void) {

        // outer frame
        draw_frame(MAIN_FRAME_X_MARGIN, MAIN_FRAME_Y_MARGIN, MAIN_FRAME_X_MARGIN + range_main_x, height - MAIN_FRAME_Y_MARGIN, 0.6f, 0.6f, 0.6f, alpha);
        // sequence frame
        draw_frame(MAIN_FRAME_X_MARGIN, MAIN_FRAME_Y_MARGIN, MAIN_FRAME_X_MARGIN + range_main_x, height - (MAIN_FRAME_Y_MARGIN + BUFFER_HEIGHT + ERROR_FRAME_HEIGHT + BUFFER_HEIGHT + GRAPH_0_FRAME_HEIGHT + GRAPH_1_FRAME_HEIGHT + GRAPH_2_FRAME_HEIGHT), 0.6f, 0.6f, 0.6f, alpha);
        // error frame
        draw_frame(MAIN_FRAME_X_MARGIN, MAIN_FRAME_Y_MARGIN + range_main_y + BUFFER_HEIGHT, MAIN_FRAME_X_MARGIN + range_main_x, height - (MAIN_FRAME_Y_MARGIN + BUFFER_HEIGHT + GRAPH_0_FRAME_HEIGHT + GRAPH_1_FRAME_HEIGHT + GRAPH_2_FRAME_HEIGHT), 0.6f, 0.6f, 0.6f, alpha);
        // graph 0 frame
        draw_frame(MAIN_FRAME_X_MARGIN, MAIN_FRAME_Y_MARGIN + range_main_y + BUFFER_HEIGHT + ERROR_FRAME_HEIGHT + BUFFER_HEIGHT, MAIN_FRAME_X_MARGIN + range_main_x, height - (MAIN_FRAME_Y_MARGIN + GRAPH_1_FRAME_HEIGHT + GRAPH_2_FRAME_HEIGHT), 0.6f, 0.6f, 0.6f, alpha);
        // graph 1 frame
        draw_frame(MAIN_FRAME_X_MARGIN, MAIN_FRAME_Y_MARGIN + range_main_y + BUFFER_HEIGHT + ERROR_FRAME_HEIGHT + BUFFER_HEIGHT + GRAPH_0_FRAME_HEIGHT, MAIN_FRAME_X_MARGIN + range_main_x, height - (MAIN_FRAME_Y_MARGIN + GRAPH_2_FRAME_HEIGHT), 0.6f, 0.6f, 0.6f, alpha);
        // graph 2 frame
        draw_frame(MAIN_FRAME_X_MARGIN, MAIN_FRAME_Y_MARGIN + range_main_y + BUFFER_HEIGHT + ERROR_FRAME_HEIGHT + BUFFER_HEIGHT + GRAPH_0_FRAME_HEIGHT + GRAPH_1_FRAME_HEIGHT, MAIN_FRAME_X_MARGIN + range_main_x, height - (MAIN_FRAME_Y_MARGIN), 0.6f, 0.6f, 0.6f, alpha);

      }

      void WindowSequence::draw_main_frame(void) {
        //y labels
        glLineWidth(0.2f);
        range_main_y = height - (MAIN_FRAME_Y_MARGIN * 2) - (BUFFER_HEIGHT + ERROR_FRAME_HEIGHT + BUFFER_HEIGHT + GRAPH_0_FRAME_HEIGHT + GRAPH_1_FRAME_HEIGHT + GRAPH_2_FRAME_HEIGHT);
        for (int i = 0; i <= MAIN_FRAME_Y_LABELS; i++) {
          float current_label = (float) range_main_y / (float) MAIN_FRAME_Y_LABELS * (float) i;
          char text_label[16];
          visible_range = (float) (visible_max_range - visible_min_range);
          sprintf(text_label, "%.2f", visible_range / (float) MAIN_FRAME_Y_LABELS * (float) i + visible_min_range);
          draw_text(MAIN_FRAME_X_MARGIN - 30,
                  height - (int) (current_label + MAIN_FRAME_Y_MARGIN +
                  BUFFER_HEIGHT + ERROR_FRAME_HEIGHT + BUFFER_HEIGHT + GRAPH_0_FRAME_HEIGHT + GRAPH_1_FRAME_HEIGHT + GRAPH_2_FRAME_HEIGHT) + 4,
                  text_label, 0.6f, 0.6f, 0.6f, text_alpha, GLUT_BITMAP_HELVETICA_10);
          glColor4f(0.8f, 0.8f, 0.8f, alpha);
          glBegin(GL_LINES);
          glVertex2i(MAIN_FRAME_X_MARGIN, height - (int) (current_label + MAIN_FRAME_Y_MARGIN + BUFFER_HEIGHT + ERROR_FRAME_HEIGHT + BUFFER_HEIGHT + GRAPH_0_FRAME_HEIGHT + GRAPH_1_FRAME_HEIGHT + GRAPH_2_FRAME_HEIGHT));
          glVertex2i(MAIN_FRAME_X_MARGIN + range_main_x, height - (int) (current_label + MAIN_FRAME_Y_MARGIN + BUFFER_HEIGHT + ERROR_FRAME_HEIGHT + BUFFER_HEIGHT + GRAPH_0_FRAME_HEIGHT + GRAPH_1_FRAME_HEIGHT + GRAPH_2_FRAME_HEIGHT));
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
            glVertex2i((int) (absolute_t0_time_position - t * data_point_spacing_x), height - (int) (MAIN_FRAME_Y_MARGIN));
            glVertex2i((int) (absolute_t0_time_position - t * data_point_spacing_x), MAIN_FRAME_Y_MARGIN);
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
            glVertex2i((int) (absolute_t0_time_position - t * data_point_spacing_x), height - (int) (((series[series.size() - t - 1]) * ERROR_FRAME_HEIGHT) + BUFFER_HEIGHT + MAIN_FRAME_Y_MARGIN + GRAPH_0_FRAME_HEIGHT + GRAPH_1_FRAME_HEIGHT + GRAPH_2_FRAME_HEIGHT));
          }
        glEnd();
      }

      void WindowSequence::draw_input_series(std::vector<float> series, int x_offset, bool display_text, int text_offset_x, int text_offset_y, float r, float g, float b, float a, mark m) {
        //draw in the main frame
        glLineWidth(graph_line_width);
        glColor4f(r, g, b, a);
        glBegin(GL_LINE_STRIP);

        for (int t = 0; t < (int) series.size(); t++) {
          if (absolute_t0_time_position - (t - x_offset) * data_point_spacing_x > MAIN_FRAME_X_MARGIN) {
            glVertex2i((int) (absolute_t0_time_position - (t - x_offset) * data_point_spacing_x), height - (int) ((series[series.size() - (unsigned) t - 1] - visible_min_range) / (visible_range) * range_main_y + MAIN_FRAME_Y_MARGIN + BUFFER_HEIGHT + ERROR_FRAME_HEIGHT + BUFFER_HEIGHT + GRAPH_0_FRAME_HEIGHT + GRAPH_1_FRAME_HEIGHT + GRAPH_2_FRAME_HEIGHT));
          }
        }
        glEnd();

        char label_data[32];
        float data_point_size = data_point_spacing_x / 4.0f + 1.0f;
        float line_width = (float) data_point_spacing_x / 20.0f;

        for (int t = 0; t < (int) series.size(); t++) {
          if (absolute_t0_time_position - (t - x_offset) * data_point_spacing_x > MAIN_FRAME_X_MARGIN) {
            draw_mark(m, (int) (absolute_t0_time_position - (t - x_offset) * data_point_spacing_x),
                    height - (int) ((series[series.size() - (unsigned) t - 1] - visible_min_range) / (visible_range) * range_main_y +
                    MAIN_FRAME_Y_MARGIN + BUFFER_HEIGHT + ERROR_FRAME_HEIGHT + BUFFER_HEIGHT + GRAPH_0_FRAME_HEIGHT + GRAPH_1_FRAME_HEIGHT + GRAPH_2_FRAME_HEIGHT),
                    data_point_size, line_width, r, g, b, a);
            if (display_text) {
              sprintf(label_data, "%.2f", (float) series[series.size() - (unsigned) t - 1]);
              draw_text((int) (absolute_t0_time_position - (t - x_offset) * data_point_spacing_x) - text_offset_x,
                      height - (int) ((series[series.size() - (unsigned) t - 1] - visible_min_range) / (visible_range) * range_main_y +
                      MAIN_FRAME_Y_MARGIN + BUFFER_HEIGHT + ERROR_FRAME_HEIGHT + BUFFER_HEIGHT + GRAPH_0_FRAME_HEIGHT + GRAPH_1_FRAME_HEIGHT + GRAPH_2_FRAME_HEIGHT + text_offset_y),
                      label_data, r, g, b, a / 2.0f, GLUT_BITMAP_HELVETICA_10);
            }
          }
        }
      }

      void WindowSequence::draw_iteration_labels(void) {
        float data_point_size = data_point_spacing_x / 4.0f + 1.0f;
        // iteration labels
        int spacing = (int) (50.0f / data_point_spacing_x);
        if (spacing < 1)
          spacing = 1;

        for (unsigned t = 0; t < input_data.size(); t++) {
          if ((int) t % spacing == 0) {
            if (absolute_t0_time_position - t * data_point_spacing_x > MAIN_FRAME_X_MARGIN) {
              char iter_label[30];
              sprintf(iter_label, "%d", current_iteration - t);
              glColor4f(0.6f, 0.6f, 0.6f, alpha);
              draw_text((int) (absolute_t0_time_position - t * data_point_spacing_x - data_point_size / 2 + 1), 10, iter_label, 0.6f, 0.6f, 0.6f, alpha, GLUT_BITMAP_HELVETICA_10);
              draw_text((int) (absolute_t0_time_position - t * data_point_spacing_x - data_point_size / 2 + 1), height - MAIN_FRAME_Y_MARGIN + 10, iter_label, 0.6f, 0.6f, 0.6f, alpha, GLUT_BITMAP_HELVETICA_10);
            }
          }
        }
      }

      void WindowSequence::add_key_entry(int whichFrame, const char *display_text, float x_location, float y_height, float r, float g, float b, float a, mark m) {
        int yPosition;

        int label_start_position = (int) (x_location * range_main_x + MAIN_FRAME_X_MARGIN);

        if (whichFrame == 0) {
          yPosition = height - (int) ((y_height) + MAIN_FRAME_Y_MARGIN + BUFFER_HEIGHT + ERROR_FRAME_HEIGHT + BUFFER_HEIGHT +
                  GRAPH_0_FRAME_HEIGHT + GRAPH_1_FRAME_HEIGHT + GRAPH_2_FRAME_HEIGHT);
        }
        else if (whichFrame == 1) {
          yPosition = height - (int) ((y_height) + MAIN_FRAME_Y_MARGIN + BUFFER_HEIGHT + GRAPH_0_FRAME_HEIGHT +
                  GRAPH_1_FRAME_HEIGHT + GRAPH_2_FRAME_HEIGHT);
        }
        else if (whichFrame == 2) {
          yPosition = height - ((int) (y_height) + MAIN_FRAME_Y_MARGIN + GRAPH_1_FRAME_HEIGHT +
                  GRAPH_2_FRAME_HEIGHT);
        }
        else if (whichFrame == 3) {
          yPosition = height - ((int) (y_height) + MAIN_FRAME_Y_MARGIN + GRAPH_2_FRAME_HEIGHT);
        }

        if (m == NO_LINE) {
          glLineWidth(graph_line_width);
          glColor4f(r, g, b, a);
          glBegin(GL_LINE_STRIP);
          glVertex2i((int) (label_start_position + (3 * 17)), yPosition);
          glVertex2i((int) (label_start_position + (6 * 17)), yPosition);
          glEnd();
        }

        switch (m) {
          case CIRCLE:
          case PLUS:
          case CROSS:
          case SQUARE:
          {
            float data_point_size = data_point_spacing_x / 4.0f + 1.0f;
            float line_width = (float) data_point_spacing_x / 20.0f;
            draw_mark(m, (int) (label_start_position + (3.75 * 17)), yPosition, data_point_size, line_width, r, g, b, a);
            draw_mark(m, (int) (label_start_position + (5.25 * 17)), yPosition, data_point_size, line_width, r, g, b, a);
            break;
          }
          case ONE_CIRCLE:
          {
            float data_point_size = data_point_spacing_x / 4.0f + 1.0f;
            float line_width = (float) data_point_spacing_x / 20.0f;
            draw_mark(m, (int) (label_start_position + (4.5 * 17)), yPosition, data_point_size, line_width, r, g, b, a);
            break;
          }
          case NO_MARK:
          case NO_LINE:
            break;
        }

        char label_data[32];
        sprintf(label_data, "%s", display_text);
        draw_text((int) (label_start_position + (6.75 * 17)), yPosition + (0.015 * range_main_y), label_data, r, g, b, a / 2.0f, GLUT_BITMAP_HELVETICA_18);
      }

#define ERROR_LABELS 4

      void WindowSequence::draw_error_labels(void) {
        float error_max_range = 1.0f;
        for (int i = 1; i <= ERROR_LABELS - 1; i++) {
          float current_label = (float) ERROR_FRAME_HEIGHT / (float) ERROR_LABELS * (float) i;
          char text_label[16];
          sprintf(text_label, "%.0f%%", 100.0f * (float) (error_max_range) / (float) ERROR_LABELS * (float) i);

          draw_text((int) (absolute_t0_time_position + 5), height - (int) (current_label + MAIN_FRAME_Y_MARGIN + GRAPH_1_FRAME_HEIGHT + GRAPH_0_FRAME_HEIGHT + BUFFER_HEIGHT + GRAPH_2_FRAME_HEIGHT) + 4,
                  text_label, 0.4f, 0.4f, 0.4f, text_alpha, GLUT_BITMAP_HELVETICA_10);

          glColor4f(0.8f, 0.8f, 0.8f, alpha);
          glBegin(GL_LINES);
          glVertex2i(MAIN_FRAME_X_MARGIN, height - (int) (current_label + MAIN_FRAME_Y_MARGIN + GRAPH_1_FRAME_HEIGHT + GRAPH_0_FRAME_HEIGHT + BUFFER_HEIGHT + GRAPH_2_FRAME_HEIGHT));
          glVertex2i(absolute_t0_time_position, height - (int) (current_label + MAIN_FRAME_Y_MARGIN + GRAPH_1_FRAME_HEIGHT + GRAPH_0_FRAME_HEIGHT + BUFFER_HEIGHT + GRAPH_2_FRAME_HEIGHT));
          glEnd();
        }
      }

      void WindowSequence::allocate_sliders(int slider_length) {
        input_slider_length = slider_length;
        
        reconstructed_slider = (uint8_t *) malloc(slider_length * sizeof (uint8_t));
        current_slider = (uint8_t *) malloc(slider_length * sizeof (uint8_t));
        next_slider = (uint8_t *) malloc(slider_length * sizeof (uint8_t));
        predicted_slider = (uint8_t *) malloc(slider_length * sizeof (uint8_t));

        for (int k = 0; k < input_slider_length; k++) {
          reconstructed_slider[k] = 0;
          current_slider[k] = 0;
          next_slider[k] = 0;
          predicted_slider[k] = 0;
        }
      }

      void WindowSequence::draw_reconstructions(float alpha) {
        float valueHere, maximum = 0.0f, minimum = 0.0f;

        for (int k = 0; k < input_slider_length; k++) {
          valueHere = (float)reconstructed_slider[k];
          if (valueHere > maximum) maximum = valueHere;
          if (valueHere < minimum) minimum = valueHere;
        }
        maximum = maximum * 1.05; // make sure we see the topmost value;
        glColor4f(0.0f, 0.4f, 0.0f, alpha);
        glBegin(GL_LINE_STRIP);
        for (int k = 0; k < input_slider_length; k++) {
          valueHere = (float)reconstructed_slider[k];
          if (maximum > minimum) valueHere = (valueHere - minimum) / (maximum - minimum);
          glVertex2i(-1 + MAIN_FRAME_X_MARGIN + (int) range_main_x * ((float) k / (float) input_slider_length), -1 + height - ((int) (valueHere * GRAPH_2_FRAME_HEIGHT) + MAIN_FRAME_Y_MARGIN));
        }
        glEnd();

        maximum = 0.0f;
        for (int k = 0; k < input_slider_length; k++) {
          valueHere =(float)predicted_slider[k];
          if (valueHere > maximum) maximum = valueHere;
          if (valueHere < minimum) minimum = valueHere;
        }
        maximum = maximum * 1.05; // make sure we see the topmost value;  glColor4f(0.0f, 0.0f, 0.9f, alpha);
        glColor4f(0.0f, 0.0f, 0.9f, alpha);
        glBegin(GL_LINE_STRIP);
        for (int k = 0; k < input_slider_length; k++) {
          valueHere = (float)predicted_slider[k];
          if (maximum > minimum) valueHere = (valueHere - minimum) / (maximum - minimum);
          glVertex2i(-1 + MAIN_FRAME_X_MARGIN + (int) range_main_x * ((float) k / (float) input_slider_length), -1 + height - ((int) (valueHere * GRAPH_2_FRAME_HEIGHT) + MAIN_FRAME_Y_MARGIN));
        }
        glEnd();

        maximum = 0.0f;
        for (int k = 0; k < input_slider_length; k++) {
          valueHere = (float)next_slider[k];
          if (valueHere > maximum) maximum = valueHere;
          if (valueHere < minimum) minimum = valueHere;
        }
        maximum = maximum * 1.05; // make sure we see the topmost value;
        glColor4f(0.9f, 0.0f, 0.9f, alpha);
        glBegin(GL_LINE_STRIP);
        for (int k = 0; k < input_slider_length; k++) {
          valueHere = (float)next_slider[k];
          if (maximum > minimum) valueHere = (valueHere - minimum) / (maximum - minimum);
          glVertex2i(1 + MAIN_FRAME_X_MARGIN + (int) range_main_x * ((float) k / (float) input_slider_length), 1 + height - ((int) (valueHere * GRAPH_2_FRAME_HEIGHT) + MAIN_FRAME_Y_MARGIN));
        }
        glEnd();

        maximum = 0.0f;
        for (int k = 0; k < input_slider_length; k++) {
          valueHere = (float)current_slider[k];
          if (valueHere > maximum) maximum = valueHere;
          if (valueHere < minimum) minimum = valueHere;
        }
        maximum = maximum * 1.05; // make sure we see the topmost value;
        glColor4f(0.9f, 0.0f, 0.0f, alpha);
        glBegin(GL_LINE_STRIP);
        for (int k = 0; k < input_slider_length; k++) {
          valueHere = (float)current_slider[k];
          if (maximum > minimum) valueHere = (valueHere - minimum) / (maximum - minimum);
          glVertex2i(1 + MAIN_FRAME_X_MARGIN + (int) range_main_x * ((float) k / (float) input_slider_length), 1 + height - ((int) (valueHere * GRAPH_2_FRAME_HEIGHT) + MAIN_FRAME_Y_MARGIN));
        }
        glEnd();
      }

      void WindowSequence::vanishWindow(int height_, int width_) {
        height = height_;
        width = width_;
        LOG(LSTATUS) << "Vanishing window to " << height << " x " << width;
        // Resize window.
        glutReshapeWindow(width, height);
        // Place it in the previous position.
        glutPositionWindow(position_x, position_y);
      }
    } /* namespace visualization */
  } /* namespace opengl */
} /* namespace mic */

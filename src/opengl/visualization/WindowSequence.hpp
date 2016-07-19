/*!
 * \file WindowSequence.hpp
 * \brief Contains declaration of a class responsible for plotting a temporal (i.e. time-varying) sequence of digits.
 * \author tkornuta
 * \date Nov 30, 2015
 */

#include <opengl/visualization/Window.hpp>
#include <vector>


#ifndef SRC_VISUALIZATION_OPENGL_WINDOWSEQUENCE_HPP_
#define SRC_VISUALIZATION_OPENGL_WINDOWSEQUENCE_HPP_


namespace mic {
  namespace opengl {
    namespace visualization {

#define MAIN_FRAME_X_MARGIN 40
#define MAIN_FRAME_Y_MARGIN 30
#define MAIN_FRAME_Y_LABELS 25
#define ERROR_FRAME_HEIGHT 100
#define BUFFER_HEIGHT 25
#define GRAPH_0_FRAME_HEIGHT 2
#define GRAPH_1_FRAME_HEIGHT 2
#define GRAPH_2_FRAME_HEIGHT 150

      /*!
       * \brief OpenGL-based window responsible for for plotting a temporal (i.e. time-varying) sequence of digits.
       * WORK IN PROGRESS.
       * \author tkornuta/krocki
       */
      class WindowSequence : public Window {
      public:

        /*!
         * Constructor.
         */
        WindowSequence(std::string name_ = "Chart", unsigned int height_ = 1024, unsigned int width_ = 768, unsigned int position_x_ = 0, unsigned int position_y_ = 0);

        /*!
         * Destructor.
         */
        virtual ~WindowSequence();

        /*!
         * Refreshes the content of the window.
         */
        void displayHandler(void);
        void allocate_sliders(int slider_length);
        void vanishWindow(int height_, int width_);
                
        bool disabled;
        std::vector<float> input_data;
        std::vector<float> predicted_data;
        std::vector<float> reconstructed_data;
        std::vector<float> spatial_error;
        std::vector<float> prediction_error;
        int current_iteration;
        uint8_t *reconstructed_slider;
        uint8_t *current_slider;
        uint8_t *next_slider;
        uint8_t *predicted_slider;


      private:
        float alpha;
        float text_alpha;
        float graph_line_width;

        float data_point_spacing_x;
        float t0_time_position;

        int absolute_t0_time_position;
        int range_main_x;
        int range_main_y;
        int input_slider_length;

        float visible_min_range;
        float visible_max_range;
        float visible_range;

        void draw_outer_frame(void);
        void draw_main_frame(void);
        void draw_input_series(std::vector<float> series, int x_offset, bool display_text, int text_offset_x, int text_offset_y, float r, float g, float b, float a, mark m);
        void draw_error_series(std::vector<float> series, float r, float g, float b, float a);
        void draw_iteration_labels(void);
        void add_key_entry(int whichFrame, const char *display_text, float x_location, float y_height, float r, float g, float b, float a, mark m);
        void draw_error_labels(void);
        void draw_reconstructions(float alpha);
        void mouseHandler(int button, int state, int x, int y) {};

      };
    } /* namespace visualization */
  } /* namespace opengl */
} /* namespace mic */

#endif /* SRC_VISUALIZATION_OPENGL_WINDOWSEQUENCE_HPP_ */

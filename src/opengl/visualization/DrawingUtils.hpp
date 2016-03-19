/*!
 * \file DrawingUtils.hpp
 * \brief Declaration of a class encapsulating methods for drawing in OpenGL windows
 * \author tkornuta
 * \date Dec 4, 2015
 */

#ifndef SRC_VISUALIZATION_OPENGL_DRAWINGUTILS_HPP_
#define SRC_VISUALIZATION_OPENGL_DRAWINGUTILS_HPP_

 #ifdef __APPLE__
#include <GLUT/glut.h>
#elif defined(_WIN32)
#define M_PI 3.1415926535897932384626433
#define GLUT_NO_LIB_PRAGMA
#define GLUT_NO_WARNING_DISABLE
#define _WCHAR_T_DEFINED
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <glut.h>
#else
#include <GL/glut.h>
#endif

// Dependencies on core types.
#include <types/vector_types.hpp>
#include <types/image_types.hpp>
using namespace mic::types;

namespace mic {
namespace opengl {
namespace visualization {

/*!
 * \brief Different types of marks drawn on chars.
 * \author krocki
 */
typedef enum {CIRCLE, PLUS, CROSS, SQUARE} mark;

/*!
 * \brief Class offering methods for drawing in OpenGL windows.
 * \author krocki
 */
class DrawingUtils {
public:

	/*!
	 * Virtual destructor. Empty.
	 */
	virtual ~DrawingUtils () {}

	/*!
	 * Draws image in current window.
	 * @param img
	 * @param w
	 * @param h
	 * @param show_grid
	 */
	void display_image(image* img, unsigned w, unsigned h, bool show_grid = false);

	/*!
	 * Draws image ROI.
	 * @param img
	 * @param w
	 * @param h
	 * @param x1
	 * @param y1
	 * @param x2
	 * @param y2
	 * @param r
	 * @param g
	 * @param b
	 * @param a
	 */
	void display_image_roi(image* img, unsigned w, unsigned h, int x1, int y1, int x2, int y2, float r, float g, float b, float a);

	/*!
	 * Draws frame.
	 * @param x1
	 * @param y1
	 * @param x2
	 * @param y2
	 * @param r
	 * @param g
	 * @param b
	 * @param a
	 */
	void draw_frame(float x1, float y1, float x2, float y2, float r, float g, float b, float a);

	/*!
	 * Draws grid (i.e. horizontal and vertical lines).
	 * @param r
	 * @param g
	 * @param b
	 * @param a
	 * @param cells_h
	 * @param cells_v
	 */
	void draw_grid(float r, float g, float b, float a, float cells_h, float cells_v);

	/*!
	 * Draws mark.
	 * @param m
	 * @param x
	 * @param y
	 * @param size
	 * @param line_width
	 * @param r
	 * @param g
	 * @param b
	 * @param a
	 */
	void draw_mark(mark m, float x, float y, float size, float line_width, float r, float g, float b, float a);

	/*!
	 * Draws circle mark.
	 * @param x
	 * @param y
	 * @param size
	 * @param line_width
	 * @param r
	 * @param g
	 * @param b
	 * @param a
	 */
	void draw_circle(float x, float y, float size, float line_width, float r, float g, float b, float a);

	/*!
	 * Draws plus mark.
	 * @param x
	 * @param y
	 * @param size
	 * @param line_width
	 * @param r
	 * @param g
	 * @param b
	 * @param a
	 */
	void draw_plus(float x, float y, float size, float line_width, float r, float g, float b, float a);

	/*!
	 * Draws cross mark.
	 * @param x
	 * @param y
	 * @param size
	 * @param line_width
	 * @param r
	 * @param g
	 * @param b
	 * @param a
	 */
	void draw_cross(float x, float y, float size, float line_width, float r, float g, float b, float a);

	/*!
	 * Draws square mark.
	 * @param x
	 * @param y
	 * @param size
	 * @param line_width
	 * @param r
	 * @param g
	 * @param b
	 * @param a
	 */
	void draw_square(float x, float y, float size, float line_width, float r, float g, float b, float a);

	/*!
	 * Draws square.
	 * @param size
	 * @param line_width
	 * @param r
	 * @param g
	 * @param b
	 * @param a
	 */
	void draw_square_in_place(float size, float line_width, float r, float g, float b, float a);

	/*!
	 * Draws filled square.
	 * @param x
	 * @param y
	 * @param size
	 * @param r
	 * @param g
	 * @param b
	 * @param a
	 */
	void draw_filled_square(float x, float y, float size, float r, float g, float b, float a);

	/*!
	 * Draws rectangle.
	 * @param x
	 * @param y
	 * @param h
	 * @param w
	 * @param r
	 * @param g
	 * @param b
	 * @param a
	 */
	void draw_rectangle(float x, float y, float h, float w, float r, float g, float b, float a);

	/*!
	 * Draws filled rectangle.
	 * @param x
	 * @param y
	 * @param h
	 * @param w
	 * @param r
	 * @param g
	 * @param b
	 * @param a
	 */
	void draw_filled_rectangle(float x, float y, float h, float w, float r, float g, float b, float a);

	/*!
	 * Draws texture in the center of the window.
	 * @param size
	 */
	void draw_texture_in_place(float size);

	/*!
	 * Draws filled square in the center of the window.
	 * @param radius
	 * @param line_width
	 * @param r
	 * @param g
	 * @param b
	 * @param a
	 */
	void draw_filled_square_in_place(float radius, float line_width, float r, float g, float b, float a);

	/*!
	 * Draws filled rectangle in the center of the window.
	 * @param radius_x
	 * @param radius_y
	 * @param line_width
	 * @param r
	 * @param g
	 * @param b
	 * @param a
	 */
	void draw_filled_rectangle_in_place(float radius_x, float radius_y, float line_width, float r, float g, float b, float a);

	/*!
	 * Draws cuboid.
	 * @param radius
	 * @param line_width
	 * @param height
	 * @param r
	 * @param g
	 * @param b
	 * @param a
	 */
	void draw_cuboid(float radius, float line_width, float height, float r, float g, float b, float a);

	/*!
	 * Draws text.
	 * @param x
	 * @param y
	 * @param string
	 * @param r
	 * @param g
	 * @param b
	 * @param a
	 * @param font
	 */
	void draw_text(float x, float y, char* string, float r, float g, float b, float a, void* font);

	/*!
	 * Draws text.
	 * @param x
	 * @param y
	 * @param z
	 * @param string
	 * @param r
	 * @param g
	 * @param b
	 * @param a
	 * @param font
	 */
	void draw_text_3i(float x, float y, float z, char* string, float r, float g, float b, float a, void* font);

	/*!
	 * Draws cursos
	 * @param x
	 * @param y
	 * @param r
	 * @param g
	 * @param b
	 * @param a
	 */
	void draw_cursor(float x, float y, float r, float g, float b, float a);

	/*!
	 * Draws text in 3D.
	 * @param x
	 * @param y
	 * @param text
	 */
	void draw_text_3d(GLfloat x, GLfloat y, char* text);

	/*!
	 * Recalculate degrees to radians.
	 * @param degrees
	 * @return
	 */
	float to_radians(float degrees);

	/*!
	 * Returns 3D position.
	 * @param x
	 * @param y
	 * @param plane
	 * @return
	 */
	v_3f get_3d_position(int x, int y, float plane);

};

} /* namespace visualization */
} /* namespace opengl */
} /* namespace mic */

#endif /* SRC_VISUALIZATION_OPENGL_DRAWINGUTILS_HPP_ */

/*!
 * \file DrawingUtils.cpp
 * \brief Definition of methods for drawing in OpenGL windows
 * \author tkornut
 * \date Dec 4, 2015
 */

#include <opengl/visualization/DrawingUtils.hpp>
#include <cmath>

namespace mic {
namespace opengl {
namespace visualization {


void DrawingUtils::display_image_roi(image* img, unsigned w, unsigned h, int x1, int y1, int x2, int y2, float r, float g, float b, float a) {

     if (img != NULL) {

        float scale_x = (float)w/(float)(img->width);
        float scale_y = (float)h/(float)(img->height);

        draw_rectangle((float)x1 * scale_x, (float)y1 * scale_y, (float)(x2 - x1) * scale_y, (float)(y2 - y1) * scale_x, r, g, b, a);

     }

}

void DrawingUtils::display_image(image* img, unsigned w, unsigned h, bool show_grid) {

    if (img != NULL && img->image_data != NULL) {

        float scale_x = (float)w/(float)(img->width);
        float scale_y = (float)h/(float)(img->height);

        for (unsigned x = 0; x < img->width; x++) {

            for (unsigned y = 0; y < img->height; y++) {

                if (img->type == BINARY) {

                    uint8_t color = get_color(img, GRAY, y, x);

                    draw_filled_rectangle((float)x * scale_x, float(y) * scale_y, scale_y, scale_x,
                    (float)color/255.0f,
                    (float)color/255.0f,
                    (float)color/255.0f,
                    1.0f);

                } else if (img->type == GRAYSCALE) {

                    float color = get_color_float(img, GRAY, y, x);

                    draw_filled_rectangle((float)x * scale_x, float(y) * scale_y, scale_y, scale_x,
                    (float)color,
                    (float)color,
                    (float)color,
                    1.0f);

                } else if (img->type == RGBA) {

                    uint8_t color_r = get_color(img, RED, y, x);
                    uint8_t color_g = get_color(img, GREEN, y, x);
                    uint8_t color_b = get_color(img, BLUE, y, x);
                    uint8_t color_a = get_color(img, ALPHA, y, x);

                    draw_filled_rectangle((float)x * scale_x, float(y) * scale_y, scale_y, scale_x,
                    (float)color_r/255.0f,
                    (float)color_g/255.0f,
                    (float)color_b/255.0f,
                    (float)color_a/255.0f);

                }

            }
        }

        if (show_grid) {

            glColor4f(0.8f, 0.0f, 0.0f, 0.5f);
            glBegin(GL_LINES);

            for (unsigned i = 0; i < w; i++) {

                glVertex2i((int)((float)i * scale_x), 0);
                glVertex2i((int)((float)i * scale_x), (GLint)h);

            }

            for (unsigned i = 0; i < h; i++) {

                glVertex2i(0, (int)((float)i * scale_y));
                glVertex2i((GLint)w, (int)((float)i * scale_y));

            }

            glEnd();

        }

    } else {

        //CHECK(img != NULL && img->image_data != NULL);
    }

}

void DrawingUtils::draw_frame(float x1, float y1, float x2, float y2, float r, float g, float b, float a) {

    glColor4f(r, g, b, a);

    glBegin(GL_LINE_STRIP);

    //margins, top frame
    glVertex2i((int)x1, (int)y1);
    glVertex2i((int)x1, (int)y2);
    glVertex2i((int)x2, (int)y2);
    glVertex2i((int)x2, (int)y1);
    glVertex2i((int)x1, (int)y1);

    glEnd();

}

void DrawingUtils::draw_grid(float r, float g, float b, float a, float cells_h, float cells_v) {

	GLint h = glutGet(GLUT_WINDOW_HEIGHT);
	GLint w = glutGet(GLUT_WINDOW_WIDTH);

	float scale_x = (float)w/(float)(cells_h);
	float scale_y = (float)h/(float)(cells_v);

    glColor4f(r, g, b, a);
    glBegin(GL_LINES);

    for (unsigned i = 1; i < cells_h; i++) {

        glVertex2i((int)((float)i * scale_x), 0);
        glVertex2i((int)((float)i * scale_x), (GLint)h);

    }

    for (unsigned i = 1; i < cells_v; i++) {

        glVertex2i(0, (int)((float)i * scale_y));
        glVertex2i((GLint)w, (int)((float)i * scale_y));

    }

    glEnd();
}

void DrawingUtils::draw_mark(mark m, float x, float y, float size, float line_width, float r, float g, float b, float a) {

    switch (m) {

        case CIRCLE:
            draw_circle(x, y, size, line_width, r, g, b, a);
            break;

        case PLUS:
            draw_plus(x, y, size, line_width, r, g, b, a);
            break;

        case CROSS:
            draw_cross(x, y, size, line_width, r, g, b, a);
            break;

        case SQUARE:
            draw_square(x, y, size, line_width, r, g, b, a);
            break;

    }
}

void DrawingUtils::draw_circle(float x, float y, float radius, float line_width, float r, float g, float b, float a) {

    glColor4f(r, g, b, a);

    glLineWidth(line_width);

    glBegin(GL_LINE_STRIP);

    for (float angle = 0.0f; angle <= 360.0f; angle += 30.0f) {
        glVertex2f((x + sinf((angle * (float)M_PI)/180.0f) * radius), (y + cosf((angle * (float)M_PI)/180.0f) * radius));
    }

    glEnd();

}

void DrawingUtils::draw_plus(float x, float y, float radius, float line_width, float r, float g, float b, float a) {

    glColor4f(r, g, b, a);

    glLineWidth(line_width);

    glBegin(GL_LINES);

        glVertex2i((int)x, (int)(y - radius));
        glVertex2i((int)x, (int)(y + radius));

        glVertex2i((int)(x - radius), (int)y);
        glVertex2i((int)(x + radius), (int)y);

    glEnd();

    glLineWidth(1.0f);

}

void DrawingUtils::draw_cross(float x, float y, float radius, float line_width, float r, float g, float b, float a) {

    glColor4f(r, g, b, a);

    glLineWidth(line_width);

    glBegin(GL_LINES);

        glVertex2i((int)(x - radius), (int)(y - radius));
        glVertex2i((int)(x + radius), (int)(y + radius));

        glVertex2i((int)(x + radius), (int)(y - radius));
        glVertex2i((int)(x - radius), (int)(y + radius));

    glEnd();

}

void DrawingUtils::draw_square(float x, float y, float radius, float line_width, float r, float g, float b, float a) {

    glColor4f(r, g, b, a);

    glLineWidth(line_width);

    glBegin(GL_LINE_STRIP);

        glVertex2i((int)(x - radius), (int)(y - radius));
        glVertex2i((int)(x + radius), (int)(y - radius));
        glVertex2i((int)(x + radius), (int)(y + radius));
        glVertex2i((int)(x - radius), (int)(y + radius));
        glVertex2i((int)(x - radius), (int)(y - radius));

    glEnd();

}

void DrawingUtils::draw_square_in_place(float radius, float line_width, float r, float g, float b, float a) {

    glColor4f(r, g, b, a);

    glLineWidth(line_width);

    glBegin(GL_LINE_STRIP);

        glNormal3f(0.0f,0.0f,1.0f);
        glVertex3f(- radius, - radius, 0.0f);
        glVertex3f(radius, - radius, 0.0f);
        glVertex3f(radius, radius, 0.0f);
        glVertex3f(- radius, radius, 0.0f);
        glVertex3f(- radius, - radius, 0.0f);

    glEnd();

}

void DrawingUtils::draw_filled_square_in_place(float radius, float line_width, float r, float g, float b, float a) {

    glColor4f(r, g, b, a);

    glLineWidth(line_width);

    glBegin(GL_QUADS);

        glNormal3f(0.0f,0.0f,1.0f);
        glVertex3f(- radius, - radius, 0.0f);
        glVertex3f(radius, - radius, 0.0f);
        glVertex3f(radius, radius, 0.0f);
        glVertex3f(- radius, radius, 0.0f);

    glEnd();

}

void DrawingUtils::draw_filled_rectangle_in_place(float radius_x, float radius_y, float line_width, float r, float g, float b, float a) {

    glColor4f(r, g, b, a);

    glLineWidth(line_width);

    glBegin(GL_QUADS);

        glNormal3f(0.0f,0.0f,1.0f);
        glVertex3f(- radius_x, - radius_y, 0.0f);
        glVertex3f(radius_x, - radius_y, 0.0f);
        glVertex3f(radius_x, radius_y, 0.0f);
        glVertex3f(- radius_x, radius_y, 0.0f);

    glEnd();

}

void DrawingUtils::draw_cuboid(float radius, float line_width, float height, float r, float g, float b, float a) {

    glColor4f(r, g, b, a);

    glLineWidth(line_width);

    glBegin(GL_POLYGON);
        glNormal3f(0,0,1);
        glVertex3f(- radius, - radius, height);
        glVertex3f(radius, - radius, height);
        glVertex3f(radius, radius, height);
        glVertex3f(- radius, radius, height);
    glEnd();

    glBegin(GL_POLYGON);
        glNormal3f(-1.0f,0.0f,0.0f);
        glVertex3f(- radius, - radius, 0.0f);
        glVertex3f(- radius, - radius, height);
        glVertex3f(- radius, radius, height);
        glVertex3f(- radius, radius, 0.0f);
    glEnd();

    glBegin(GL_POLYGON);
        glNormal3f(1.0f,0.0f,0.0f);
        glVertex3f( radius, - radius, 0.0f);
        glVertex3f( radius, - radius, height);
        glVertex3f( radius, radius, height);
        glVertex3f( radius, radius, 0.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0f,1.0f,0.0f);
        glVertex3f( - radius, radius, 0.0f);
        glVertex3f( - radius, radius, height);
        glVertex3f( radius, radius, height);
        glVertex3f( radius, radius, 0.0f);
    glEnd();

     glBegin(GL_POLYGON);
      glNormal3f(0.0f,-1.0f,0.0f);
        glVertex3f( - radius, -radius, 0.0f);
        glVertex3f( - radius, -radius, height);
        glVertex3f(  radius, -radius, height);
        glVertex3f(  radius, -radius, 0.0f);
     glEnd();


}

void DrawingUtils::draw_texture_in_place(float radius) {

    glBegin(GL_QUADS);

        glNormal3f(0.0f, 0.0f, 1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(- radius, - radius, 0.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(radius, - radius, 0.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(radius, radius, 0.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(- radius, radius, 0.0f);

    glEnd();

}
void DrawingUtils::draw_filled_square(float x, float y, float radius, float r, float g, float b, float a) {

    draw_filled_rectangle(x, y, radius/2.0f, radius/2.0f, r, g, b, a);

}

void DrawingUtils::draw_filled_rectangle(float x, float y, float h, float w, float r, float g, float b, float a) {

    glColor4f(r, g, b, a);

    glBegin(GL_QUADS);

        //margins, top frame
        glVertex2i((int)(x), (int)(y));
        glVertex2i((int)(x + w), (int)(y));
        glVertex2i((int)(x + w), (int)(y + h));
        glVertex2i((int)(x), (int)(y + h));

    glEnd();

}

void DrawingUtils::draw_rectangle(float x, float y, float h, float w, float r, float g, float b, float a) {

    glColor4f(r, g, b, a);

    glBegin(GL_LINE_STRIP);

        //margins, top frame
        glVertex2i((int)(x), (int)(y));
        glVertex2i((int)(x + w), (int)(y));
        glVertex2i((int)(x + w), (int)(y + h));
        glVertex2i((int)(x), (int)(y + h));
        glVertex2i((int)(x), (int)(y));

    glEnd();

}

void DrawingUtils::draw_text(float x, float y, char* string, float r, float g, float b, float a, void* font) {

    int len, i;

    glColor4f(r, g, b, a);

    glRasterPos2i((int)x, (int)y);

    len = (int) strlen(string);

    for (i = 0; i < len; i++)
        glutBitmapCharacter(font, string[i]);

}

void DrawingUtils::draw_text_3i(float x, float y, float z, char* string, float r, float g, float b, float a, void* font) {

    int len, i;

    glColor4f(r, g, b, a);
    glRasterPos3i((int)x, (int)y, (int)z);

    len = (int) strlen(string);

    for (i = 0; i < len; i++)
        glutBitmapCharacter(font, string[i]);

}

void DrawingUtils::draw_cursor(float x, float y, float r, float g, float b, float a) {

    char str[32];

    sprintf(str, "[%.3f, %.3f]", x, y);

    draw_text(x, y, str, r, g, b, a, GLUT_BITMAP_HELVETICA_10);

}

float DrawingUtils::to_radians(float degrees) {
    return degrees * (float)(M_PI / 180.0f);
}

v_3f DrawingUtils::get_3d_position(int x, int y, float plane) {

    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY, winZ;
    GLdouble posX, posY, posZ;
 	v_3f point;

    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetDoublev( GL_PROJECTION_MATRIX, projection );
    glGetIntegerv( GL_VIEWPORT, viewport );

    winX = (float)x;
    winY = (float)viewport[3] - (float)y;
    glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );

    gluUnProject( winX, winY, plane, modelview, projection, viewport, &posX, &posY, &posZ);

 	point.x = (float)posX;
 	point.y = (float)posY;
 	point.z = (float)posZ;

    return point;
}

} /* namespace visualization */
} /* namespace opengl */
} /* namespace mic */


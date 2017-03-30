/*!
 * \file WindowMatrix2D.hpp
 * \brief Window displaying 2d matrix (e.g. a grayscale image).
 * \author tkornut
 * \date Dec 22, 2015
 */

#ifndef SRC_VISUALIZATION_OPENGL_WINDOWMATRIX2D_HPP_
#define SRC_VISUALIZATION_OPENGL_WINDOWMATRIX2D_HPP_

#include <opengl/visualization/Window.hpp>

// Dependencies on core types.
#include <types/MatrixTypes.hpp>
using namespace mic::types;

namespace mic {
namespace opengl {
namespace visualization {

/*!
 * \brief OpenGL-based window responsible for displaying 2D matrices.
 * \author tkornuta/krocki
 */
class WindowMatrix2D: public Window {
public:
	/*!
	 * Constructor. NULLs the image pointer.
	 */
	WindowMatrix2D(std::string name_ = "Matrix2D", unsigned int height_ = 512, unsigned int width_ = 512, unsigned int position_x_ = 0, unsigned int position_y_ = 0);

	/*!
	 * Destructor.
	 */
	virtual ~WindowMatrix2D();


	/*!
	 * Refreshes the content of the window.
	 */
	void displayHandler(void);

	/*!
	 * Sets displayed matrix.
	 * @param displayed_matrix_
	 */
	void setMatrixSynchronized(mic::types::MatrixXf & displayed_matrix_);

	/*!
	 * Sets displayed matrix. Unsynchronized i.e. must be used inside of manually synchronized section.
	 * @param displayed_matrix_
	 */
	void setMatrixUnsynchronized(mic::types::MatrixXf & displayed_matrix_);


	/*!
	 * Sets pointer to displayed matrix.
	 * @param displayed_matrix_
	 */
	void setMatrixPointerSynchronized(mic::types::MatrixXfPtr displayed_matrix_ptr_);

	/*!
	 * Sets pointer to displayed matrix. Unsynchronized i.e. must be used inside of manually synchronized section.
	 * @param displayed_matrix_
	 */
	void setMatrixPointerUnsynchronized(mic::types::MatrixXfPtr displayed_matrix_ptr_);

private:

	/*!
	 * Pointer to displayed matrix.
	 */
	mic::types::MatrixXfPtr displayed_matrix_ptr;
};

} /* namespace visualization */
} /* namespace opengl */
} /* namespace mic */

#endif /* SRC_VISUALIZATION_OPENGL_WINDOWMATRIX2D_HPP_ */

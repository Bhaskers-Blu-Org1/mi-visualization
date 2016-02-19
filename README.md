Machine Intelligence Core: Visualization
=========================================

Description
-----------

A subproject of Machine Intelligence Core framework.

The library contains OpenGL-based tools for visualization.

MIC dependencies
------------
   * MIToolchain - core library of MIC.
   * MIAlgorithms - contains basic (core) types used by MIVisualization.

External dependencies
------------
Additionally it depends on the following external libraries:
   * Boost - library of free (open source) peer-reviewed portable C++ source libraries.
   * Eigen - a C++ template library for linear algebra: matrices, vectors, numerical solvers, and related algorithms.
   * OpenGL - a cross-language, cross-platform application programming interface for rendering 2D and 3D vector graphics.

Main modules
------------
   *  visualization_opengl contains window manager and several types of windows, as well as base classes usefull for building applications using OpenGL. 

Applications
------------
   *  image_encoder_test image encoder (with OpenGL-based visualization) test application 

Maintainer
----------

tkornuta
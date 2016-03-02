Machine Intelligence Core: Visualization
=========================================

Description
-----------

A subproject of Machine Intelligence Core framework.

Contains tools for building applications with OpenGL-based visualization of data, results of execution etc.

MIC dependencies
------------
   * MIToolchain - the core of MIC framework.
   * MIAlgorithms - contains basic (core) types used by MIVisualization.

External dependencies
------------
Additionally it depends on the following external libraries:
   * Boost - library of free (open source) peer-reviewed portable C++ source libraries.
   * Eigen - a C++ template library for linear algebra: matrices, vectors, numerical solvers, and related algorithms.
   * OpenGL/GLUT - a cross-language, cross-platform application programming interface for rendering 2D and 3D vector graphics.

Main modules
------------
   *  visualization_opengl contains window manager and several types of windows, as well as base classes useful for building applications using OpenGL. 

Applications
------------
   *  image_encoder_test image encoder (with OpenGL-based visualization) test application 

Installation
------------
```
git clone git@github.rtp.raleigh.ibm.com:tkornut-us/mi-visualization.git
cd mi-visualization
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=~/Documents/workspace/mic/
make -j4 install
```

Maintainer
----------
tkornuta
#Machine Intelligence Core: Visualization

Status of Travis Continuous Integration:

[![Build Status](https://travis.ibm.com/tkornut/mi-visualization.svg?token=9XHfj7QaSbmFqHsyaQes&branch=master)](https://travis.ibm.com/tkornut/mi-visualization)

## Description

A subproject of Machine Intelligence Core framework.

Contains tools for building applications with OpenGL-based visualization of data, results of execution etc.

## MIC dependencies

   * MIToolchain - the core of MIC framework.
   * MIAlgorithms - contains basic (core) types used by MIVisualization.

## External dependencies

Additionally it depends on the following external libraries:
   * Boost - library of free (open source) peer-reviewed portable C++ source libraries.
   * Eigen - a C++ template library for linear algebra: matrices, vectors, numerical solvers, and related algorithms.
   * OpenGL/GLUT - a cross-language, cross-platform application programming interface for rendering 2D and 3D vector graphics.

### Installation of the dependencies/required tools

On Linux (Ubuntu 14.04): 

    sudo apt-get install git cmake cmake-curses-gui doxygen libboost1.54-all-dev libeigen3-dev freeglut3-dev libxmu-dev libxi-dev

## Main modules

   *  visualization_opengl contains window manager and several types of windows, as well as base classes useful for building applications using OpenGL. 

## Applications

   *  image_encoder_test image encoder (with OpenGL-based visualization) test application 

## Installation

In order to download, configure, make and install new "clean" version of mi-visualization please execute the following:

    cd ~/workspace
    git clone git@github.ibm.com:tkornut/mi-visualization.git
    cd mi-visualization
    mkdir build
    cd build
    cmake .. -DCMAKE_INSTALL_PREFIX=~/workspace/mic/
    make -j4 install

## Documentation

In order to generate a "living" documentation of the code please run Doxygen:

    cd ~/workspace/mi-visualization
    doxygen mi-visualization.doxyfile
    firefox html/index.html

The current documentation (generated straight from the code and automatically uploaded to GH pages by Travis) is available at:

https://pages.github.ibm.com/tkornut/mi-visualization/

## Maintainer

Tomasz Kornuta (tkornut@us.ibm.com)
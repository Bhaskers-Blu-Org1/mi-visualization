# Machine Intelligence Core: Visualization

![Language](https://img.shields.io/badge/language-C%2B%2B-blue.svg)
[![GitHub license](https://img.shields.io/github/license/IBM/mi-visualization.svg)](https://github.com/IBM/mi-visualization/blob/master/LICENSE)
![](https://img.shields.io/github/release/IBM/mi-visualization.svg)
[![Build Status](https://travis-ci.com/IBM/mi-visualization.svg?branch=master)](https://travis-ci.com/IBM/mi-visualization)
[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/IBM/mi-visualization.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/IBM/mi-visualization/context:cpp)
[![Total alerts](https://img.shields.io/lgtm/alerts/g/IBM/mi-visualization.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/IBM/mi-visualization/alerts/)

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

The current documentation (generated straight from the code and automatically uploaded to github pages by Travis) is available at:

https://ibm.github.io/mi-visualization/


## Maintainer

Tomasz Kornuta (tkornut@us.ibm.com)

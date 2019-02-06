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

### Main modules

   *  visualization_opengl contains window manager and several types of windows, as well as base classes useful for building applications using OpenGL. 
   *  opengl_application contains base classes for building applications using OpenGL windows and controlled by events thrown by those windows.

### Applications (tests)

   *  window_grayscale_image_test grayscale image visualization test application
   *  window_grayscale_batch_test grayscale batch visualization test application
   *  window_rgb_image_test the RGB image visualization test application


## External dependencies

Additionally it depends on the following external libraries:
   * Boost - library of free (open source) peer-reviewed portable C++ source libraries.
   * Eigen - a C++ template library for linear algebra: matrices, vectors, numerical solvers, and related algorithms.
   * OpenGL/GLUT - a cross-language, cross-platform application programming interface for rendering 2D and 3D vector graphics.

### Installation of the dependencies/required tools

On Linux (Ubuntu 14.04): 

    sudo apt-get install git cmake doxygen libboost1.54-all-dev libeigen3-dev freeglut3-dev libxmu-dev libxi-dev

#### On Mac (OS X 10.14): (last tested on: Jan/22/2019)

    brew install git cmake doxygen boost eigen glfw3


## MIC dependencies

   * [MI-Toolchain](https://github.com/IBM/mi-toolchain) - the core of MIC framework.
   * [MI-Algorithms](https://github.com/IBM/mi-algorithms) - contains basic (core) types and algorithms.

### Installation of all MIC dependencies (optional)

This step is required only when not downloaded/installed the listed MIC dependencies earlier.

In directory scripts one can find script that will download and install all required MIC modules.

    git clone git@github.com:IBM/mi-visualization.git
    cd mi-visualization
    ./scripts/install_mic_deps.sh ../mic

Then one can install the module by calling the following.

    ./scripts/build_mic_module.sh ../mic

Please note that it will create a directory 'deps' and download all sources into that directory.
After compilation all dependencies will be installed in the directory '../mic'.

## Installation of MI-Visualization
The following assumes that all MIC dependencies are installed in the directory '../mic'.

    git clone git@github.com:IBM/mi-visualization.git
    cd mi-visualization
    ./scripts/build_mic_module.sh ../mic

### Make commands

   * make install - install applications to ../mic/bin, headers to ../mic/include, libraries to ../mic/lib, cmake files to ../mic/share

## Documentation

In order to generate a "living" documentation of the code please run Doxygen:

    cd mi-visualization
    doxygen mi-visualization.doxyfile
    firefox html/index.html

The current documentation (generated straight from the code and automatically uploaded to github pages by Travis) is available at:
https://ibm.github.io/mi-visualization/

## Maintainer

[tkornuta](http://github.com/tkornut)

[![HitCount](http://hits.dwyl.io/tkornut/ibm/mi-visualization.svg)](http://hits.dwyl.io/tkornut/ibm/mi-visualization)

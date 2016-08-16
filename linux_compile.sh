#!/bin/bash

module load gcc/4.8.2

PYTHON_INCLUDE_DIR=/gpfs/runtime/opt/python/2.7.3/include/python2.7
PYBIND_EIGEN_INCLUDE_DIR=$HOME/include

# cd to source directory
cd TessBinding

g++ -std=c++11 -I$PYBIND_EIGEN_INCLUDE_DIR -I$PYTHON_INCLUDE_DIR -c TessBinding.cpp -fPIC -o ../Release/TessBinding.o
g++ -std=c++11 -shared -o ../Release/TessBinding.so ../Release/TessBinding.o -ltesseract -llept -lpython2.7

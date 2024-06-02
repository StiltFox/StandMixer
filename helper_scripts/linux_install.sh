#!/bin/bash
rm -rf build
mkdir build
cd build
cmake -DSFSkipTesting=true -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
sudo cmake --install .
cd ..
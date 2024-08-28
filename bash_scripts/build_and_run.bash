#! /usr/bin/env bash

echo "Start project building"
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j 10
cd ..
echo "Running program"
./build/app
echo "Program is ended, results in output folder"
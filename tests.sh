#!/bin/bash

mkdir -p test/temp
cd test/temp
cmake ..
make
./skynet_tests
cd ../..
rm -rf test/temp


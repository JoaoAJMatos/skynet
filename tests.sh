#!/bin/bash

mkdir -p test/temp
cd test/temp
cmake ..
make
clear
./skynet_tests
cd ../..
rm -rf test/temp


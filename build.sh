#!/bin/bash

cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -G "Unix Makefiles"
cd build
make


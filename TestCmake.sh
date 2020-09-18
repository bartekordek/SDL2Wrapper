#!/bin/bash -xe
clear;cd Build-Linux && rm -rf *
pwd
cmake ../libsdl2wrapper -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles"
make -j
pwd
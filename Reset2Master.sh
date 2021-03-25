#!/bin/bash 
time git checkout -f master
time git reset --hard origin/master
cd deps/helpers && ./Reset2Master.sh
cd ../CUL && ./Reset2Master.sh

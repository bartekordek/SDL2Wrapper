#!/bin/bash 
find . -name '*.cpp' | sed 's/\.\///g' > CPP_FILES_LIST.txt

#!/bin/bash 
find inc -name '*.hpp' | sed 's/\.\///g' > HEADER_FILES_LIST.txt

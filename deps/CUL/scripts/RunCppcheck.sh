#!/bin/bash -xe
ROOT_DIR=..
#PREPROCESOR=""
SUPRESS="--suppress=information:SDL_surface.h --suppress=information:gtest/gtest.h"
SETTINGS="--enable=all --std=c++11 --suppress=missingIncludeSystem $SUPRESS"
CPP_FILES=`find $ROOT_DIR -name '*.cpp' | tr '\n' ' '`
HEADERS_LIST=`find $ROOT_DIR -name '*.hpp*'`
HEADERS=$(dirname ${HEADERS_LIST})
HEADERS=`for i in \`echo $HEADERS\`; do
	echo $i
done | sort -u`
HEADERS="$HEADERS .."
#HEADERS=`echo $HEADERS | tr '\.' "-\I ."`
HEADERS=`echo $HEADERS | sed 's/\../-I ../g'` 
echo "Runing cppcheck..."
if [ "$1" == "--check-config" ];then
	cppcheck $ROOTDIR $CPP_FILES $SETTINGS $PREPROCESOR $HEADERS --check-config 2> "CppCheckConfig.txt"
else
	cppcheck $ROOTDIR $CPP_FILES $SETTINGS $PREPROCESOR $HEADERS 2> StaticAnalysis.txt
fi

find $ROOT_DIR -name '*.h' > HeaderList.txt
find $ROOT_DIR -name '*.hpp' >> HeaderList.txt
touch temp.txt
cat HeaderList.txt | sort > temp.txt
cat temp.txt > HeaderList.txt
rm temp.txt
find $ROOT_DIR -name '*.cpp' > SourceList.txt

#!/bin/bash
find . -name '*.cpp' | tr '\n' ' ' > sourcesList
HEADERS_LIST=`find . -name '*.h*'`
HEADERS=$(dirname ${HEADERS_LIST})
HEADERS=`for i in \`echo $HEADERS\`; do
	echo $i
done | sort -u`
HEADERS=`echo $HEADERS | sed 's/\./-I ./g'` 
echo "$HEADERS" > headerDirs

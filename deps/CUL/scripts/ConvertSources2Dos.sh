#!/bin/bash

SOURCES_DIR=..

find $SOURCES_DIR -name '*.cpp' | xargs unix2dos
find $SOURCES_DIR -name '*.hpp' | xargs unix2dos
find $SOURCES_DIR -name '*.h' | xargs unix2dos

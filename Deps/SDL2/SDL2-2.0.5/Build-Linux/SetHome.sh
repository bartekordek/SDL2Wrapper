#!/bin/bash -xe
CURRENT_DIR=`pwd`
LIB_NAME=SDL2_LINUX
KEY_NAME=HOME_$LIB_NAME
export $KEY_NAME=$CURRENT_DIR
setx $KEY_NAME $CURRENT_DIR 
echo "export $KEY_NAME=$CURRENT_DIR" >> ~/.bashrc

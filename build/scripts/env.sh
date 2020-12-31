#!/bin/bash

# output dir
if [ -z ${ROOT_DIR+x} ]; 
then 
    BASE_DIR=$PWD
    # output dir
    OUTPUT_DIR=$BASE_DIR/output
    ROOT_DIR=$OUTPUT_DIR/root
    export CMAKE_INCLUDE_PATH="$ROOT_DIR/usr/include"
    export CMAKE_LIBRARY_PATH="$ROOT_DIR/usr/lib"
    export PKG_CONFIG_PATH="$ROOT_DIR/usr/lib/pkgconfig"
    export LD_LIBRARY_PATH=$ROOT_DIR/usr/lib:$LD_LIBRARY_PATH
    export PATH=$ROOT_DIR/usr/bin:$PATH
    mkdir -p $ROOT_DIR
fi

echo ""
echo "ROOT_DIR=$ROOT_DIR"
echo ""

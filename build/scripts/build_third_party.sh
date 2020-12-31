#!/bin/bash

if [ -z ${ROOT_DIR+x} ]; 
then 
    BASE_DIR=$(dirname $(readlink -f "$0"))
    OUTPUT_DIR=$BASE_DIR/../../output
    ROOT_DIR=$OUTPUT_DIR/root
    mkdir -p $ROOT_DIR
fi


echo ""
echo "ROOT_DIR=$ROOT_DIR"
echo ""


# build jerryscipt
function build_jerryscriot()
{
    cd src/third_party/jerryscript

    cmake -DCMAKE_INSTALL_PREFIX=$ROOT_DIR/usr \
         -DJERRY_GLOBAL_HEAP_SIZE=20480 \
         -DCMAKE_BUILD_TYPE=MinSizeRel \
         -DEXTERNAL_COMPILE_FLAGS=-Wno-unused-function \
         -DBUILD_SHARED_LIBS=ON \
         -DJERRY_CMDLINE_SNAPSHOT=ON \
         -DJERRY_ERROR_MESSAGES=ON \
         -DJERRY_LOGGING=ON \
         -DJERRY_MEM_STATS=ON \
         -DJERRY_PROFILE=es5.1 \
         -DJERRY_SNAPSHOT_EXEC=ON \
         -DJERRY_SNAPSHOT_SAVE=ON \
         -DEXTERNAL_COMPILE_FLAGS="-Wno-unused-function" .
    make -j16
    sudo make install
    cd -
}



# build bounds_checking_function
function build_bounds_checking_function()
{
    cd src/third_party/bounds_checking_function

    cmake -DCMAKE_INSTALL_PREFIX=$ROOT_DIR/usr
    make -j16
    sudo make install

    cd -
}


build_jerryscriot
build_bounds_checking_function

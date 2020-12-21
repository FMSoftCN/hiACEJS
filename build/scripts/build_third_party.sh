#!/bin/bash

BASE_DIR=$(dirname $(readlink -f "$0"))

# output dir
OUTPUT_DIR=$BASE_DIR/../../output
ROOT_DIR=$OUTPUT_DIR/root
mkdir -p $ROOT_DIR

# build jerryscipt
function build_jerryscriot()
{
    pushd ${BASE_DIR}/../../src/third_party/jerryscript

    python tools/build.py --mem-heap=20480 --snapshot-exec=ON --snapshot-save=ON \
        --profile=es5.1 --error-messages=ON --logging=ON --mem-stats=ON \
        --jerry-cmdline-snapshot=ON --compile-flag="-Wno-unused-function" \
        --shared-libs=ON --install=$ROOT_DIR/usr

    popd
}



# build bounds_checking_function
function build_bounds_checking_function()
{
pushd ${BASE_DIR}/../../src/third_party/bounds_checking_function

cmake -DCMAKE_INSTALL_PREFIX=$ROOT_DIR/usr
make -j16
sudo make install

popd
}


build_jerryscriot
build_bounds_checking_function

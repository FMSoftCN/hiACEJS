#!/bin/bash

BASE_DIR=$(dirname $(readlink -f "$0"))

# output dir
OUTPUT_DIR=$BASE_DIR/../../output
ROOT_DIR=$OUTPUT_DIR/root
mkdir -p $ROOT_DIR

export CMAKE_INCLUDE_PATH="$ROOT_DIR/usr/include"
export CMAKE_LIBRARY_PATH="$ROOT_DIR/usr/lib"
export PKG_CONFIG_PATH="$ROOT_DIR/usr/lib/pkgconfig"
echo $PKG_CONFIG_PATH

# build ace
pushd ${BASE_DIR}/../../

cmake -DCMAKE_INSTALL_PREFIX=$ROOT_DIR/usr
make -j16
sudo make install

popd

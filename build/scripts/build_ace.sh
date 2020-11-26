#!/bin/bash

BASE_DIR=$(dirname $(readlink -f "$0"))

# output dir
OUTPUT_DIR=$BASE_DIR/../../output
ROOT_DIR=$OUTPUT_DIR/root
mkdir -p $ROOT_DIR

# build ace
pushd ${BASE_DIR}/../../

cmake -DCMAKE_INSTALL_PREFIX=$ROOT_DIR/usr
make -j16
sudo make install

popd

#!/bin/bash

# output dir
OUTPUT_DIR=output
ROOT_DIR=$OUTPUT_DIR/root

export LD_LIBRARY_PATH=$ROOT_DIR/usr/lib:$LD_LIBRARY_PATH
export PATH=$ROOT_DIR/usr/bin:$PATH

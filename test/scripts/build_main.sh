#!/bin/bash

if [ ! -d build ];then
  mkdir build
fi

gcc -Wall -g src/main.c -I../src/foundation/ace/frameworks/lite/targets/hybridos  -Wl,-rpath-link ../output/root/usr/lib/  -L../output/root/usr/lib -lace -o build/main

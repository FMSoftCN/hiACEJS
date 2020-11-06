#!/bin/sh
pushd ${PWD}/../src/third_party/jerryscript

python tools/build.py --mem-heap=48 --snapshot-exec=ON --snapshot-save=ON \
        --profile=es5.1 --error-messages=ON --logging=ON --mem-stats=ON \
        --jerry-cmdline-snapshot=ON --compile-flag="-Wno-unused-function"

popd

if [ ! -d build ]; then
  mkdir build
fi

cp ${PWD}/../src/third_party/jerryscript/build/bin/jerry ./build/
cp ${PWD}/../src/third_party/jerryscript/build/bin/jerry-snapshot ./build/

echo "snapshot tool generated done."
echo "useage: jerry-snapshot generate -o xxx.bc xxx.js"

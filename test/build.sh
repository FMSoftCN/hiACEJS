#!/bin/bash

gcc -Wall -g main.c -I../src/foundation/ace/frameworks/lite/targets/hybridos -L../src/out/hybridos \
  -lmbedtls -lcipher_shared -lcjson_shared -lsec_shared \
  -ljerry-core_shared -ljerry-ext_shared -ljerry-libm_shared -ljerry-port-default_shared \
  -lace_kit_cipher -lhilog_shared -lace_kit_timer -lace_kit_common -lace_kit_deviceinfo \
  -lace_kit_file -lace_kit_kvstore -lkal_timer -lability_shared -lace_lite -o main

cmake_minimum_required(VERSION 3.10)

project(ace)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -fno-strict-aliasing -fsigned-char -Werror -O1 -fno-lto -fPIC")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wno-format -Wno-format-extra-args -Wno-narrowing -fexceptions -fPIC")

add_definitions(-D_XOPEN_SOURCE=700)
add_definitions(-D__LINUX__)


list(APPEND ace_INCLUDE_DIRECTORIES
    foundation/ace/interfaces/innerkits/builtin
    foundation/ace/interfaces/innerkits/builtin/jsi
    foundation/ace/interfaces/innerkits/builtin/base
    foundation/ace/interfaces/innerkits/builtin/async

    foundation/aafwk/interfaces/kits/ability_lite

    utils/native/lite/include
    utils/native/lite/kal/timer/include
    utils/native/lite/js/builtin/common/include

    base/security/frameworks/crypto_lite/cipher/include
    base/security/frameworks/crypto_lite/js/builtin/include

    third_party/bounds_checking_function/include
)

# hilog_shared
list(APPEND ace_INCLUDE_DIRECTORIES
    utils/native/lite/hilog
)

list(APPEND ace_SOURCES
    utils/native/lite/hilog/log.c
)

# kal_timer
list(APPEND ace_INCLUDE_DIRECTORIES
    utils/native/lite/kal/timer/include
)

list(APPEND ace_SOURCES
    utils/native/lite/kal/timer/src/kal.c
)

# ace_kit_timer
list(APPEND ace_INCLUDE_DIRECTORIES
    utils/native/lite/timer_task/include
)

list(APPEND ace_SOURCES
    utils/native/lite/timer_task/src/nativeapi_timer_task.c
)

# ace_kit_file
list(APPEND ace_INCLUDE_DIRECTORIES
    utils/native/lite/js/builtin/filekit/include/
)

list(APPEND ace_SOURCES
    utils/native/lite/js/builtin/filekit/src/nativeapi_fs.cpp
    utils/native/lite/js/builtin/filekit/src/nativeapi_fs_impl.c
)

include_directories(${ace_INCLUDE_DIRECTORIES})
add_library(ace SHARED ${ace_SOURCES})

cmake_minimum_required(VERSION 3.10)

project(ace)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -fno-strict-aliasing -fsigned-char -Werror -O1 -fno-lto -fPIC")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wno-format -Wno-format-extra-args -Wno-narrowing -fexceptions -fPIC")

add_definitions(-D_XOPEN_SOURCE=700)
add_definitions(-D__LINUX__)


list(APPEND ace_INCLUDE_DIRECTORIES
    foundation/ace/interfaces/innerkits/builtin/jsi
    foundation/ace/interfaces/innerkits/builtin/base

    utils/native/lite/include
    utils/native/lite/kal/timer/include

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

include_directories(${ace_INCLUDE_DIRECTORIES})
add_library(ace SHARED ${ace_SOURCES})

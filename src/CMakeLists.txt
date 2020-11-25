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

    foundation/graphic/lite/interfaces
    foundation/graphic/lite/interfaces/kits/config
    foundation/graphic/lite/interfaces/kits/ui
    foundation/graphic/lite/interfaces/kits/ui/common
    foundation/graphic/lite/interfaces/kits/utils
    foundation/graphic/lite/interfaces/kits/surface

    foundation/graphic/lite/interfaces/innerkits/ui
    foundation/graphic/lite/interfaces/innerkits/wms
    foundation/graphic/lite/services/wms/include
    foundation/graphic/lite/services/ims/include
    foundation/graphic/lite/tools
    foundation/graphic/lite/frameworks

    utils/native/lite/
    utils/native/lite/include
    utils/native/lite/kal/timer/include
    utils/native/lite/js/builtin/common/include


    base/security/frameworks/crypto_lite/cipher/include
    base/security/frameworks/crypto_lite/js/builtin/include

    third_party/bounds_checking_function/include
    third_party/mbedtls/include/mbedtls
    third_party/cJSON
    third_party/freetype/include
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

# ace_kit_kvstore
list(APPEND ace_INCLUDE_DIRECTORIES
    utils/native/lite/js/builtin/kvstorekit/include
)

list(APPEND ace_SOURCES
    utils/native/lite/js/builtin/kvstorekit/src/nativeapi_kv.cpp
    utils/native/lite/js/builtin/kvstorekit/src/nativeapi_kv_impl.c
)

# ace_kit_deviceinfo
list(APPEND ace_INCLUDE_DIRECTORIES
    utils/native/lite/js/builtin/deviceinfokit/include
)

list(APPEND ace_SOURCES
    utils/native/lite/js/builtin/deviceinfokit/src/nativeapi_deviceinfo.cpp
)

# ace_kit_common
list(APPEND ace_INCLUDE_DIRECTORIES
    utils/native/lite/js/builtin/common/src/include
)

list(APPEND ace_SOURCES
    utils/native/lite/js/builtin/common/src/nativeapi_common.cpp
)

# cipher_shared
list(APPEND ace_INCLUDE_DIRECTORIES
    base/security/frameworks/crypto_lite/cipher/include/
)

list(APPEND ace_SOURCES
    base/security/frameworks/crypto_lite/cipher/src/cipher_aes.c
    base/security/frameworks/crypto_lite/cipher/src/cipher_rsa.c
)

# ace_kit_cipher
list(APPEND ace_INCLUDE_DIRECTORIES
    base/security/frameworks/crypto_lite/js/builtin/include/
)

list(APPEND ace_SOURCES
    base/security/frameworks/crypto_lite/js/builtin/src/cipher_module.cpp
)

# graphic_hals
list(APPEND ace_INCLUDE_DIRECTORIES
    foundation/graphic/lite/hals/include/
)

list(APPEND ace_SOURCES
    foundation/graphic/lite/hals/src/hal_tick.cpp
)

# graphic_utils
list(APPEND ace_INCLUDE_DIRECTORIES
    foundation/graphic/lite/utils/include
)

list(APPEND ace_SOURCES
    foundation/graphic/lite/utils/src/color.cpp
    foundation/graphic/lite/utils/src/file.c
    foundation/graphic/lite/utils/src/geometry2d.cpp
    foundation/graphic/lite/utils/src/graphic_math.cpp
    foundation/graphic/lite/utils/src/linux_file.c
    foundation/graphic/lite/utils/src/mem_api.cpp
    foundation/graphic/lite/utils/src/style.cpp
    foundation/graphic/lite/utils/src/transform.cpp
    foundation/graphic/lite/utils/src/version.cpp
)

# ui_shared
list(APPEND ace_INCLUDE_DIRECTORIES
    foundation/graphic/lite/frameworks/ui/include
)

list(APPEND ace_SOURCES
    foundation/graphic/lite/frameworks/ui/src/animator/animator.cpp
    foundation/graphic/lite/frameworks/ui/src/animator/easing_equation.cpp
    foundation/graphic/lite/frameworks/ui/src/animator/interpolation.cpp
    foundation/graphic/lite/frameworks/ui/src/common/graphic_startup.cpp
    foundation/graphic/lite/frameworks/ui/src/common/image.cpp
    foundation/graphic/lite/frameworks/ui/src/common/input_device_manager.cpp
    foundation/graphic/lite/frameworks/ui/src/common/screen.cpp
    foundation/graphic/lite/frameworks/ui/src/common/screen_device_proxy.cpp
    foundation/graphic/lite/frameworks/ui/src/common/task.cpp
    foundation/graphic/lite/frameworks/ui/src/common/text.cpp
    foundation/graphic/lite/frameworks/ui/src/common/typed_text.cpp
    foundation/graphic/lite/frameworks/ui/src/common/ui_text_language.cpp
    foundation/graphic/lite/frameworks/ui/src/components/root_view.cpp
    foundation/graphic/lite/frameworks/ui/src/components/text_adapter.cpp
    foundation/graphic/lite/frameworks/ui/src/components/ui_abstract_clock.cpp
    foundation/graphic/lite/frameworks/ui/src/components/ui_abstract_progress.cpp
    foundation/graphic/lite/frameworks/ui/src/components/ui_abstract_scroll.cpp
    foundation/graphic/lite/frameworks/ui/src/components/ui_analog_clock.cpp
    foundation/graphic/lite/frameworks/ui/src/components/ui_arc_label.cpp
    foundation/graphic/lite/frameworks/ui/src/components/ui_axis.cpp
    foundation/graphic/lite/frameworks/ui/src/components/ui_box_progress.cpp
    foundation/graphic/lite/frameworks/ui/src/components/ui_button.cpp
    foundation/graphic/lite/frameworks/ui/src/components/ui_canvas.cpp
    foundation/graphic/lite/frameworks/ui/src/components/ui_chart.cpp
    foundation/graphic/lite/frameworks/ui/src/components/ui_checkbox.cpp
    foundation/graphic/lite/frameworks/ui/src/components/ui_circle_progress.cpp
    foundation/graphic/lite/frameworks/ui/src/components/ui_dialog.cpp
    foundation/graphic/lite/frameworks/ui/src/components/ui_digital_clock.cpp
    foundation/graphic/lite/frameworks/ui/src/components/ui_image_animator.cpp
    foundation/graphic/lite/frameworks/ui/src/components/ui_image_view.cpp
    foundation/graphic/lite/frameworks/ui/src/components/ui_label.cpp
    foundation/graphic/lite/frameworks/ui/src/components/ui_label_button.cpp
    foundation/graphic/lite/frameworks/ui/src/components/ui_list.cpp
    foundation/graphic/lite/frameworks/ui/src/components/ui_picker.cpp
    foundation/graphic/lite/frameworks/ui/src/components/ui_radiobutton.cpp
    foundation/graphic/lite/frameworks/ui/src/components/ui_repeat_button.cpp
    foundation/graphic/lite/frameworks/ui/src/components/ui_scroll_view.cpp
    foundation/graphic/lite/frameworks/ui/src/components/ui_slider.cpp
    #foundation/graphic/lite/frameworks/ui/src/components/ui_surface_view.cpp
    foundation/graphic/lite/frameworks/ui/src/components/ui_swipe_view.cpp
    foundation/graphic/lite/frameworks/ui/src/components/ui_texture_mapper.cpp
    foundation/graphic/lite/frameworks/ui/src/components/ui_time_picker.cpp
    foundation/graphic/lite/frameworks/ui/src/components/ui_toggle_button.cpp
    foundation/graphic/lite/frameworks/ui/src/components/ui_view.cpp
    foundation/graphic/lite/frameworks/ui/src/components/ui_view_group.cpp
    foundation/graphic/lite/frameworks/ui/src/core/measure_manager.cpp
    foundation/graphic/lite/frameworks/ui/src/core/render_manager.cpp
    foundation/graphic/lite/frameworks/ui/src/core/task_manager.cpp
    foundation/graphic/lite/frameworks/ui/src/default_resource/check_box_res.cpp
    foundation/graphic/lite/frameworks/ui/src/default_resource/radio_button_res.cpp
    foundation/graphic/lite/frameworks/ui/src/default_resource/toggle_button_res.cpp
    foundation/graphic/lite/frameworks/ui/src/dfx/event_injector.cpp
    foundation/graphic/lite/frameworks/ui/src/dfx/point_event_injector.cpp
    foundation/graphic/lite/frameworks/ui/src/dfx/ui_dump_dom_tree.cpp
    foundation/graphic/lite/frameworks/ui/src/dfx/ui_screenshot.cpp
    foundation/graphic/lite/frameworks/ui/src/dock/input_device.cpp
    foundation/graphic/lite/frameworks/ui/src/dock/key_input_device.cpp
    foundation/graphic/lite/frameworks/ui/src/dock/ohos/ohos_input_device.cpp
    foundation/graphic/lite/frameworks/ui/src/dock/pointer_input_device.cpp
    foundation/graphic/lite/frameworks/ui/src/dock/virtual_input_device.cpp
    foundation/graphic/lite/frameworks/ui/src/draw/draw_arc.cpp
    foundation/graphic/lite/frameworks/ui/src/draw/draw_curve.cpp
    foundation/graphic/lite/frameworks/ui/src/draw/draw_image.cpp
    foundation/graphic/lite/frameworks/ui/src/draw/draw_label.cpp
    foundation/graphic/lite/frameworks/ui/src/draw/draw_line.cpp
    foundation/graphic/lite/frameworks/ui/src/draw/draw_rect.cpp
    foundation/graphic/lite/frameworks/ui/src/draw/draw_triangle.cpp
    foundation/graphic/lite/frameworks/ui/src/draw/draw_utils.cpp
    foundation/graphic/lite/frameworks/ui/src/events/event.cpp
    foundation/graphic/lite/frameworks/ui/src/font/ui_base_font.cpp
    foundation/graphic/lite/frameworks/ui/src/font/ui_dynamic_font.cpp
    foundation/graphic/lite/frameworks/ui/src/font/ui_font.cpp
    foundation/graphic/lite/frameworks/ui/src/font/ui_font_allocator.cpp
    foundation/graphic/lite/frameworks/ui/src/font/ui_font_cache.cpp
    foundation/graphic/lite/frameworks/ui/src/font/ui_font_vector.cpp
    foundation/graphic/lite/frameworks/ui/src/imgdecode/cache_manager.cpp
    foundation/graphic/lite/frameworks/ui/src/imgdecode/file_img_decoder.cpp
    foundation/graphic/lite/frameworks/ui/src/layout/flex_layout.cpp
    foundation/graphic/lite/frameworks/ui/src/layout/grid_layout.cpp
    foundation/graphic/lite/frameworks/ui/src/layout/list_layout.cpp
    foundation/graphic/lite/frameworks/ui/src/themes/theme.cpp
    foundation/graphic/lite/frameworks/ui/src/themes/theme_manager.cpp
    foundation/graphic/lite/frameworks/ui/src/window/iwindows_manager.cpp
    foundation/graphic/lite/frameworks/ui/src/window/window.cpp
    foundation/graphic/lite/frameworks/ui/src/window/window_impl.cpp
)

include_directories(${ace_INCLUDE_DIRECTORIES})
add_library(ace SHARED ${ace_SOURCES})

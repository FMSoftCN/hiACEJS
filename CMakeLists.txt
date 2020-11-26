cmake_minimum_required(VERSION 3.10)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_INCLUDE_PATH "${CMAKE_SOURCE_DIR}/output/root/usr/include")
set(CMAKE_LIBRARY_PATH "${CMAKE_SOURCE_DIR}/output/root/usr/lib")

find_package(JPEG REQUIRED)
find_package(PNG REQUIRED)
find_package(ZLIB REQUIRED)
find_package(Freetype 2.4.2 REQUIRED)

find_package(MbedTLS REQUIRED)
find_package(Securec REQUIRED)
find_package(MiniGUI 5.0.2 REQUIRED)

set(MINIGUI_LIBRARIES ${MiniGUI_LIBRARIES})
set(MINIGUI_INCLUDE_DIRS ${MiniGUI_INCLUDE_DIRS})

# sub-directory
add_subdirectory(src)

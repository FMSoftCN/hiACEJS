#
# 
#                           IMPORTANT NOTICE
# 
#  The following open source license statement does not apply to any
#  entity in the Exception List published by FMSoft.
# 
#  For more information, please visit:
# 
#  https://www.fmsoft.cn/exception-list
# 
#
#   This file is part of HybridOS, a developing operating system based on
#   MiniGUI. HybridOs will support embedded systems and smart IoT devices.
#
#   Copyright (C) 2020 Beijing FMSoft Technologies Co., Ltd.
#
#   This program is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
#   Or,
#
#   As this program is a library, any link to this program must follow
#   GNU General Public License version 3 (GPLv3). If you cannot accept
#   GPLv3, you need to be licensed from FMSoft.
#
#   If you have got a commercial license of this program, please use it
#   under the terms and conditions of the commercial license.
#
#   For more information about the commercial license, please refer to
#   <http://www.minigui.com/blog/minigui-licensing-policy/>.
#

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
find_package(Jerryscript REQUIRED)
find_package(MiniGUI 5.0.2 REQUIRED)

set(MINIGUI_LIBRARIES ${MiniGUI_LIBRARIES})
set(MINIGUI_INCLUDE_DIRS ${MiniGUI_INCLUDE_DIRS})

# sub-directory
add_subdirectory(src)
add_subdirectory(src/hiacejs_run)
add_subdirectory(src/appagent)
add_subdirectory(test)

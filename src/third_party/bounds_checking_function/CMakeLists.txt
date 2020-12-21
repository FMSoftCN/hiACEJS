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

project(sec_config)

list(APPEND sec_config_INCLUDE_DIRECTORIES
    include
)

list(APPEND sec_config_SOURCES
  src/vsscanf_s.c
  src/wcsncpy_s.c
  src/wmemmove_s.c
  src/swscanf_s.c
  src/vsnprintf_s.c
  src/swprintf_s.c
  src/fwscanf_s.c
  src/secureinput_a.c
  src/sprintf_s.c
  src/vfscanf_s.c
  src/snprintf_s.c
  src/wcstok_s.c
  src/secureprintoutput_w.c
  src/vfwscanf_s.c
  src/vwscanf_s.c
  src/memmove_s.c
  src/strcpy_s.c
  src/wmemcpy_s.c
  src/fscanf_s.c
  src/strcat_s.c
  src/memcpy_s.c
  src/scanf_s.c
  src/securecutil.c
  src/wcsncat_s.c
  src/vswscanf_s.c
  src/strncpy_s.c
  src/gets_s.c
  src/wcscpy_s.c
  src/vswprintf_s.c
  src/strncat_s.c
  src/strtok_s.c
  src/secureinput_w.c
  src/vscanf_s.c
  src/wcscat_s.c
  src/secureprintoutput_a.c
  src/wscanf_s.c
  src/memset_s.c
  src/sscanf_s.c
  src/vsprintf_s.c
)

include_directories(${sec_config_INCLUDE_DIRECTORIES})
add_library(sec_config SHARED ${sec_config_SOURCES})

configure_file(libsec_config.pc.in libsec_config.pc @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libsec_config.pc DESTINATION lib/pkgconfig)
install(FILES "include/securec.h" DESTINATION include)
install(FILES "include/securectype.h" DESTINATION include)
install(TARGETS sec_config DESTINATION lib)

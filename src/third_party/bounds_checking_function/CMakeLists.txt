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

install(FILES "include/securec.h" DESTINATION ${CMAKE_INSTALL_PREFIX}/include/)
install(FILES "include/securectype.h" DESTINATION ${CMAKE_INSTALL_PREFIX}/include/)
install(TARGETS sec_config DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/)

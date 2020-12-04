/*
 * Copyright (c) 2020 FMSoft.
 */

#ifndef HI_ACE_JS_H
#define HI_ACE_JS_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

bool HiAceJsRun(const char* appPath, const char* bundle, const char* fontFileName);

#ifdef __cplusplus
}
#endif

#endif  // HI_ACE_JS_H

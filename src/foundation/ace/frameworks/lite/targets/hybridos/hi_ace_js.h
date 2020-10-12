/*
 * Copyright (c) 2020 FMSoft.
 */

#ifndef HI_ACE_JS_H
#define HI_ACE_JS_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _HiAceJs* HiAceJs;

bool HiAceJsRun(const char* bundle, const char* path, HiAceJs* hi_ace_js_out);
bool HiAceJsShow(HiAceJs hi_ace_js);
bool HiAceJsHide(HiAceJs hi_ace_js);
bool HiAceJsShutdown(HiAceJs hi_ace_js);

#ifdef __cplusplus
}
#endif

#endif  // HI_ACE_JS_H

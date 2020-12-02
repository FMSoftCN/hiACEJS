#include <stddef.h>
#include <stdio.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>

#include "hi_ace_js.h"

#define LOG(fmt, ...) fprintf(stderr, "%s:%d:%s"fmt, __FILE__, __LINE__, __func__, __VA_ARGS__)

int MiniGUIMain (int argc, const char* argv[])
{
    HiAceJs hi_ace_js;
    HiAceJsRun("com.example.helloworld", "js/default", &hi_ace_js);
    LOG("%s\n", "this is log");
    return 0;
}

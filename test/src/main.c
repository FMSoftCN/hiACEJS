#include <stddef.h>
#include <stdio.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>

#include "hi_ace_js.h"

int MiniGUIMain (int argc, const char* argv[])
{
    HiAceJs hi_ace_js;
    HiAceJsRun("com.example.helloworld", "./", &hi_ace_js);
    return 0;
}

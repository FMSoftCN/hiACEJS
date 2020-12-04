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
    HiAceJsRun("./app", "com.example.helloworld", "SourceHanSansSC-Regular.otf");
    return 0;
}

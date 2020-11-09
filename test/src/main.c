#include <stddef.h>

#include "hi_ace_js.h"

int main(int argc, char ** argv)
{
    HiAceJs hi_ace_js;
    HiAceJsRun("com.example.helloworld", "js/default", &hi_ace_js);
    return 0;
}

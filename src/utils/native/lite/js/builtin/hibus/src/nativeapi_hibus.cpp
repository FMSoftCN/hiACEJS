/////////////////////////////////////////////////////////////////////////////// //
//                          IMPORTANT NOTICE
//
// The following open source license statement does not apply to any
// entity in the Exception List published by FMSoft.
//
// For more information, please visit:
//
// https://www.fmsoft.cn/exception-list
//
//////////////////////////////////////////////////////////////////////////////
/**
 \verbatim

    This file is part of HybridOS, a developing operating system based on
    MiniGUI. HybridOs will support embedded systems and smart IoT devices.

    Copyright (C) 2020 Beijing FMSoft Technologies Co., Ltd.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    Or,

    As this program is a library, any link to this program must follow
    GNU General Public License version 3 (GPLv3). If you cannot accept
    GPLv3, you need to be licensed from FMSoft.

    If you have got a commercial license of this program, please use it
    under the terms and conditions of the commercial license.

    For more information about the commercial license, please refer to
    <http://www.minigui.com/blog/minigui-licensing-policy/>.

 \endverbatim
 */

#include <limits.h>
#include <string.h>

#include "nativeapi_hibus.h"
#include "js_async_work.h"
#include "nativeapi_common.h"
#include "nativeapi_config.h"
#include "parameter.h"
#include "screen.h"
#include "ace_log.h"

#include "hibus.h"
#include "internal/jsi_internal.h"
#include "js_fwk_common.h"


namespace OHOS {
namespace ACELite {

const char HIBUS_POINTER_NAME[] = "HiBusPointer";

typedef struct
{
    char appName[128];
    char runnerName[64];
    char pathSocket[PATH_MAX];
    int fdSocket;
    hibus_conn * context;
} hibus_object_t;

void InitHiBusModule(JSIValue exports)
{
    JSI::SetModuleAPI(exports, "printInfo", NativeapiHiBus::printInfo);
}

void SetHiBusPointer(JSIValue object, hibus_object_t* hibusPointer)
{
    if (!JSI::ValueIsObject(object) || (hibusPointer == nullptr)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "SetHiBusPointer failed!");
        return;
    }

#if defined(ENABLE_JERRY)
    JSIValue hibusObj = JSI::CreateObject();
    void *nativePtr = reinterpret_cast<void *>(hibusPointer);
    jerry_set_object_native_pointer(AS_JERRY_VALUE(hibusObj), nativePtr, nullptr);
    JSI::SetNamedProperty(object, HIBUS_POINTER_NAME, hibusObj);
    JSI::ReleaseValue(hibusObj);
#else
    HILOG_ERROR(HILOG_MODULE_ACE, "SetHiBusPointer has not been implemented in this js engine!");
#endif
}

hibus_object_t* GetHiBusPointer(JSIValue object)
{
    if (!JSI::ValueIsObject(object)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "GetHiBusPointer failed!");
        return nullptr;
    }

#if defined(ENABLE_JERRY)
    void *nativePointer = nullptr;
    bool exist = jerry_get_object_native_pointer(AS_JERRY_VALUE(object), &nativePointer, nullptr);
    if (!exist || (nativePointer == nullptr)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "GetHiBusPointer get function pointer failed!");
        return nullptr;
    }
    return reinterpret_cast<hibus_object_t *>(nativePointer);
#else
    HILOG_ERROR(HILOG_MODULE_ACE, "SetHiBusPointer has not been implemented in this js engine!");
    return nullptr;
#endif
}

void NativeapiHiBus::RegistPropertyAppName(JSIValue exports)
{
    JSPropertyDescriptor desc;
    const char * const propName = "appName";
    desc.getter = GetterAppName;
    desc.setter = nullptr;
    JSI::DefineNamedProperty(exports, propName, desc);
}

JSIValue NativeapiHiBus::GetterAppName(const JSIValue thisVal, const JSIValue *args, uint8_t argsNum)
{
    JSIValue undefValue = JSI::CreateUndefined();
    if ((args == nullptr) || (argsNum == 0) || JSI::ValueIsUndefined(args[0])) {
        return undefValue;
    }

    hibus_object_t* hibus = GetHiBusPointer(args[0]);
    if (hibus == nullptr)
    {
        return undefValue;
    }

    const char* appName = hibus_conn_app_name(hibus->context);
    return JSI::CreateString(appName);
}

void NativeapiHiBus::RegistPropertyRunnerName(JSIValue exports)
{
    JSPropertyDescriptor desc;
    const char * const propName = "runnerName";
    desc.getter = GetterRunnerName;
    desc.setter = nullptr;
    JSI::DefineNamedProperty(exports, propName, desc);
}

JSIValue NativeapiHiBus::GetterRunnerName(const JSIValue thisVal, const JSIValue *args, uint8_t argsNum)
{
    JSIValue undefValue = JSI::CreateUndefined();
    if ((args == nullptr) || (argsNum == 0) || JSI::ValueIsUndefined(args[0])) {
        return undefValue;
    }

    hibus_object_t* hibus = GetHiBusPointer(args[0]);
    if (hibus == nullptr)
    {
        return undefValue;
    }

    const char* runnerName = hibus_conn_runner_name(hibus->context);
    return JSI::CreateString(runnerName);
}

void NativeapiHiBus::RegistPropertyPathSocket(JSIValue exports)
{
    JSPropertyDescriptor desc;
    const char * const propName = "pathSocket";
    desc.getter = GetterPathSocket;
    desc.setter = nullptr;
    JSI::DefineNamedProperty(exports, propName, desc);
}

JSIValue NativeapiHiBus::GetterPathSocket(const JSIValue thisVal, const JSIValue *args, uint8_t argsNum)
{
    JSIValue undefValue = JSI::CreateUndefined();
    if ((args == nullptr) || (argsNum == 0) || JSI::ValueIsUndefined(args[0])) {
        return undefValue;
    }

    hibus_object_t* hibus = GetHiBusPointer(args[0]);
    if (hibus == nullptr)
    {
        return undefValue;
    }

    return JSI::CreateString(hibus->pathSocket);
}

JSIValue NativeapiHiBus::Connect(const JSIValue thisVal, const JSIValue *args, uint8_t argsNum)
{
    JSIValue undefValue = JSI::CreateUndefined();
    if ((args == nullptr) || (argsNum == 0) || JSI::ValueIsUndefined(args[0])) {
        return undefValue;
    }

    hibus_object_t* hibusObject = (hibus_object_t*)malloc(sizeof(hibus_object_t));
    if(hibusObject == NULL)
    {
        return undefValue;
    }

    memset(hibusObject, 0, sizeof(hibus_object_t));

    switch(argsNum)
    {
        case 0:
        case 1:
        case 2:
            jerry_string_to_char_buffer(AS_JERRY_VALUE(args[0]), (jerry_char_t*)hibusObject->appName, 127);
            jerry_string_to_char_buffer(AS_JERRY_VALUE(args[1]), (jerry_char_t*)hibusObject->runnerName, 63);
            sprintf(hibusObject->pathSocket, "/var/tmp/hibus.sock");
            break;
        default:
            jerry_string_to_char_buffer(AS_JERRY_VALUE(args[0]), (jerry_char_t*)hibusObject->appName, 127);
            jerry_string_to_char_buffer(AS_JERRY_VALUE(args[1]), (jerry_char_t*)hibusObject->runnerName, 63);
            jerry_string_to_char_buffer(AS_JERRY_VALUE(args[2]), (jerry_char_t*)hibusObject->pathSocket, PATH_MAX - 1);
            break;
    }

    hibusObject->fdSocket = hibus_connect_via_unix_socket (hibusObject->pathSocket, \
            hibusObject->appName, hibusObject->runnerName, &(hibusObject->context));
    fprintf(stderr, "create object: app_name = %s, runner_name = %s, path_socket = %s, fd = %d, conn = %p\n", \
            hibusObject->appName, hibusObject->runnerName, hibusObject->pathSocket, hibusObject->fdSocket, hibusObject->context);

    if (((hibus_object_t *)hibusObject)->fdSocket >= 0)
    {
        JSIValue jsiHiBus = JSI::CreateObject();
        SetHiBusPointer(jsiHiBus, hibusObject);
        return jsiHiBus;
    }

    free(hibusObject);
    return undefValue;
}

JSIValue NativeapiHiBus::Disconnect(const JSIValue thisVal, const JSIValue *args, uint8_t argsNum)
{
    JSIValue undefValue = JSI::CreateUndefined();
    if ((args == nullptr) || (argsNum == 0) || JSI::ValueIsUndefined(args[0])) {
        return undefValue;
    }

    hibus_object_t* hibus = GetHiBusPointer(args[0]);
    if (hibus == nullptr)
    {
        return undefValue;
    }

    return JSI::CreateNumber(hibus_disconnect(hibus->context));
}

JSIValue NativeapiHiBus::Send(const JSIValue thisVal, const JSIValue *args, uint8_t argsNum)
{
    int length = -1;
    JSIValue undefValue = JSI::CreateUndefined();
    if ((args == nullptr) || (argsNum < 2) || JSI::ValueIsUndefined(args[0])) {
        return undefValue;
    }

    hibus_object_t* hibus = GetHiBusPointer(args[0]);
    if (hibus == nullptr)
    {
        return undefValue;
    }

    char *content = JSI::ValueToString(args[1]);
    if (content == nullptr)
    {
        return undefValue;
    }

    if (hibus->fdSocket >= 0 && hibus->context)
    {
        length = hibus_send_text_packet (hibus->context, content, strlen(content));
    }
    return  JSI::CreateNumber (length);
}

JSIValue NativeapiHiBus::Read(const JSIValue thisVal, const JSIValue *args, uint8_t argsNum)
{
    JSIValue undefValue = JSI::CreateUndefined();
    if ((args == nullptr) || (argsNum < 2) || JSI::ValueIsUndefined(args[0])) {
        return undefValue;
    }

    hibus_object_t* hibus = GetHiBusPointer(args[0]);
    if (hibus == nullptr)
    {
        return undefValue;
    }

    unsigned int length = 4096;
    char content[4096] = {0};
    int timeout = 0;
    timeout = JSI::ValueToNumber(args[1]);
    memset(content, 0, 4096);

    if (hibus->fdSocket >= 0 && hibus->context)
    {
        fd_set rfds;
        struct timeval tv;
        int result = 0;
        int maxfd = 0;

        FD_ZERO(&rfds);
        FD_SET(hibus->fdSocket, &rfds);
        maxfd = hibus->fdSocket + 1;

        tv.tv_sec = timeout / 1000;
        tv.tv_usec = (timeout % 1000) * 1000;

        result = select(maxfd, &rfds, NULL, NULL, &tv);
        if(result > 0)
        {
            length = hibus_read_packet (hibus->context, (void *) content, &length);
        }
    }

    if(length)
        return JSI::CreateString (content);

    return undefValue;
}

JSIValue NativeapiHiBus::printInfo(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum)
{
    fprintf(stderr, "##################################### nativeapi_hibus printInfo isCalled\n");
    return JSI::CreateUndefined();
}
} // ACELite
} // OHOS

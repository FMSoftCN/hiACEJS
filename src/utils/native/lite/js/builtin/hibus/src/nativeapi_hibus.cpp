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

#include "hibus_wrapper.h"


namespace OHOS {
namespace ACELite {

const char HIBUS_POINTER_NAME[] = "HiBusPointer";

void InitHiBusModule(JSIValue exports)
{
    JSI::SetModuleAPI(exports, "printInfo", NativeapiHiBus::printInfo);
    JSI::SetModuleAPI(exports, "connect", NativeapiHiBus::Connect);
    JSI::SetModuleAPI(exports, "disconnect", NativeapiHiBus::Disconnect);
    JSI::SetModuleAPI(exports, "send", NativeapiHiBus::Send);
    JSI::SetModuleAPI(exports, "read", NativeapiHiBus::Read);
    JSI::SetModuleAPI(exports, "subscribeEvent", NativeapiHiBus::SubscribeEvent);
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
    HiBusWrapper* hibus = HiBusWrapper::GetInstance(); 
    const char* value = hibus->GetAppName();
    return value ? JSI::CreateString(value) : JSI::CreateUndefined();
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
    HiBusWrapper* hibus = HiBusWrapper::GetInstance(); 
    const char* value = hibus->GetRunnerName();
    return value ? JSI::CreateString(value) : JSI::CreateUndefined();
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
    HiBusWrapper* hibus = HiBusWrapper::GetInstance(); 
    const char* value = hibus->GetPathToSocket();
    return value ? JSI::CreateString(value) : JSI::CreateUndefined();
}

JSIValue NativeapiHiBus::Connect(const JSIValue thisVal, const JSIValue *args, uint8_t argsNum)
{
    JSIValue undefValue = JSI::CreateUndefined();
    if ((args == nullptr) || (argsNum == 0) || JSI::ValueIsUndefined(args[0])) {
        return undefValue;
    }

    HiBusWrapper* hibus = HiBusWrapper::GetInstance(); 
    char appName[APP_NAME_LEN + 1] = {0};
    char runnerName[RUNNER_NAME_LEN + 1] = {0};
    char pathToSocket[PATH_MAX] = {0};

    switch(argsNum)
    {
        case 0:
        case 1:
        case 2:
            jerry_string_to_char_buffer(AS_JERRY_VALUE(args[0]), (jerry_char_t*)appName, APP_NAME_LEN);
            jerry_string_to_char_buffer(AS_JERRY_VALUE(args[1]), (jerry_char_t*)runnerName, RUNNER_NAME_LEN);
            sprintf(pathToSocket, "/var/tmp/hibus.sock");
            break;
        default:
            jerry_string_to_char_buffer(AS_JERRY_VALUE(args[0]), (jerry_char_t*)appName, APP_NAME_LEN);
            jerry_string_to_char_buffer(AS_JERRY_VALUE(args[1]), (jerry_char_t*)runnerName, RUNNER_NAME_LEN);
            jerry_string_to_char_buffer(AS_JERRY_VALUE(args[2]), (jerry_char_t*)pathToSocket, PATH_MAX - 1);
            break;
    }

    bool result = hibus->ConnectViaUnixSocket(pathToSocket, appName, runnerName);
    return JSI::CreateBoolean(result);
}

JSIValue NativeapiHiBus::Disconnect(const JSIValue thisVal, const JSIValue *args, uint8_t argsNum)
{
    HiBusWrapper* hibus = HiBusWrapper::GetInstance(); 
    return JSI::CreateBoolean(hibus->Disconnect());
}

JSIValue NativeapiHiBus::Send(const JSIValue thisVal, const JSIValue *args, uint8_t argsNum)
{
    JSIValue undefValue = JSI::CreateUndefined();
    if ((args == nullptr) || (argsNum == 0) || JSI::ValueIsUndefined(args[0])) {
        return undefValue;
    }

    char *content = JSI::ValueToString(args[0]);
    if (content == nullptr)
    {
        return undefValue;
    }

    HiBusWrapper* hibus = HiBusWrapper::GetInstance(); 
    int ret = hibus->SendTextPacket(content, strlen(content));
    return  JSI::CreateNumber (ret);
}

JSIValue NativeapiHiBus::Read(const JSIValue thisVal, const JSIValue *args, uint8_t argsNum)
{
    JSIValue undefValue = JSI::CreateUndefined();
    if ((args == nullptr) || (argsNum == 0) || JSI::ValueIsUndefined(args[0])) {
        return undefValue;
    }

    HiBusWrapper* hibus = HiBusWrapper::GetInstance(); 
    if (!hibus->IsConnected())
    {
        return undefValue;
    }

    unsigned int length = 4096;
    char content[4096] = {0};
    int timeout = 0;
    timeout = JSI::ValueToNumber(args[0]);
    memset(content, 0, 4096);

    int fdSocket = hibus->GetSocketFd();
    if (fdSocket >= 0)
    {
        fd_set rfds;
        struct timeval tv;
        int result = 0;
        int maxfd = 0;

        FD_ZERO(&rfds);
        FD_SET(fdSocket, &rfds);
        maxfd = fdSocket + 1;

        tv.tv_sec = timeout / 1000;
        tv.tv_usec = (timeout % 1000) * 1000;

        result = select(maxfd, &rfds, NULL, NULL, &tv);
        if(result > 0)
        {
            int ret = hibus->ReadPacket(content, &length);
            if (ret == 0)
                return JSI::CreateString (content);
        }
    }
    return undefValue;
}

JSIValue NativeapiHiBus::SubscribeEvent(const JSIValue thisVal, const JSIValue *args, uint8_t argsNum)
{
    JSIValue undefValue = JSI::CreateUndefined();
    if ((args == nullptr) || (argsNum < 3)
            || JSI::ValueIsUndefined(args[0])
            || JSI::ValueIsUndefined(args[1])
            || JSI::ValueIsUndefined(args[2])) {
        return undefValue;
    }
    char* endpoint = JSI::ValueToString(args[0]);
    char* bubbleName = JSI::ValueToString(args[1]);

    fprintf(stderr, "SubscribeEvent|endpoint=%s|bubbleName=%s\n", endpoint, bubbleName);
    JSIValue retEndpoint = JSI::CreateString(endpoint);
    JSIValue retBubbleName = JSI::CreateString(bubbleName);
    JSIValue retBubbleData = JSI::CreateString("{\"bubbleDataKey\":\"bubbleDataValue\"}");

    JSIValue argv[ARGC_THREE] = {retEndpoint, retBubbleName, retBubbleData};
    JSI::CallFunction(args[2], thisVal, argv, ARGC_THREE);

    JSI::ReleaseValueList(retEndpoint, retBubbleName, retBubbleData);
    JSI::ReleaseString(endpoint);
    JSI::ReleaseString(bubbleName);
    return JSI::CreateUndefined();
}

JSIValue NativeapiHiBus::printInfo(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum)
{
    fprintf(stderr, "##################################### nativeapi_hibus printInfo isCalled\n");
    return JSI::CreateUndefined();
}
} // ACELite
} // OHOS
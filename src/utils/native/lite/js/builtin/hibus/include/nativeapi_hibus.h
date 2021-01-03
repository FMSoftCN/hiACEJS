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


#ifndef JS_NATIVE_API_HI_BUS_H
#define JS_NATIVE_API_HI_BUS_H

#include "jsi/jsi.h"

namespace OHOS {
namespace ACELite {
class NativeapiHiBus {
public:
    NativeapiHiBus() {}
    ~NativeapiHiBus() {}

    // appName property
    static void RegistPropertyAppName(JSIValue exports);
    static JSIValue GetterAppName(const JSIValue thisVal, const JSIValue *args, uint8_t argsNum);

    // runnerName property
    static void RegistPropertyRunnerName(JSIValue exports);
    static JSIValue GetterRunnerName(const JSIValue thisVal, const JSIValue *args, uint8_t argsNum);

    // pathSocket property
    static void RegistPropertyPathSocket(JSIValue exports);
    static JSIValue GetterPathSocket(const JSIValue thisVal, const JSIValue *args, uint8_t argsNum);

    // connect function
    static JSIValue Connect(const JSIValue thisVal, const JSIValue *args, uint8_t argsNum);
    // disconnect function
    static JSIValue Disconnect(const JSIValue thisVal, const JSIValue *args, uint8_t argsNum);
    // send function
    static JSIValue Send(const JSIValue thisVal, const JSIValue *args, uint8_t argsNum);
    // read function
    static JSIValue Read(const JSIValue thisVal, const JSIValue *args, uint8_t argsNum);

    // only for test
    static JSIValue printInfo(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum);


    // int hibus_connect_via_unix_socket (const char* path_to_socket, const char* app_name, const char* runner_name, hibus_conn** conn);
    // int hibus_disconnect (hibus_conn* conn);
    //
    // typedef void (*hibus_event_handler)(hibus_conn* conn, const char* from_endpoint, const char* bubble_name, const char* bubble_data);
    // int hibus_subscribe_event (hibus_conn* conn, const char* endpoint, const char* bubble_name, hibus_event_handler event_handler);
    // int hibus_unsubscribe_event (hibus_conn* conn, const char* endpoint, const char* bubble_name);
    //
    // typedef void (*hibus_result_handler)(hibus_conn* conn, const char* from_endpoint, const char* method_name, int ret_code, const char* ret_value);
    // int hibus_call_procedure (hibus_conn* conn, const char* endpoint, const char* method_name, const char* method_praram, time_t ret_time_expected, hibus_result_handler result_handler);

};
} // ACELite
} // OHOS
#endif /* JS_NATIVE_API_HI_BUS_H */

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

#ifndef HYBRIDOS_SURFACE_H
#define HYBRIDOS_SURFACE_H

#include "client/isurface.h"
#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>

#include <linux/limits.h>

#include "hibus.h"

#define APP_NAME_LEN 127
#define RUNNER_NAME_LEN 127
#define HOST_NAME_LEN 63

namespace OHOS {
class HiBusWrapper {
public:
    ~HiBusWrapper();

    static HiBusWrapper* GetInstance()
    {
        static HiBusWrapper hibusWrapper;
        return &hibusWrapper;
    }


    bool IsConnected() { return m_hiBusConn != nullptr; }

    // int hibus_connect_via_unix_socket (const char* path_to_socket, const char* app_name, const char* runner_name, hibus_conn** conn);
    bool ConnectViaUnixSocket(const char* pathToSocket, const char* appName, const char* runnerName);
    // int hibus_connect_via_web_socket (const char* host_name, int port, const char* app_name, const char* runner_name, hibus_conn** conn);
    bool ConnectViaWebSocket(const char* hostName, int port, const char* appName, const char* runnerName);
    // int hibus_disconnect (hibus_conn* conn);
    bool Disconnect();

    // const char* hibus_conn_srv_host_name (hibus_conn* conn);
    const char* GetSrvHostName();
    // const char* hibus_conn_own_host_name (hibus_conn* conn);
    const char* GetOwnHostName();
    // const char* hibus_conn_app_name (hibus_conn* conn);
    const char* GetAppName();
    // const char* hibus_conn_runner_name (hibus_conn* conn);
    const char* GetRunnerName();
    // int hibus_conn_socket_fd (hibus_conn* conn);
    int GetSocketFd();
    // int hibus_conn_socket_type (hibus_conn* conn);
    int GetSocketType();

    // #define MAX_LEN_PAYLOAD     4096
    // int hibus_read_packet (hibus_conn* conn, void* packet_buf, unsigned int *packet_len);
    int ReadPacket(void* packetBuf, unsigned int* packetLen);
    // int hibus_read_packet_alloc (hibus_conn* conn, void **packet, unsigned int *packet_len);
    int ReadPacketAlloc(void **packet, unsigned int* packetLen);
    // int hibus_send_text_packet (hibus_conn* conn, const char* text, unsigned int txt_len);
    int SendTextPacket(const char* text, unsigned int txtLen);


    // typedef void (*hibus_event_handler)(hibus_conn* conn, const char* from_endpoint, const char* bubble_name, const char* bubble_data);
    // int hibus_subscribe_event (hibus_conn* conn, const char* endpoint, const char* bubble_name, hibus_event_handler event_handler);
    int SubscribeEvent(const char* endpoint, const char* bubbleName, hibus_event_handler event_handler);
    // int hibus_unsubscribe_event (hibus_conn* conn, const char* endpoint, const char* bubble_name);
    int UnsubscribeEvent(const char* endpoint, const char* bubbleName);

    // typedef void (*hibus_result_handler)(hibus_conn* conn, const char* from_endpoint, const char* method_name, int ret_code, const char* ret_value);
    // int hibus_call_procedure (hibus_conn* conn, const char* from_endpoint, const char* from_method, const char* method_param, int time_expected, hibus_result_handler result_handler);
    int CallProcedure (const char* endpoint, const char* methodName, const char* methodParam, int timeExpected, hibus_result_handler resultHandler);
    // int hibus_call_procedure_and_wait (hibus_conn* conn, const char* endpoint, const char* method_name, const char* method_param, int time_expected, int *ret_code, char** ret_value);
    int CallProcedureAndWait(const char* endpoint, const char* methodName, const char* methodParam, int timeExpected, int *retCode, char** retValue);

    const char* GetPathToSocket() { return m_hiBusConn ? m_pathToSocket : nullptr; }

    // int hibus_wait_and_dispatch_packet (hibus_conn* conn, int timeout_ms);
    int WaitAndDispatchPacket(int timeoutMs);
private:
    HiBusWrapper();

private:
    char m_appName[APP_NAME_LEN + 1];
    char m_runnerName[RUNNER_NAME_LEN + 1];
    char m_pathToSocket[PATH_MAX];

    char m_hostName[HOST_NAME_LEN + 1];
    int m_port;


    hibus_conn* m_hiBusConn;
    int m_hiBusFd;
};
}
#endif

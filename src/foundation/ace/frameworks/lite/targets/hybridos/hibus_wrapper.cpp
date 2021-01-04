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

#include "hibus_wrapper.h"

namespace OHOS {
HiBusWrapper::HiBusWrapper()
 : m_appName{0}    
 , m_runnerName{0}
 , m_pathToSocket{0} 
 , m_hostName{0} 
 , m_port(0)
 , m_hiBusConn(nullptr)
 , m_hiBusFd(-1)
{
}

HiBusWrapper::~HiBusWrapper()
{
}

bool HiBusWrapper::ConnectViaUnixSocket(const char* pathToSocket, const char* appName, const char* runnerName)
{
    m_hiBusFd =  hibus_connect_via_unix_socket(pathToSocket, appName, runnerName, &m_hiBusConn);
    if (m_hiBusFd >= 0)
    {
        strcpy(m_pathToSocket, pathToSocket);
        strcpy(m_appName, appName);
        strcpy(m_runnerName, runnerName);
        return true;
    }
    m_hiBusConn = nullptr;
    m_hiBusFd = -1;
    return false;
}

bool HiBusWrapper::ConnectViaWebSocket(const char* hostName, int port, const char* appName, const char* runnerName)
{
    m_hiBusFd = hibus_connect_via_web_socket(hostName, port, appName, runnerName, &m_hiBusConn);
    if (m_hiBusFd >= 0)
    {
        strcpy(m_hostName, hostName);
        m_port = port;
        strcpy(m_appName, appName);
        strcpy(m_runnerName, runnerName);
        return true;
    }
    m_hiBusConn = nullptr;
    m_hiBusFd = -1;
    return false;
}

bool HiBusWrapper::Disconnect()
{
    if (m_hiBusConn)
    {
        hibus_disconnect(m_hiBusConn);
    }

    m_appName[0] = 0;
    m_runnerName[0] = 0;
    m_pathToSocket[0] = 0;
    m_hostName[0] = 0;
    m_port = 0;
    m_hiBusConn = nullptr;
    m_hiBusFd = -1;
    return true;
}

const char* HiBusWrapper::GetSrvHostName()
{
    return m_hiBusConn ?hibus_conn_srv_host_name (m_hiBusConn) : nullptr;
}

const char* HiBusWrapper::GetOwnHostName()
{
    return m_hiBusConn ? hibus_conn_own_host_name (m_hiBusConn) : nullptr;
}

const char* HiBusWrapper::GetAppName()
{
    return m_hiBusConn ? hibus_conn_app_name (m_hiBusConn) : nullptr;
}

const char* HiBusWrapper::GetRunnerName()
{
    return m_hiBusConn ? hibus_conn_runner_name (m_hiBusConn) : nullptr;
}

int HiBusWrapper::GetSocketFd()
{
    return m_hiBusConn ? hibus_conn_socket_fd (m_hiBusConn) : -1;
}

int HiBusWrapper::GetSocketType()
{
    return m_hiBusConn ? hibus_conn_socket_type (m_hiBusConn) : -1;
}

int HiBusWrapper::ReadPacket(void* packetBuf, unsigned int* packetLen)
{
    return m_hiBusConn ? hibus_read_packet (m_hiBusConn, packetBuf, packetLen) : -1;
}

int HiBusWrapper::ReadPacketAlloc(void **packet, unsigned int* packetLen)
{
    return m_hiBusConn ? hibus_read_packet_alloc (m_hiBusConn, packet, packetLen) : -1;
}

int HiBusWrapper::SendTextPacket(const char* text, unsigned int txtLen)
{
    return m_hiBusConn ? hibus_send_text_packet (m_hiBusConn, text, txtLen) : -1;
}

int HiBusWrapper::SubscribeEvent(const char* endpoint, const char* bubbleName, hibus_event_handler event_handler)
{
    return m_hiBusConn ? hibus_subscribe_event (m_hiBusConn, endpoint, bubbleName, event_handler) : -1;
}

int HiBusWrapper::UnsubscribeEvent(const char* endpoint, const char* bubbleName)
{
    return m_hiBusConn ? hibus_unsubscribe_event (m_hiBusConn, endpoint, bubbleName) : -1;
}

int HiBusWrapper::CallProcedure (const char* endpoint, const char* methodName, const char* methodParam, int timeExpected, hibus_result_handler resultHandler)
{
    return m_hiBusConn ? hibus_call_procedure (m_hiBusConn, endpoint, methodName, methodParam, timeExpected, resultHandler) : -1;
}

int HiBusWrapper::CallProcedureAndWait (const char* endpoint, const char* methodName, const char* methodParam, int timeExpected, int *retCode, char** retValue)
{
    return m_hiBusConn ? hibus_call_procedure_and_wait (m_hiBusConn, endpoint, methodName, methodParam, timeExpected, retCode, retValue) : -1;
}


}

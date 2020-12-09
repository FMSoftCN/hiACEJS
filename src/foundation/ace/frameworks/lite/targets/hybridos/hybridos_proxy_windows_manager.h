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

#ifndef HYBRIDOS_PROXY_WINDOWS_MANAGER_H
#define HYBRIDOS_PROXY_WINDOWS_MANAGER_H

#include "client/iwindows_manager.h"
#include "client/isurface.h"

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>


#define MSG_PROCESS_ABILITY_EVENT     (MSG_USER + 100 + 0)

namespace OHOS {
class HybridosProxyWindowsManager : public IWindowsManager {
public:
    HybridosProxyWindowsManager();
    virtual ~HybridosProxyWindowsManager() {}

    int Init() override;
    IWindow* CreateWindow(const LiteWinConfig& config) override;
    void RemoveWindow(IWindow* win) override;
    void GetEventData(DeviceData* data) override;
    void Screenshot() override;
    void SetScreenshotListener(ScreenshotListener* listener) override;
    void Run();
    void ProcessAbilityEvent();
    void InvalidateRect(const Rect& invalidatedArea);
    void DispatchEvent();

private:
    bool CheckWinIdIsAvailable();
    int32_t GetUniqueWinId();
    void RecycleWinId(int32_t id);

    static LRESULT WindowsManagerWndProc(HWND, UINT, WPARAM, LPARAM);
    LRESULT WndProc(HWND, UINT, WPARAM, LPARAM);

private:
    RECT m_windowRect;
    HWND m_hMainWnd;
    HDC m_memDC;
    uint32_t m_mainWndId;

    uint32_t m_winIdStorage;

    int m_mouseX;
    int m_mouseY;
    BOOL m_lastMouseLeftButtonStatus;
};
}
#endif

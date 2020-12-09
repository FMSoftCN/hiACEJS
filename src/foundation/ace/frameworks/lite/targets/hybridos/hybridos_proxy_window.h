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

#ifndef HYBRIDOS_PROXY_WINDOW_H
#define HYBRIDOS_PROXY_WINDOW_H

#include "client/iwindow.h"
#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>

namespace OHOS {
class HybridosProxyWindow : public IWindow {
public:
    HybridosProxyWindow(HWND hwnd, HDC hdc, RECT* rect, int32_t windowId);
    virtual ~HybridosProxyWindow();

    int Init() override;
    void Destroy() override;
    void Show() override;
    void Hide() override;
    void Resize(int16_t width, int16_t height) override;
    void MoveTo(int16_t x, int16_t y) override;
    void RaiseToTop() override;
    void LowerToBottom() override;
    ISurface* GetSurface() override;
    int32_t GetWindowId() override;
    void Update() override;

private:
    int32_t id_;
    ISurface* surface_;
    HWND m_hwnd;
    HDC m_memDC;
    RECT* m_rect;
};
}
#endif


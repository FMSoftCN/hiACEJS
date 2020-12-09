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

#include "hybridos_proxy_window.h"
#include "hybridos_surface.h"
#include "graphic_log.h"
#include "surface.h"
#include "ace_log.h"

namespace OHOS {
HybridosProxyWindow::HybridosProxyWindow(HWND hwnd, HDC hdc, RECT* rect, int32_t windowId)
    : id_(windowId), surface_(nullptr), m_hwnd(hwnd), m_memDC(hdc), m_rect(rect)
{
    HILOG_DEBUG(HILOG_MODULE_ACE, "%s", __func__);
}

HybridosProxyWindow::~HybridosProxyWindow()
{
    HILOG_DEBUG(HILOG_MODULE_ACE, "%s", __func__);
    if (surface_) {
        delete surface_;
        surface_ = nullptr;
    }
}

int HybridosProxyWindow::Init()
{
    HILOG_DEBUG(HILOG_MODULE_ACE, "%s", __func__);
    return 0;
}

void HybridosProxyWindow::Destroy()
{
    HILOG_DEBUG(HILOG_MODULE_ACE, "%s", __func__);
}

void HybridosProxyWindow::Show()
{
    HILOG_DEBUG(HILOG_MODULE_ACE, "%s", __func__);
    ShowWindow(m_hwnd, SW_SHOWNORMAL);
}

void HybridosProxyWindow::Hide()
{
    HILOG_DEBUG(HILOG_MODULE_ACE, "%s", __func__);
}

void HybridosProxyWindow::Resize(int16_t width, int16_t height)
{
    HILOG_DEBUG(HILOG_MODULE_ACE, "%s", __func__);
}

void HybridosProxyWindow::MoveTo(int16_t x, int16_t y)
{
    HILOG_DEBUG(HILOG_MODULE_ACE, "%s", __func__);
}

void HybridosProxyWindow::RaiseToTop()
{
    HILOG_DEBUG(HILOG_MODULE_ACE, "%s", __func__);
}

void HybridosProxyWindow::LowerToBottom()
{
    HILOG_DEBUG(HILOG_MODULE_ACE, "%s", __func__);
}

ISurface* HybridosProxyWindow::GetSurface()
{
    if (surface_ == nullptr) {
        surface_ = new HybridosSurface(m_memDC, m_rect);
    }
    return surface_;
}

int32_t HybridosProxyWindow::GetWindowId()
{
    return id_;
}

void HybridosProxyWindow::Update()
{
}
}


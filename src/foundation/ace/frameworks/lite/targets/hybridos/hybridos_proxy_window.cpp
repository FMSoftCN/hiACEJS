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
    InvalidateRect(m_hwnd, NULL, TRUE);
}
}


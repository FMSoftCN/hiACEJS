#include "hybridos_proxy_window.h"
#include "graphic_log.h"
#include "surface.h"
#include "ace_log.h"

namespace OHOS {
HybridosProxyWindow::HybridosProxyWindow(HWND hwnd)
    : id_(INVALID_WINDOW_ID), surface_(nullptr), m_hwnd(hwnd)
{
    HILOG_DEBUG(HILOG_MODULE_ACE, "%s:%d:%s", __FILE__, __LINE__, __func__);
}

HybridosProxyWindow::~HybridosProxyWindow()
{
    HILOG_DEBUG(HILOG_MODULE_ACE, "%s:%d:%s", __FILE__, __LINE__, __func__);
    if (surface_) {
        delete surface_;
        surface_ = nullptr;
    }
}

int HybridosProxyWindow::Init()
{
    HILOG_DEBUG(HILOG_MODULE_ACE, "%s:%d:%s", __FILE__, __LINE__, __func__);
    return 0;
}

void HybridosProxyWindow::Destroy()
{
    HILOG_DEBUG(HILOG_MODULE_ACE, "%s:%d:%s", __FILE__, __LINE__, __func__);
}

void HybridosProxyWindow::Show()
{
    HILOG_DEBUG(HILOG_MODULE_ACE, "%s:%d:%s", __FILE__, __LINE__, __func__);
    ShowWindow(m_hwnd, SW_SHOWNORMAL);
}

void HybridosProxyWindow::Hide()
{
    HILOG_DEBUG(HILOG_MODULE_ACE, "%s:%d:%s", __FILE__, __LINE__, __func__);
}

void HybridosProxyWindow::Resize(int16_t width, int16_t height)
{
    HILOG_DEBUG(HILOG_MODULE_ACE, "%s:%d:%s", __FILE__, __LINE__, __func__);
}

void HybridosProxyWindow::MoveTo(int16_t x, int16_t y)
{
    HILOG_DEBUG(HILOG_MODULE_ACE, "%s:%d:%s", __FILE__, __LINE__, __func__);
}

void HybridosProxyWindow::RaiseToTop()
{
    HILOG_DEBUG(HILOG_MODULE_ACE, "%s:%d:%s", __FILE__, __LINE__, __func__);
}

void HybridosProxyWindow::LowerToBottom()
{
    HILOG_DEBUG(HILOG_MODULE_ACE, "%s:%d:%s", __FILE__, __LINE__, __func__);
}

ISurface* HybridosProxyWindow::GetSurface()
{
//    HILOG_DEBUG(HILOG_MODULE_ACE, "%s:%d:%s", __FILE__, __LINE__, __func__);
    return nullptr;
}

int32_t HybridosProxyWindow::GetWindowId()
{
    HILOG_DEBUG(HILOG_MODULE_ACE, "%s:%d:%s", __FILE__, __LINE__, __func__);
    return INVALID_WINDOW_ID;
}

void HybridosProxyWindow::Update()
{
    HILOG_DEBUG(HILOG_MODULE_ACE, "%s:%d:%s", __FILE__, __LINE__, __func__);
}
}


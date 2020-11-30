#include "hybridos_proxy_window.h"
#include "graphic_log.h"
#include "surface.h"

namespace OHOS {
HybridosProxyWindow::HybridosProxyWindow()
    : id_(INVALID_WINDOW_ID), surface_(nullptr)
{
}

HybridosProxyWindow::~HybridosProxyWindow()
{
    if (surface_) {
        delete surface_;
        surface_ = nullptr;
    }
}

int HybridosProxyWindow::Init()
{
    return 0;
}

void HybridosProxyWindow::Destroy()
{
}

void HybridosProxyWindow::Show()
{
}

void HybridosProxyWindow::Hide()
{
}

void HybridosProxyWindow::Resize(int16_t width, int16_t height)
{
}

void HybridosProxyWindow::MoveTo(int16_t x, int16_t y)
{
}

void HybridosProxyWindow::RaiseToTop()
{
}

void HybridosProxyWindow::LowerToBottom()
{
}

ISurface* HybridosProxyWindow::GetSurface()
{
    return nullptr;
}

int32_t HybridosProxyWindow::GetWindowId()
{
    return INVALID_WINDOW_ID;
}

void HybridosProxyWindow::Update()
{
}
}


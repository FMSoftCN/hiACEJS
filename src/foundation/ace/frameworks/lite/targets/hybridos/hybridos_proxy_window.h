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
    HybridosProxyWindow(HWND hwnd, HDC hdc, RECT* rect);
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


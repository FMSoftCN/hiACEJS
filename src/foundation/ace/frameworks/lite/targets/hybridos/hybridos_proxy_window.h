#ifndef HYBRIDOS_PROXY_WINDOW_H
#define HYBRIDOS_PROXY_WINDOW_H

#include "client/iwindow.h"

namespace OHOS {
class HybridosProxyWindow : public IWindow {
public:
    HybridosProxyWindow();
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
};
}
#endif

#ifndef HYBRIDOS_PROXY_WINDOWS_MANAGER_H
#define HYBRIDOS_PROXY_WINDOWS_MANAGER_H

#include "client/iwindows_manager.h"
#include "client/isurface.h"

namespace OHOS {
class HybridosProxyWindowsManager : public IWindowsManager {
public:
    HybridosProxyWindowsManager() {}
    virtual ~HybridosProxyWindowsManager() {}

    int Init() override;
    IWindow* CreateWindow(const LiteWinConfig& config) override;
    void RemoveWindow(IWindow* win) override;
    void GetEventData(DeviceData* data) override;
    void Screenshot() override;
    void SetScreenshotListener(ScreenshotListener* listener) override;
};
}
#endif

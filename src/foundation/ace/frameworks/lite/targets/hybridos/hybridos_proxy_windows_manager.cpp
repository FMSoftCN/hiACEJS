#include "hybridos_proxy_windows_manager.h"

#include "color.h"
#include "graphic_log.h"

namespace OHOS {
int HybridosProxyWindowsManager::Init()
{
    GRAPHIC_LOGI("Init");
    return 0;
}

IWindow* HybridosProxyWindowsManager::CreateWindow(const LiteWinConfig& config)
{
    return nullptr;
}

void HybridosProxyWindowsManager::RemoveWindow(IWindow* window)
{
}

void HybridosProxyWindowsManager::GetEventData(DeviceData* data)
{
}

void HybridosProxyWindowsManager::Screenshot()
{
}

void HybridosProxyWindowsManager::SetScreenshotListener(ScreenshotListener* listener)
{
}
}


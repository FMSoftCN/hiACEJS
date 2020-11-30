#include "hybridos_proxy_windows_manager.h"

#include "color.h"
#include "graphic_log.h"
#include "ace_log.h"

namespace OHOS {
int HybridosProxyWindowsManager::Init()
{
    HILOG_DEBUG(HILOG_MODULE_ACE, "%s:%d:%s", __FILE__, __LINE__, __func__);
    return 0;
}

IWindow* HybridosProxyWindowsManager::CreateWindow(const LiteWinConfig& config)
{
    HILOG_DEBUG(HILOG_MODULE_ACE, "%s:%d:%s", __FILE__, __LINE__, __func__);
    return nullptr;
}

void HybridosProxyWindowsManager::RemoveWindow(IWindow* window)
{
    HILOG_DEBUG(HILOG_MODULE_ACE, "%s:%d:%s", __FILE__, __LINE__, __func__);
}

void HybridosProxyWindowsManager::GetEventData(DeviceData* data)
{
    HILOG_DEBUG(HILOG_MODULE_ACE, "%s:%d:%s", __FILE__, __LINE__, __func__);
}

void HybridosProxyWindowsManager::Screenshot()
{
    HILOG_DEBUG(HILOG_MODULE_ACE, "%s:%d:%s", __FILE__, __LINE__, __func__);
}

void HybridosProxyWindowsManager::SetScreenshotListener(ScreenshotListener* listener)
{
    HILOG_DEBUG(HILOG_MODULE_ACE, "%s:%d:%s", __FILE__, __LINE__, __func__);
}
}


#include "client/iwindows_manager.h"
#include "hybridos_proxy_windows_manager.h"

namespace OHOS {
IWindowsManager* IWindowsManager::GetInstance()
{
    static HybridosProxyWindowsManager winManager;
    return &winManager;
}
}


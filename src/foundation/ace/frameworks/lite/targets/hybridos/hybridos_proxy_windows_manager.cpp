#include "hybridos_proxy_windows_manager.h"
#include "hybridos_proxy_window.h"

#include "color.h"
#include "graphic_log.h"
#include "ace_log.h"

namespace OHOS {

static LRESULT MainProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    return DefaultMainWinProc(hWnd, message, wParam, lParam);
}

int HybridosProxyWindowsManager::Init()
{
    HILOG_DEBUG(HILOG_MODULE_ACE, "%s:%d:%s", __FILE__, __LINE__, __func__);
    return 0;
}

IWindow* HybridosProxyWindowsManager::CreateWindow(const LiteWinConfig& config)
{
    HILOG_DEBUG(HILOG_MODULE_ACE, "%s:%d:%s", __FILE__, __LINE__, __func__);

    m_ScreenRect = GetScreenRect();

#ifdef _MGRM_PROCESSES
    JoinLayer(NAME_DEF_LAYER , "hiAceJS" , 0 , 0);
#endif

    MAINWINCREATE CreateInfo;
    CreateInfo.dwStyle = WS_VISIBLE;
    CreateInfo.dwExStyle = WS_EX_NONE;
    CreateInfo.hMenu = 0;
    CreateInfo.hCursor = GetSystemCursor(0);
    CreateInfo.spCaption = "";
    CreateInfo.hIcon = 0;
    CreateInfo.MainWindowProc = MainProc;
    CreateInfo.lx = m_ScreenRect.left;
    CreateInfo.ty = m_ScreenRect.top;
    CreateInfo.rx = m_ScreenRect.right;
    CreateInfo.by = m_ScreenRect.bottom;
    CreateInfo.iBkColor = COLOR_lightwhite;
    CreateInfo.dwAddData = 0;
    CreateInfo.hHosting = HWND_DESKTOP;

    m_hMainWnd = CreateMainWindow (&CreateInfo);
    return new HybridosProxyWindow(m_hMainWnd);
}

void HybridosProxyWindowsManager::RemoveWindow(IWindow* window)
{
    HILOG_DEBUG(HILOG_MODULE_ACE, "%s:%d:%s", __FILE__, __LINE__, __func__);
    window->Hide();
    window->Destroy();
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

void HybridosProxyWindowsManager::Run()
{
    MSG Msg;
    while (GetMessage(&Msg, m_hMainWnd)) {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
}

}


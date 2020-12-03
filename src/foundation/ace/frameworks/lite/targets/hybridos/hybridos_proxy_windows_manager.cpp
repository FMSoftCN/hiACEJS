#include "hybridos_proxy_windows_manager.h"
#include "hybridos_proxy_window.h"

#include "color.h"
#include "graphic_log.h"
#include "ace_log.h"

#include "ability_event_handler.h"
#include "core/render_manager.h"

#define UI_TASK_TIMER_ID 1001

namespace OHOS {

LRESULT HybridosProxyWindowsManager::WindowsManagerWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (HybridosProxyWindowsManager* wm = reinterpret_cast<HybridosProxyWindowsManager*>(GetWindowAdditionalData2(hWnd)))
        return wm->WndProc(hWnd, message, wParam, lParam);
    return DefaultMainWinProc(hWnd, message, wParam, lParam);
}

LRESULT HybridosProxyWindowsManager::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case MSG_TIMER:
            if (wParam == UI_TASK_TIMER_ID)
            {
                RenderManager::GetInstance().JobExecute();
            }
            break;

        case MSG_PAINT:
            {
                HDC hdc = BeginPaint (hWnd);
                BitBlt (m_memDc, 0, 0, RECTW(m_ScreenRect), RECTH(m_ScreenRect), hdc, 0, 0, 0);
                EndPaint (hWnd, hdc);
            }
            break;

        case MSG_PROCESS_ABILITY_EVENT:
            HILOG_DEBUG(HILOG_MODULE_ACE, "MSG_PROCESS_ABILITY_EVENT");
            AbilityEventHandler::GetCurrentHandler()->ProcessEvent();
            break;
    }
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
    CreateInfo.MainWindowProc = HybridosProxyWindowsManager::WindowsManagerWndProc;
    CreateInfo.lx = m_ScreenRect.left;
    CreateInfo.ty = m_ScreenRect.top;
    CreateInfo.rx = m_ScreenRect.right;
    CreateInfo.by = m_ScreenRect.bottom;
    CreateInfo.iBkColor = COLOR_lightwhite;
    CreateInfo.dwAddData = 0;
    CreateInfo.hHosting = HWND_DESKTOP;

    m_hMainWnd = CreateMainWindow (&CreateInfo);
    SetWindowAdditionalData2(m_hMainWnd, (DWORD)this);

    m_memDc = CreateMemDC (RECTW(m_ScreenRect), RECTH(m_ScreenRect),
                        32, MEMDC_FLAG_HWSURFACE,
                        0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

    SetTimer(m_hMainWnd, UI_TASK_TIMER_ID, 1);
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


void HybridosProxyWindowsManager::ProcessAbilityEvent()
{
    SendMessage(m_hMainWnd, MSG_PROCESS_ABILITY_EVENT, 0, 0);
}

}


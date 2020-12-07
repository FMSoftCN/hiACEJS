#include "hybridos_proxy_windows_manager.h"
#include "hybridos_proxy_window.h"
#include "hybridos_input_device.h"

#include "color.h"
#include "graphic_log.h"
#include "ace_log.h"

#include "ability_event_handler.h"
#include "core/render_manager.h"
#include "animator/animator.h"
#include "dock/input_device.h"

#define UI_TASK_TIMER_ID 1001

namespace OHOS {

const uint8_t MAX_WINDOW_NUMBLE = 32;
const uint32_t WINDOW_ID_FULL_STORAGE = 0xFFFFFFFF;

HybridosProxyWindowsManager::HybridosProxyWindowsManager()
 : m_hMainWnd(HWND_INVALID)
 , m_memDC(HDC_INVALID)
 , m_winIdStorage(0) 
 , m_mainWndId(0)
{
}

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
                AnimatorManager::GetInstance()->JobExecute();
            }
            break;

        case MSG_PAINT:
            {
                HILOG_DEBUG(HILOG_MODULE_ACE, "paint");
                HDC hdc = BeginPaint (hWnd);
                BitBlt (m_memDC, 0, 0, RECTW(m_ScreenRect), RECTH(m_ScreenRect), hdc, 0, 0, 0);
                EndPaint (hWnd, hdc);
            }
            break;

        case MSG_LBUTTONDOWN:
        case MSG_MBUTTONDOWN:
        case MSG_RBUTTONDOWN:
            {
                int mouseX = LOWORD(lParam);
                int mouseY = HIWORD(lParam);
                ScreenToClient (hWnd, &mouseX, &mouseY);
                DeviceData data;
                data.point.x = mouseX;
                data.point.y = mouseY;
                data.state = InputDevice::STATE_PRESS;
                data.winId = m_mainWndId;
                HybridosInputDevice::GetInstance()->Dispatch(data);
            }
            break;

        case MSG_LBUTTONUP:
        case MSG_MBUTTONUP:
        case MSG_RBUTTONUP:
            {
                int mouseX = LOWORD(lParam);
                int mouseY = HIWORD(lParam);
                ScreenToClient (hWnd, &mouseX, &mouseY);
                DeviceData data;
                data.point.x = mouseX;
                data.point.y = mouseY;
                data.state = InputDevice::STATE_RELEASE;
                data.winId = m_mainWndId;
                HybridosInputDevice::GetInstance()->Dispatch(data);
            }
            break;

        case MSG_MOUSEMOVE:
            {
                int mouseX = LOWORD(lParam);
                int mouseY = HIWORD(lParam);
                ScreenToClient (hWnd, &mouseX, &mouseY);
                DeviceData data;
                data.point.x = mouseX;
                data.point.y = mouseY;
                if (wParam & KS_LEFTBUTTON 
                        || wParam & KS_RIGHTBUTTON
                        || wParam & KS_MIDDLEBUTTON)
                {
                    data.state = InputDevice::STATE_PRESS;
                }
                else
                {
                    data.state = InputDevice::STATE_RELEASE;
                }
                data.winId = m_mainWndId;
                HybridosInputDevice::GetInstance()->Dispatch(data);
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
    HILOG_DEBUG(HILOG_MODULE_ACE, "%s x=%d|y=%d|width=%d|height=%d", __func__, config.rect.GetX(), config.rect.GetY(), config.rect.GetWidth(), config.rect.GetHeight());

    m_ScreenRect.left = 0;
    m_ScreenRect.top = 0;
    m_ScreenRect.right = config.rect.GetWidth();
    m_ScreenRect.bottom = config.rect.GetHeight();

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
    m_mainWndId = GetUniqueWinId();

    m_memDC = CreateMemDC (RECTW(m_ScreenRect), RECTH(m_ScreenRect),
                        32, MEMDC_FLAG_HWSURFACE,
                        0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

    SetTimer(m_hMainWnd, UI_TASK_TIMER_ID, 1);
    return new HybridosProxyWindow(m_hMainWnd, m_memDC, &m_ScreenRect, m_mainWndId);
}

void HybridosProxyWindowsManager::RemoveWindow(IWindow* window)
{
    HILOG_DEBUG(HILOG_MODULE_ACE, "%s:%d:%s", __FILE__, __LINE__, __func__);
    window->Hide();
    window->Destroy();
}

bool HybridosProxyWindowsManager::CheckWinIdIsAvailable()
{
    if (m_winIdStorage == WINDOW_ID_FULL_STORAGE) {
        GRAPHIC_LOGE("reach max window num!");
        return false;
    }
    return true;
}

int32_t HybridosProxyWindowsManager::GetUniqueWinId()
{
    static uint8_t winId = 0;
    if (CheckWinIdIsAvailable() == false) {
        return INVALID_WINDOW_ID;
    }
    while (m_winIdStorage & (1 << winId)) {
        winId++;
        winId %= MAX_WINDOW_NUMBLE;
    }
    m_winIdStorage |= (1 << winId);
    return winId;
}

void HybridosProxyWindowsManager::RecycleWinId(int32_t id)
{
    if (id == INVALID_WINDOW_ID) {
        return;
    }
    m_winIdStorage &= (~(1 << static_cast<uint32_t>(id)));
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


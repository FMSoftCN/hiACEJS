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
 , m_mainWndId(0)
 , m_winIdStorage(0) 
 , m_mouseX(0)
 , m_mouseY(0)
 , m_lastMouseLeftButtonStatus(FALSE)
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
                DispatchEvent();
                RenderManager::GetInstance().JobExecute();
                AnimatorManager::GetInstance()->JobExecute();
            }
            break;

        case MSG_PAINT:
            {
                HDC hdc = BeginPaint (hWnd);
                BitBlt (m_memDC, 0, 0, RECTW(m_windowRect), RECTH(m_windowRect), hdc, 0, 0, 0);
                EndPaint (hWnd, hdc);
            }
            break;

        case MSG_LBUTTONDOWN:
            if(GetCapture() == HWND_NULL) {
                SetCapture(m_hMainWnd);

                int mouseX = LOWORD(lParam);
                int mouseY = HIWORD(lParam);
                ScreenToClient (hWnd, &mouseX, &mouseY);
                m_mouseX = mouseX;
                m_mouseY = mouseY;
            }
            break;

        case MSG_LBUTTONUP:
            if(GetCapture() == m_hMainWnd)
            {
                ReleaseCapture();

                int mouseX = LOWORD(lParam);
                int mouseY = HIWORD(lParam);
                ScreenToClient (hWnd, &mouseX, &mouseY);
                m_mouseX = mouseX;
                m_mouseY = mouseY;
            }
            break;

        case MSG_MOUSEMOVE:
            if(GetCapture() == m_hMainWnd)
            {
                int mouseX = LOWORD(lParam);
                int mouseY = HIWORD(lParam);
                ScreenToClient (hWnd, &mouseX, &mouseY);
                m_mouseX = mouseX;
                m_mouseY = mouseY;
            }
            break;

        case MSG_PROCESS_ABILITY_EVENT:
            HILOG_DEBUG(HILOG_MODULE_ACE, "MSG_PROCESS_ABILITY_EVENT");
            AbilityEventHandler::GetCurrentHandler()->ProcessEvent();
            break;
    }
    return DefaultMainWinProc(hWnd, message, wParam, lParam);
}

void HybridosProxyWindowsManager::InvalidateRect(const Rect& invalidatedArea)
{
    RECT rect;
    rect.left = invalidatedArea.GetX();
    rect.top = invalidatedArea.GetY();
    rect.right = rect.left + invalidatedArea.GetWidth();
    rect.bottom = rect.top + invalidatedArea.GetHeight();
    ::InvalidateRect(m_hMainWnd, &rect, FALSE);
}

void HybridosProxyWindowsManager::DispatchEvent()
{
    BOOL leftButtonStatus = GetKeyStatus(SCANCODE_LEFTBUTTON);
    if (leftButtonStatus || leftButtonStatus != m_lastMouseLeftButtonStatus)
    {
        m_lastMouseLeftButtonStatus = leftButtonStatus;
        DeviceData data;
        data.point.x = m_mouseX;
        data.point.y = m_mouseY;
        data.state = leftButtonStatus ? InputDevice::STATE_PRESS :  InputDevice::STATE_RELEASE;
        data.winId = m_mainWndId;
        HybridosInputDevice::GetInstance()->Dispatch(data);
    }
}

int HybridosProxyWindowsManager::Init()
{
    HILOG_ERROR(HILOG_MODULE_ACE, "%s", __func__);
    return 0;
}

IWindow* HybridosProxyWindowsManager::CreateWindow(const LiteWinConfig& config)
{
    RECT screenRect = GetScreenRect();

    m_windowRect.left = 0;
    m_windowRect.top = 0;
    m_windowRect.right = config.rect.GetWidth();
    m_windowRect.bottom = config.rect.GetHeight();

    HILOG_DEBUG(HILOG_MODULE_ACE, "%s screen rect(x=0,y=0,w=%d,h=%d)", __func__, RECTW(screenRect), RECTH(screenRect));
    HILOG_DEBUG(HILOG_MODULE_ACE, "%s window rect(x=0,y=0,w=%d,h=%d)", __func__, RECTW(m_windowRect), RECTH(m_windowRect));


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
    CreateInfo.lx = m_windowRect.left;
    CreateInfo.ty = m_windowRect.top;
    CreateInfo.rx = m_windowRect.right;
    CreateInfo.by = m_windowRect.bottom;
    CreateInfo.iBkColor = COLOR_lightwhite;
    CreateInfo.dwAddData = 0;
    CreateInfo.hHosting = HWND_DESKTOP;

    m_hMainWnd = CreateMainWindow (&CreateInfo);
    SetWindowAdditionalData2(m_hMainWnd, (DWORD)this);
    m_mainWndId = GetUniqueWinId();

    m_memDC = CreateMemDC (RECTW(m_windowRect), RECTH(m_windowRect),
                        32, MEMDC_FLAG_HWSURFACE,
                        0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

    SetTimer(m_hMainWnd, UI_TASK_TIMER_ID, 1);
    return new HybridosProxyWindow(m_hMainWnd, m_memDC, &m_windowRect, m_mainWndId);
}

void HybridosProxyWindowsManager::RemoveWindow(IWindow* window)
{
    HILOG_DEBUG(HILOG_MODULE_ACE, "%s", __func__);
    RecycleWinId(window->GetWindowId());
    window->Hide();
    window->Destroy();
}

bool HybridosProxyWindowsManager::CheckWinIdIsAvailable()
{
    if (m_winIdStorage == WINDOW_ID_FULL_STORAGE) {
        HILOG_ERROR(HILOG_MODULE_ACE, "%s", __func__);
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
    HILOG_ERROR(HILOG_MODULE_ACE, "%s", __func__);
}

void HybridosProxyWindowsManager::Screenshot()
{
    HILOG_ERROR(HILOG_MODULE_ACE, "%s", __func__);
}

void HybridosProxyWindowsManager::SetScreenshotListener(ScreenshotListener* listener)
{
    HILOG_ERROR(HILOG_MODULE_ACE, "%s", __func__);
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


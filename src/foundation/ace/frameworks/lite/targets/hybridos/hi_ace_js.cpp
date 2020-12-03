/*
 * Copyright (c) 2020 FMSoft.
 */

#include "hi_ace_js.h"

#include <memory>

#include <common/screen_device_proxy.h>
#include <ability.h>
#include <ability_state.h>
#include "ability_loader.h"
#include "ability_env_impl.h"

#include "pthread.h"
#include "sys/prctl.h"
#include "unistd.h"

#include "ability_event_handler.h"
#include "ace_log.h"
#include "graphic_startup.h"
#include "js_ability.h"
#include "task_manager.h"
#include "ui_font_header.h"

#include "hybridos_proxy_windows_manager.h"

constexpr static char FONT_PATH[] = "/storage/data/";
constexpr static int UI_TASK_HANDLER_PERIOD = 10 * 1000; // UI task sleep period is 10ms
constexpr static char UI_TASK_THREAD_NAME[] = "UIJobFunc";
constexpr static char ACE_ABILITY_NAME[] = "AceAbility";

static uint32_t g_fontPsramBaseAddr[OHOS::MIN_FONT_PSRAM_LENGTH / 4];
static OHOS::AbilityEventHandler* g_eventHandler = nullptr;

void* UIJobFunc(void* arg)
{
    prctl(PR_SET_NAME, UI_TASK_THREAD_NAME);

    auto handler = static_cast<OHOS::AbilityEventHandler*>(arg);
    if (handler == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "EventHandler is nullptr, fail to start loop");
        return nullptr;
    }

    int ret = pthread_detach(pthread_self());
    if (ret != 0) {
        HILOG_WARN(HILOG_MODULE_ACE, "UIJobFunc detach failed: %{public}d", ret);
    }

    while (true) {
        handler->PostTask([] {
            OHOS::JobManager::GetInstance()->JobHandler();
        });
        usleep(UI_TASK_HANDLER_PERIOD);
    }
    return nullptr;
}

void HiAceJsHandleLifecycleTransaction(OHOS::Ability &ability, const Want &want, int state)
{
    // Switch INITIAL state to INACTIVE state
    if (ability.GetState() == STATE_INITIAL) {
        ability.OnStart(want);
    }

    // Switch ACTIVE state to INACTIVE state
    if (ability.GetState() == STATE_ACTIVE) {
        ability.OnInactive();
    }

    switch (state) {
        case STATE_INITIAL: {
            if (ability.GetState() == STATE_INACTIVE) {
                ability.OnBackground();
            }
            ability.OnStop();
            break;
        }
        case STATE_INACTIVE: {
            // Not support transact from BACKGROUND to INACTIVE state
            break;
        }
        case STATE_ACTIVE: {
            ability.OnActive(want);
            break;
        }
        case STATE_BACKGROUND: {
            if (ability.GetState() == STATE_INACTIVE) {
                ability.OnBackground();
            }
            break;
        }
        default: {
            HILOG_ERROR(HILOG_MODULE_APP, "Unknown target state: %{public}d", state);
            break;
        }
    }
}

bool HiAceJsRun(const char* bundle, const char* path, HiAceJs* hi_ace_js_out)
{
    if (hi_ace_js_out == nullptr) {
        return false;
    }

    OHOS::Ability *ability = nullptr;
    OHOS::GraphicStartUp::Init();
    OHOS::GraphicStartUp::InitFontEngine(reinterpret_cast<uintptr_t>(g_fontPsramBaseAddr), OHOS::MIN_FONT_PSRAM_LENGTH,
        const_cast<char *>(FONT_PATH), DEFAULT_VECTOR_FONT_FILENAME);

    auto screenDevice = new OHOS::ScreenDevice();
    OHOS::ScreenDeviceProxy::GetInstance()->SetDevice(screenDevice);
    ability = OHOS::AbilityLoader::GetInstance().GetAbilityByName(ACE_ABILITY_NAME);

    g_eventHandler = new OHOS::AbilityEventHandler();

    ability->Init(0, 0, true);

    AppInfo appInfo = {};
    appInfo.bundleName = bundle;
    appInfo.srcPath = path;
    appInfo.isNativeApp = true;

    OHOS::AbilityEnvImpl::GetInstance().SetAppInfo(appInfo);
    Want want;
    HiAceJsHandleLifecycleTransaction(*ability, want, STATE_ACTIVE);

    ((OHOS::HybridosProxyWindowsManager*)OHOS::IWindowsManager::GetInstance())->Run();

    return true;
}

bool HiAceJsShow(HiAceJs hi_ace_js)
{
    if (hi_ace_js != nullptr) {
        auto js_ability = reinterpret_cast<OHOS::ACELite::JSAbility*>(hi_ace_js);
        js_ability->Show();
        return true;
    }
    return false;
}

bool HiAceJsHide(HiAceJs hi_ace_js)
{
    if (hi_ace_js != nullptr) {
        auto js_ability = reinterpret_cast<OHOS::ACELite::JSAbility*>(hi_ace_js);
        js_ability->Show();
        return true;
    }
    return false;
}

bool HiAceJsShutdown(HiAceJs hi_ace_js)
{
    if (hi_ace_js != nullptr) {
        auto js_ability = reinterpret_cast<OHOS::ACELite::JSAbility*>(hi_ace_js);
        js_ability->TransferToDestroy();
        delete js_ability;
    }
    return false;
}

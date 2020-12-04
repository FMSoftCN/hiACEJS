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

constexpr static char FONT_PATH[] = "./assets/fonts/";
constexpr static int UI_TASK_HANDLER_PERIOD = 10 * 1000; // UI task sleep period is 10ms
constexpr static char UI_TASK_THREAD_NAME[] = "UIJobFunc";
constexpr static char ACE_ABILITY_NAME[] = "AceAbility";

static uint32_t g_fontPsramBaseAddr[OHOS::MIN_FONT_PSRAM_LENGTH / 4];
static OHOS::AbilityEventHandler* g_eventHandler = nullptr;

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

bool HiAceJsRun(const char* appPath, const char* bundle, const char* fontFileName)
{
    if (appPath == nullptr || bundle == nullptr || fontFileName == nullptr)
    {
        HILOG_ERROR(HILOG_MODULE_APP, "invalid param!(appPath=%s|bundle=%s|fontFileName=%s)", appPath, bundle, fontFileName);
        return false;
    }

    char srcPath[PATH_MAX] = {0};
    char fontPath[PATH_MAX] = {0};
    sprintf(srcPath, "%s/%s", appPath, bundle);
    sprintf(fontPath, "%s/assets/fonts/", srcPath);

    HILOG_INFO(HILOG_MODULE_APP, "src path=%s", srcPath);
    HILOG_INFO(HILOG_MODULE_APP, "bundle=%s", bundle);
    HILOG_INFO(HILOG_MODULE_APP, "font path=%s", fontPath);
    HILOG_INFO(HILOG_MODULE_APP, "font file=%s", fontFileName);

    OHOS::Ability *ability = nullptr;
    OHOS::GraphicStartUp::Init();
    OHOS::GraphicStartUp::InitFontEngine(reinterpret_cast<uintptr_t>(g_fontPsramBaseAddr), OHOS::MIN_FONT_PSRAM_LENGTH,
        const_cast<char *>(fontPath), fontFileName);

    auto screenDevice = new OHOS::ScreenDevice();
    OHOS::ScreenDeviceProxy::GetInstance()->SetDevice(screenDevice);
    ability = OHOS::AbilityLoader::GetInstance().GetAbilityByName(ACE_ABILITY_NAME);

    g_eventHandler = new OHOS::AbilityEventHandler();

    ability->Init(0, 0, true);

    AppInfo appInfo = {};
    appInfo.bundleName = bundle;
    appInfo.srcPath = srcPath;
    appInfo.isNativeApp = true;

    OHOS::AbilityEnvImpl::GetInstance().SetAppInfo(appInfo);
    Want want;
    HiAceJsHandleLifecycleTransaction(*ability, want, STATE_ACTIVE);

    ((OHOS::HybridosProxyWindowsManager*)OHOS::IWindowsManager::GetInstance())->Run();

    return true;
}

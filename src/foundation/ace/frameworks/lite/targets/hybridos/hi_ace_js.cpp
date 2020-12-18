///////////////////////////////////////////////////////////////////////////////
//
//                          IMPORTANT NOTICE
//
// The following open source license statement does not apply to any
// entity in the Exception List published by FMSoft.
//
// For more information, please visit:
//
// https://www.fmsoft.cn/exception-list
//
//////////////////////////////////////////////////////////////////////////////
/**
 \verbatim

    This file is part of HybridOS, a developing operating system based on
    MiniGUI. HybridOs will support embedded systems and smart IoT devices.

    Copyright (C) 2020 Beijing FMSoft Technologies Co., Ltd.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    Or,

    As this program is a library, any link to this program must follow
    GNU General Public License version 3 (GPLv3). If you cannot accept
    GPLv3, you need to be licensed from FMSoft.

    If you have got a commercial license of this program, please use it
    under the terms and conditions of the commercial license.

    For more information about the commercial license, please refer to
    <http://www.minigui.com/blog/minigui-licensing-policy/>.

 \endverbatim
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

constexpr static char DEFAULT_FONT_PATH[] = "/usr/share/fonts/";
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

bool HiAceJsRun(const char* appPath, const char* bundle, const char* fontPath, const char* fontName)
{
    if (appPath == nullptr || bundle == nullptr)
    {
        HILOG_ERROR(HILOG_MODULE_APP, "invalid param!(appPath=%s|bundle=%s)", appPath, bundle);
        return false;
    }

    char srcPath[PATH_MAX] = {0};
    sprintf(srcPath, "%s/%s", appPath, bundle);


    if (fontPath == nullptr)
    {
        fontPath = DEFAULT_FONT_PATH;
    }

    if (fontName == nullptr)
    {
        fontName = DEFAULT_VECTOR_FONT_FILENAME;
    }

    HILOG_INFO(HILOG_MODULE_APP, "src path=%s", srcPath);
    HILOG_INFO(HILOG_MODULE_APP, "bundle=%s", bundle);
    HILOG_INFO(HILOG_MODULE_APP, "font path=%s", fontPath);
    HILOG_INFO(HILOG_MODULE_APP, "font file=%s", fontName);

    OHOS::Ability *ability = nullptr;
    OHOS::GraphicStartUp::Init();
    OHOS::GraphicStartUp::InitFontEngine(reinterpret_cast<uintptr_t>(g_fontPsramBaseAddr), OHOS::MIN_FONT_PSRAM_LENGTH,
        const_cast<char *>(fontPath), fontName);

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

    ((OHOS::HybridosProxyWindowsManager*)OHOS::IWindowsManager::GetInstance())->ProcessAbilityEvent();
    ((OHOS::HybridosProxyWindowsManager*)OHOS::IWindowsManager::GetInstance())->Run();

    return true;
}

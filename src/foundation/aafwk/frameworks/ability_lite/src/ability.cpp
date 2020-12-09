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

#include "ability.h"

#include <ability_state.h>
#include "ability_window.h"

#include "log.h"

namespace OHOS {
void Ability::OnStart(const Want &want)
{
    HILOG_INFO(HILOG_MODULE_APP, "Ability OnStart");
    if (abilityState_ != STATE_INITIAL) {
        HILOG_ERROR(HILOG_MODULE_APP, "Start ability error, state: %{public}d", abilityState_);
        exit(-1);
    }

    DispatchAbilityLifecycle(START, &want);
    if (abilityWindow_ != nullptr) {
        abilityWindow_->OnPostAbilityStart();
    }
    abilityState_ = STATE_INACTIVE;
}

void Ability::OnInactive()
{
    HILOG_INFO(HILOG_MODULE_APP, "Ability OnInactive");
    if (abilityState_ != STATE_ACTIVE) {
        HILOG_ERROR(HILOG_MODULE_APP, "Inactive ability error, state: %{public}d", abilityState_);
        exit(-1);
    }

    DispatchAbilityLifecycle(INACTIVE);
    abilityState_ = STATE_INACTIVE;
}

void Ability::OnActive(const Want &want)
{
    HILOG_INFO(HILOG_MODULE_APP, "Ability OnActive");
    HILOG_INFO(HILOG_MODULE_APP, "Ability OnActive");
    if ((abilityState_ != STATE_INACTIVE) && (abilityState_ != STATE_BACKGROUND)) {
        HILOG_ERROR(HILOG_MODULE_APP, "Active ability error, state: %{public}d", abilityState_);
        exit(-1);
    }

    DispatchAbilityLifecycle(ACTIVE, &want);
    if ((abilityWindow_ != nullptr) && (abilityState_ == STATE_BACKGROUND)) {
        abilityWindow_->OnPostAbilityActive();
    }
    abilityState_ = STATE_ACTIVE;
}

void Ability::OnBackground()
{
    HILOG_INFO(HILOG_MODULE_APP, "Ability OnBackground");
    if (abilityState_ != STATE_INACTIVE) {
        HILOG_ERROR(HILOG_MODULE_APP, "Background ability error, state: %{public}d", abilityState_);
        exit(-1);
    }

    DispatchAbilityLifecycle(BACKGROUND);
    if (abilityWindow_ != nullptr) {
        abilityWindow_->OnPostAbilityBackground();
    }
    abilityState_ = STATE_BACKGROUND;
}

void Ability::OnStop()
{
    HILOG_INFO(HILOG_MODULE_APP, "Ability OnStop");
    if (abilityState_ != STATE_BACKGROUND) {
        HILOG_ERROR(HILOG_MODULE_APP, "Stop ability error, state: %{public}d", abilityState_);
        exit(-1);
    }

    DispatchAbilityLifecycle(STOP);
    if (abilityWindow_ != nullptr) {
        abilityWindow_->OnPostAbilityStop();
        delete abilityWindow_;
    }
    abilityWindow_ = nullptr;
    abilityState_ = STATE_INITIAL;
}

void Ability::OnDisconnect(const Want &want)
{
    HILOG_INFO(HILOG_MODULE_APP, "Ability OnDisconnect");
}

void Ability::SetMainRoute(const std::string &entry)
{
    HILOG_INFO(HILOG_MODULE_APP, "Ability SetMainRoute");
}

void Ability::SetUIContent(RootView *rootView)
{
    HILOG_INFO(HILOG_MODULE_APP, "Ability SetUIContent");
    if (abilityWindow_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_APP, "AbilityWindow is null, fail to SetUIContent");
        exit(-1);
    }

    abilityWindow_->SetRootView(rootView);
}

void Ability::Dump(const std::string &extra)
{
    HILOG_INFO(HILOG_MODULE_APP, "Ability Dump");
}

void Ability::Init(uint64_t token, int abilityType, bool isNativeApp)
{
    HILOG_INFO(HILOG_MODULE_APP, "Ability Init");
    abilityWindow_ = new AbilityWindow();

    abilityType_ = abilityType;
    token_ = token;
    abilityState_ = STATE_INITIAL;
}

int Ability::TerminateAbility()
{
    HILOG_INFO(HILOG_MODULE_APP, "Ability TerminateAbility");
    return 0;
}

void Ability::DispatchAbilityLifecycle(Action action, const Want *want)
{
}

} // namespace OHOS

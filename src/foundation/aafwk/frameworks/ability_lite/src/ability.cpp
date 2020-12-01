/*
 * Copyright (c) 2020 FMSoft.
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

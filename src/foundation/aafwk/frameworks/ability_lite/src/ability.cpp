/*
 * Copyright (c) 2020 FMSoft.
 */

#include "ability.h"

#include "log.h"

namespace OHOS {
void Ability::OnStart(const Want &want)
{
    HILOG_INFO(HILOG_MODULE_APP, "Ability OnStart");
}

void Ability::OnInactive()
{
    HILOG_INFO(HILOG_MODULE_APP, "Ability OnInactive");
}

void Ability::OnActive(const Want &want)
{
    HILOG_INFO(HILOG_MODULE_APP, "Ability OnActive");
}

void Ability::OnBackground()
{
    HILOG_INFO(HILOG_MODULE_APP, "Ability OnBackground");
}

void Ability::OnStop()
{
    HILOG_INFO(HILOG_MODULE_APP, "Ability OnStop");
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
}

void Ability::Dump(const std::string &extra)
{
    HILOG_INFO(HILOG_MODULE_APP, "Ability Dump");
}

int Ability::TerminateAbility()
{
    HILOG_INFO(HILOG_MODULE_APP, "Ability TerminateAbility");
    return 0;
}

} // namespace OHOS

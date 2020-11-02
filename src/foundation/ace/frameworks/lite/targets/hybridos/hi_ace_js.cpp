/*
 * Copyright (c) 2020 FMSoft.
 */

#include "hi_ace_js.h"

#include <memory>

#include "js_ability.h"

bool HiAceJsRun(const char* bundle, const char* path, HiAceJs* hi_ace_js_out)
{
    if (hi_ace_js_out == nullptr) {
        return false;
    }

    auto js_ability = std::make_unique<OHOS::ACELite::JSAbility>();
    js_ability->Launch(const_cast<char*>(path), bundle, 0xff);
    *hi_ace_js_out = reinterpret_cast<HiAceJs>(js_ability.release());
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

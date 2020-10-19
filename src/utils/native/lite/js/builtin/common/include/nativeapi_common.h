/*
 * Copyright (c) 2020 FMSoft.
 */

#ifndef JS_NATIVE_API_COMMON_H
#define JS_NATIVE_API_COMMON_H

#include "jsi/jsi.h"

namespace OHOS {
namespace ACELite {
struct FuncParams {
    JSIValue args = JSI::CreateUndefined();
    JSIValue thisVal = JSI::CreateUndefined();
    bool flag = false;
};

class NativeapiCommon {
public:
    static void FailCallBack(const JSIValue thisVal, const JSIValue args, int ret);
    static void SuccessCallBack(const JSIValue thisVal, const JSIValue args, JSIValue jsiValue);
    static bool IsValidJSIValue(const JSIValue* args, uint8_t argsNum);
private:
    NativeapiCommon() {}
    ~NativeapiCommon() {}
};
}
}

#endif /* JS_NATIVE_API_CALLBACK_H */

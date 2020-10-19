/*
 * Copyright (c) 2020 FMSoft.
 */

#ifndef JS_NATIVE_API_KV_H
#define JS_NATIVE_API_KV_H

#include "jsi/jsi.h"

namespace OHOS {
namespace ACELite {
class NativeapiKv {
public:
    NativeapiKv() {}
    ~NativeapiKv() {}
    static JSIValue Get(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum);
    static JSIValue Set(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum);
    static JSIValue Delete(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum);
    static JSIValue Clear(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum);
};
} // ACELite
} // OHOS
#endif // JS_NATIVE_API_KV_H

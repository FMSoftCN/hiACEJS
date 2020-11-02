/*
 * Copyright (c) 2020 FMSoft.
 */

#ifndef JS_NATIVE_API_DEVICE_INFO_H
#define JS_NATIVE_API_DEVICE_INFO_H

#include "jsi/jsi.h"

namespace OHOS {
namespace ACELite {
class NativeapiDeviceInfo {
public:
    NativeapiDeviceInfo() {}
    ~NativeapiDeviceInfo() {}

    static JSIValue GetDeviceInfo(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum);
};
} // ACELite
} // OHOS
#endif /* JS_NATIVE_API_DEVICE_INFO_H */

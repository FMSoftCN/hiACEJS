/*
 * Copyright (c) 2020 FMSoft.
 */

#ifndef JS_NATIVE_API_FS_H
#define JS_NATIVE_API_FS_H

#include "jsi/jsi.h"
#include "nativeapi_config.h"

namespace OHOS {
namespace ACELite {
class NativeapiFs {
public:
    NativeapiFs() {}
    ~NativeapiFs() {}

    static JSIValue MoveFile(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum);
    static JSIValue CopyFile(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum);
    static JSIValue DeleteFile(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum);
    static JSIValue GetFileList(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum);
    static JSIValue GetFileInfo(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum);
    static JSIValue WriteTextFile(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum);
    static JSIValue ReadTextFile(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum);
    static JSIValue Access(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum);
    static JSIValue CreateDir(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum);
    static JSIValue RemoveDir(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum);

#if (JS_FWK_TYPEDARRAY == NATIVE_FEATURE_ON)
    static JSIValue ReadArrayFile(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum);
    static JSIValue WriteArrayFile(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum);
#endif /* JS_FWK_TYPEDARRAY */
};
} // ACELite
} // OHOS

#endif /* JS_NATIVE_API_FS_H */

/////////////////////////////////////////////////////////////////////////////// //
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

/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "nativeapi_deviceinfo.h"
#include "js_async_work.h"
#include "nativeapi_common.h"
#include "nativeapi_config.h"
#include "parameter.h"
#include "screen.h"

namespace OHOS {
namespace ACELite {
namespace {
JSIValue ExecuteAsyncWork(const JSIValue thisVal, const JSIValue* args,
    uint8_t argsNum, AsyncWorkHandler ExecuteFunc, bool flag = false)
{
    JSIValue undefValue = JSI::CreateUndefined();
    if (!NativeapiCommon::IsValidJSIValue(args, argsNum)) {
        return undefValue;
    }
    FuncParams* params = new FuncParams();
    if (params == nullptr) {
        return undefValue;
    }
    params->thisVal = JSI::AcquireValue(thisVal);
    params->args = JSI::AcquireValue(args[0]);
    params->flag = flag;
    JsAsyncWork::DispatchAsyncWork(ExecuteFunc, reinterpret_cast<void *>(params));
    return undefValue;
}

void ExecuteGetInfo(void* data)
{
    FuncParams* params = reinterpret_cast<FuncParams *>(data);
    if (params == nullptr) {
        return;
    }
    JSIValue args = params->args;
    JSIValue thisVal = params->thisVal;
    char* brand = GetBrand();
    if (brand == nullptr) {
        NativeapiCommon::FailCallBack(args, thisVal, ERROR_CODE_GENERAL);
        JSI::ReleaseValueList(args, thisVal, ARGS_END);
        delete params;
        return;
    }
    char* manufacture = GetManufacture();
    if (manufacture == nullptr) {
        free(brand);
        NativeapiCommon::FailCallBack(args, thisVal, ERROR_CODE_GENERAL);
        JSI::ReleaseValueList(args, thisVal, ARGS_END);
        delete params;
        return;
    }
    char* model = GetProductModel();
    if (model == nullptr) {
        free(brand);
        free(manufacture);
        NativeapiCommon::FailCallBack(args, thisVal, ERROR_CODE_GENERAL);
        JSI::ReleaseValueList(args, thisVal, ARGS_END);
        delete params;
        return;
    }
    JSIValue result = JSI::CreateObject();
    JSI::SetStringProperty(result, "brand", brand);
    JSI::SetStringProperty(result, "manufacturer", manufacture);
    JSI::SetStringProperty(result, "model", model);
    JSI::SetStringProperty(result, "product", model);
    Screen &screen = Screen::GetInstance();
    JSI::SetNumberProperty(result, "windowWidth", (double)screen.GetWidth());
    JSI::SetNumberProperty(result, "windowHeight", (double)screen.GetHeight());
    free(brand);
    free(manufacture);
    free(model);
    NativeapiCommon::SuccessCallBack(thisVal, args, result);
    JSI::ReleaseValueList(args, thisVal, result, ARGS_END);
    delete params;
    params = nullptr;
}
}

void InitDeviceModule(JSIValue exports)
{
    JSI::SetModuleAPI(exports, "getInfo", NativeapiDeviceInfo::GetDeviceInfo);
}

JSIValue NativeapiDeviceInfo::GetDeviceInfo(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum)
{
    return ExecuteAsyncWork(thisVal, args, argsNum, ExecuteGetInfo);
}
} // ACELite
} // OHOS

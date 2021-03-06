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

#include "common/input_device_manager.h"
#include "common/task_manager.h"
#include "graphic_log.h"

namespace OHOS {
void InputDeviceManager::Init()
{
    if (INDEV_READ_PERIOD > 0) {
        SetPeriod(INDEV_READ_PERIOD);
        JobManager::GetInstance()->Add(this);
    }
}

void InputDeviceManager::Add(InputDevice* device)
{
    if (device == nullptr) {
        GRAPHIC_LOGE("InputDeviceManager::Add invalid param\n");
        return;
    }
    deviceList_.PushBack(device);
}

void InputDeviceManager::Remove(InputDevice* device)
{
    if (device == nullptr) {
        return;
    }
    ListNode<InputDevice*>* node = deviceList_.Begin();
    while (node != deviceList_.End()) {
        if (node->data_ == device) {
            deviceList_.Remove(node);
            return;
        }
        node = node->next_;
    }
}

void InputDeviceManager::Callback()
{
    ListNode<InputDevice*>* node = deviceList_.Begin();
    while (node != deviceList_.End()) {
        node->data_->ProcessEvent();
        node = node->next_;
    }
}

void InputDeviceManager::Clear()
{
    deviceList_.Clear();
}
}  // namespace OHOS

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

#ifndef GRAPHIC_LITE_INPUT_DEVICE_MANAGER_H
#define GRAPHIC_LITE_INPUT_DEVICE_MANAGER_H

#include "dock/input_device.h"
#include "list.h"
#include "common/task.h"

namespace OHOS {
/**
 * @brief Manage all input devices.
 */
class InputDeviceManager : public Job {
public:
    /**
     * @brief Get instance of InputDeviceManager.
     * @returns Instance of InputDeviceManager
     */
    static InputDeviceManager* GetInstance()
    {
        static InputDeviceManager instance;
        return &instance;
    }

    void Init() override;

    /**
     * @brief Add an input device.
     *
     * @param [in] device Specific input device
     */
    void Add(InputDevice* device);

    /**
     * @brief Remove an input device.
     *
     * @param [in] Device Specific device to remove
     */
    void Remove(InputDevice* device);

    /**
     * Clear all display devices.
     */
    void Clear();

    void Callback() override;

private:
    InputDeviceManager() {}
    ~InputDeviceManager() {}

    InputDeviceManager(const InputDeviceManager&) = delete;
    InputDeviceManager& operator=(const InputDeviceManager&) = delete;
    InputDeviceManager(InputDeviceManager&&) = delete;
    InputDeviceManager& operator=(InputDeviceManager&&) = delete;

    List<InputDevice*> deviceList_;
};
} // namespace OHOS
#endif // GRAPHIC_LITE_INPUT_DEVICE_MANAGER_H

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

#include "common/graphic_startup.h"
#include "animator/animator.h"
#include "common/input_device_manager.h"
#include "core/render_manager.h"
#include "common/task_manager.h"
#include "file.h"
#include "font/ui_font.h"
#include "graphic_log.h"
#include "imgdecode/cache_manager.h"
#ifdef VERSION_STANDARD
#include "dock/ohos/ohos_input_device.h"
#endif
#if ENABLE_WINDOW
#include "client/iwindows_manager.h"
#if ENABLE_HARDWARE_ACCELERATION
#if 0 // Commented by checkywho@gmail.com
#include "gfx_engines.h"
#endif
#endif
#endif

namespace OHOS {
void GraphicStartUp::InitFontEngine(uintptr_t psramAddr, uint32_t psramLen, const char* dPath, const char* ttfName)
{
    UIFont* pFont = UIFont::GetInstance();
    if (pFont == nullptr) {
        GRAPHIC_LOGE("Get UIFont error");
        return;
    }
    int8_t ret = pFont->SetPsramMemory(psramAddr, psramLen);
    if (ret == INVALID_RET_VALUE) {
        GRAPHIC_LOGE("SetPsramMemory failed");
        return;
    }
    // font and glyph path
    ret = pFont->SetFontPath(const_cast<char*>(dPath));
    if (ret == INVALID_RET_VALUE) {
        GRAPHIC_LOGW("SetFontPath failed");
    }
    if (ttfName != nullptr) {
        ret = pFont->RegisterFontInfo(ttfName);
        if (ret == INVALID_RET_VALUE) {
            GRAPHIC_LOGW("SetTtfName failed");
        }
    }
}

void GraphicStartUp::Init()
{
    JobManager::GetInstance()->SetJobRun(true);
    FileInit();

    if (INDEV_READ_PERIOD > 0) {
        InputDeviceManager::GetInstance()->Init();
    }
    AnimatorManager::GetInstance()->Init();

    StyleDefault::Init();
    RenderManager::GetInstance().Init();

    CacheManager::GetInstance().Init(IMG_CACHE_SIZE);

#ifdef VERSION_STANDARD
    OHOSInputDevice* input = new OHOSInputDevice();
    InputDeviceManager::GetInstance()->Add(input);
#endif

#if ENABLE_WINDOW
    IWindowsManager::GetInstance()->Init();
#if 0 // Commented by checkywho@gmail.com
#if ENABLE_HARDWARE_ACCELERATION
    GfxEngines::GetInstance()->InitDriver();
#endif
#endif
#endif
}
} // namespace OHOS

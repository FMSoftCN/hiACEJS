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

#include "ability_event_handler.h"
#include "hybridos_proxy_windows_manager.h"

namespace OHOS {
namespace {
    thread_local AbilityEventHandler* g_currentHandler;
}

AbilityEventHandler::AbilityEventHandler()
{
    g_currentHandler = this;
    (void) pthread_mutex_init(&queueMutex_, nullptr);
    (void) pthread_cond_init(&pthreadCond_, nullptr);
}

AbilityEventHandler::~AbilityEventHandler()
{
    (void) pthread_mutex_destroy(&queueMutex_);
    (void) pthread_cond_destroy(&pthreadCond_);

    g_currentHandler = nullptr;
}

void AbilityEventHandler::Run()
{
    while (!quit_) {
        (void) pthread_mutex_lock(&queueMutex_);
        if (taskQueue_.empty()) {
            (void) pthread_cond_wait(&pthreadCond_, &queueMutex_);
        }
        Task task = std::move(taskQueue_.front());
        taskQueue_.pop();
        (void) pthread_mutex_unlock(&queueMutex_);
        task();
    }
}

void AbilityEventHandler::ProcessEvent()
{
    do {
        (void) pthread_mutex_lock(&queueMutex_);
        if (taskQueue_.empty()) {
             (void) pthread_mutex_unlock(&queueMutex_);
            break;
        }
        Task task = std::move(taskQueue_.front());
        taskQueue_.pop();
        (void) pthread_mutex_unlock(&queueMutex_);
        task();
    } while(1);
}

void AbilityEventHandler::PostTask(const Task& task)
{
    (void) pthread_mutex_lock(&queueMutex_);
    taskQueue_.push(task);
    (void) pthread_mutex_unlock(&queueMutex_);

    (void) pthread_cond_signal(&pthreadCond_);

    ((OHOS::HybridosProxyWindowsManager*)OHOS::IWindowsManager::GetInstance())->ProcessAbilityEvent();
}

void AbilityEventHandler::PostQuit()
{
    Task task = [this]() {
        quit_ = true;
    };
    PostTask(task);
}

AbilityEventHandler* AbilityEventHandler::GetCurrentHandler()
{
    return g_currentHandler;
}
}  // namespace OHOS

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

/**
 * @addtogroup AbilityKit
 * @{
 *
 * @brief Provides ability-related functions, including ability lifecycle callbacks and functions for connecting to or
 *        disconnecting from Particle Abilities.
 *
 * Abilities are classified into Feature Abilities and Particle Abilities. Feature Abilities support the Page template,
 * and Particle Abilities support the Service template. An ability using the Page template is called a Page ability for
 * short and that using the Service template is called a Service ability.
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file ability_event_handler.h
 *
 * @brief Declares functions for performing operations during inter-thread communication, including running and
 *        quitting the event loop of the current thread and posting tasks to an asynchronous thread.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef OHOS_ABILITY_EVENT_HANDLER_H
#define OHOS_ABILITY_EVENT_HANDLER_H

#include <functional>
#include <pthread.h>
#include <queue>

namespace OHOS {
/**
 * @brief Declares functions for performing operations during inter-thread communication, including running and
 *        quitting the event loop of the current thread and posting tasks to an asynchronous thread.
 *
 * @since 1.0
 * @version 1.0
 */
class AbilityEventHandler {
public:
    using Task = std::function<void()>;

    AbilityEventHandler();
    ~AbilityEventHandler();

    /**
     * @brief Starts running the event loop of the current thread.
     */
    void Run();

    void ProcessEvent();

    /**
     * @brief Posts a task to an asynchronous thread.
     *
     * @param task Indicates the task to post.
     */
    void PostTask(const Task &task);

    /**
     * @brief Quits the event loop of the current thread.
     */
    void PostQuit();

    /**
     * @brief Obtains the event handler of the current thread.
     *
     * @return Returns the pointer to the {@link AbilityEventHandler} object of the current thread.
     */
    static AbilityEventHandler* GetCurrentHandler();
private:
    std::queue<Task> taskQueue_;

    pthread_cond_t pthreadCond_ = PTHREAD_COND_INITIALIZER;
    pthread_mutex_t queueMutex_ = PTHREAD_MUTEX_INITIALIZER;

    bool quit_ { false };

    AbilityEventHandler(const AbilityEventHandler&) = delete;
    AbilityEventHandler& operator = (const AbilityEventHandler&) = delete;
    AbilityEventHandler(AbilityEventHandler&&) = delete;
    AbilityEventHandler& operator= (AbilityEventHandler&&) = delete;
};
}  // namespace OHOS
#endif  // OHOS_ABILITY_EVENT_HANDLER_H

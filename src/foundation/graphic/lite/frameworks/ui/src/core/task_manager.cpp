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

#include "common/task_manager.h"
#include <cassert>
#include "hal_tick.h"

namespace OHOS {
void JobManager::Add(Job* job)
{
    if (job == nullptr) {
        return;
    }

    list_.PushBack(job);
}

void JobManager::Remove(Job* job)
{
    if (job == nullptr) {
        return;
    }
    ListNode<Job*>* pos = list_.Begin();
    while (pos != list_.End()) {
        if (pos->data_ == job) {
            list_.Remove(pos);
            return;
        }
        pos = pos->next_;
    }
}

void JobManager::JobHandler()
{
    if (canJobRun_ == false) {
        return;
    }

    if (isHandlerRunning_) {
        return;
    }
    isHandlerRunning_ = true;

    ListNode<Job*>* node = list_.Begin();

    while (node != list_.End()) {
        Job* currentJob = node->data_;
        currentJob->JobExecute();

        node = node->next_;
    }

    isHandlerRunning_ = false;
}
}

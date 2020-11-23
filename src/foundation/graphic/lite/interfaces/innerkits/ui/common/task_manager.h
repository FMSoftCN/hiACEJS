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

#ifndef GRAPHIC_LITE_TASK_MANAGER_H
#define GRAPHIC_LITE_TASK_MANAGER_H

#include <cstdint>

#include "list.h"
#include "common/task.h"

namespace OHOS {
class JobManager : public HeapBase {
public:
    /**
     * @brief return JobManager's singleton
     * @return JobManager*
     */
    static JobManager* GetInstance()
    {
        static JobManager jobManager;
        return &jobManager;
    }

    /**
     * @brief add job to job manager
     * @param [in] job job pointer
     */
    void Add(Job* job);

    /**
     * @brief del job from job manager
     * @param [in] job job pointer
     */
    void Remove(Job* job);

    /**
     * @brief set job run
     * @param [in] enable job run
     */
    void SetJobRun(bool enable)
    {
        canJobRun_ = enable;
    }

    /**
     * @brief get job run
     * @return enable job run
     */
    bool GetJobRun() const
    {
        return canJobRun_;
    }

    /**
     * @brief run all job
     */
    void JobHandler();

    /**
     * @brief reset the mutex of job handler, must be used carefully
     */
    void ResetJobHandlerMutex();

protected:
    List<Job*> list_; /* the job list */
    bool canJobRun_;
    bool isHandlerRunning_;
    uint8_t idleLast_;

private:
    JobManager() : canJobRun_(false), isHandlerRunning_(false), idleLast_(0) {}
    ~JobManager() {}

    static const uint16_t IDLE_MEAS_PERIOD = 500;
};
} // namespace OHOS
#endif // GRAPHIC_LITE_TASK_MANAGER_H

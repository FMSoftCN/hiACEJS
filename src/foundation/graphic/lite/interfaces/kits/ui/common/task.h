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
 * @addtogroup Graphic
 * @{
 *
 * @brief Defines a lightweight graphics system that provides basic UI and container views,
 *        including buttons, images, labels, lists, animators, scroll views, swipe views, and layouts.
 *        This system also provides the Design for X (DFX) capability to implement features such as
 *        view rendering, animation, and input event distribution.
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file task.h
 *
 * @brief Declares the <b>Job</b> class of the graphics module, which provides functions for setting the running period
 * and time of a task.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef GRAPHIC_LITE_TASK_H
#define GRAPHIC_LITE_TASK_H

#include <cstdint>

#include "heap_base.h"

namespace OHOS {
/**
 * @brief Represents the <b>Job</b> class of the graphics module.
 *        This class provides functions for setting the running period and time of a task.
 *
 * @since 1.0
 * @version 1.0
 */
class Job : public HeapBase {
public:
    /**
     * @brief A constructor used to create a <b>Job</b> instance.
     */
    Job() : period_(DEFAULT_TASK_PERIOD), lastRun_(0) {}

    /**
     * @brief A constructor used to create a <b>Job</b> instance with the specified running period.
     * @param period Indicates the running period of this task.
     */
    Job(uint32_t period) : period_(period), lastRun_(0) {}

    /**
     * @brief A destructor used to delete the <b>Job</b> instance.
     */
    virtual ~Job() {}

    /**
     * @brief Sets the running period for this task.
     * @param period Indicates the running period to set.
     */
    void SetPeriod(uint32_t period)
    {
        period_ = period;
    }

    /**
     * @brief Sets the end time for this task.
     * @param lastRun Indicates the end time to set.
     */
    void SetLastRun(uint32_t lastRun)
    {
        lastRun_ = lastRun;
    }

    /**
     * @brief Obtains the running period of this task.
     * @return Returns the running period.
     */
    uint32_t GetPeriod() const
    {
        return period_;
    }

    /**
     * @brief Obtains the end time of this task.
     * @return Returns the end time.
     */
    uint32_t GetLastRun() const
    {
        return lastRun_;
    }

    /**
     * @brief Executes this task.
     */
    void JobExecute();

    /**
     * @brief Called when this task is executed.
     */
    virtual void Callback() = 0;

    /**
     * @brief Initializes this task.
     */
    virtual void Init();

protected:
    uint32_t period_;  /* call period in ms unit */
    uint32_t lastRun_; /* last run time */
};
} // namespace OHOS
#endif // GRAPHIC_LITE_TASK_H

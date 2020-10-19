/*
 * Copyright (c) 2020 FMSoft.
 */

#include "nativeapi_timer_task.h"

#include <stdio.h>

#include "kal.h"
#include "ohos_errno.h"

int InitTimerTask()
{
    return EC_SUCCESS;
}

int StartTimerTask(bool isPeriodic, const unsigned int delay, void* userCallback,
    void* userContext, timerHandle_t* timerHandle)
{
    if (userCallback == NULL) {
        return EC_FAILURE;
    }
    KalTimerType timerType;
    if (isPeriodic) {
        timerType = KAL_TIMER_PERIODIC;
    } else {
        timerType = KAL_TIMER_ONCE;
    }
    KalTimerId timerId = KalTimerCreate((KalTimerProc)userCallback, timerType, userContext, delay);
    if (timerId == NULL) {
        return EC_FAILURE;
    }
    int ret = KalTimerStart(timerId);
    if (ret != KAL_OK) {
        StopTimerTask(timerId);
        return EC_FAILURE;
    }
    *timerHandle = timerId;
    return EC_SUCCESS;
}

int StopTimerTask(const timerHandle_t timerHandle)
{
    if (timerHandle == NULL) {
        return EC_FAILURE;
    }
    int ret = KalTimerDelete((KalTimerId)timerHandle);
    return ret;
}

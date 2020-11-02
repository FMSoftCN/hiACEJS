/*
 * Copyright (c) 2020 FMSoft.
 */

#ifndef JS_NATIVEAPI_TIMER_TASK_H
#define JS_NATIVEAPI_TIMER_TASK_H

#include <stdbool.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

typedef void *timerHandle_t;

int InitTimerTask();
int StartTimerTask(bool isPeriodic, const unsigned int delay, void* userCallback,
                   void* userContext, timerHandle_t* timerHandle);
int StopTimerTask(const timerHandle_t timerHandle);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif  /* __cplusplus */

#endif /* JS_NATIVEAPI_TIMER_TASK_H */

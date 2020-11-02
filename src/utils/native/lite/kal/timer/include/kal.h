/*
 * Copyright (c) 2020 FMSoft.
 */

#ifndef KAL_H_
#define KAL_H_

#include <signal.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*KalTimerProc)(union sigval);
typedef void *KalTimerId;

typedef enum {
    KAL_TIMER_ONCE = 0,    // /< One-shot timer.
    KAL_TIMER_PERIODIC = 1 // /< Repeating timer.
} KalTimerType;

typedef enum {
    KAL_OK = 0,
    KAL_ERR_PARA = 1,
    KAL_ERR_INNER = 2,
    KAL_ERR_TIMER_STATE = 0x100,
} KalErrCode;

KalTimerId KalTimerCreate(KalTimerProc func, KalTimerType type, void* arg, unsigned int millisec);
KalErrCode KalTimerStart(KalTimerId timerId);
KalErrCode KalTimerChange(KalTimerId timerId, unsigned int millisec);
KalErrCode KalTimerStop(KalTimerId timerId);
KalErrCode KalTimerDelete(KalTimerId timerId);
unsigned int KalTimerIsRunning(KalTimerId timerId);

#ifdef __cplusplus
}
#endif

#endif // KAL_H_

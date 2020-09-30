/*
 * Copyright (c) 2013-2019, Huawei Technologies Co., Ltd. All rights reserved.
 * Copyright (c) 2020, Huawei Device Co., Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 *    conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 *    of conditions and the following disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _LOS_MEMRECORD_PRI_H
#define _LOS_MEMRECORD_PRI_H

#include "los_memory.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#define RECORD_LEN 4000

typedef struct {
    UINT32 addrID;
    UINT32 taskID;
    UINT32 reqSizeID;
    UINT32 allocatedSizeID;
    UINT32 actType;
    UINT64 sysTick;
    UINT32 linkRegID;
} MemRecordInfo;

#define MEM_RECORDSHOW_TIMEOUT 6000

extern VOID OsMemRecordShowSet(UINT32 value);
extern VOID OsMemRecordMalloc(const VOID *ptr, UINT32 size);
extern VOID OsMemRecordFree(const VOID *ptr, UINT32 size);
extern VOID OsMemRecordShowTask(VOID);
extern VOID OsDecTo64F(UINT32 num, CHAR *base64, INT32 base64Len);


#ifndef LOSCFG_MEM_RECORDINFO
INLINE VOID OsMemRecordFree(const VOID *ptr, UINT32 size)
{
    return;
}
#endif

#ifndef LOSCFG_MEM_RECORDINFO
INLINE VOID OsMemRecordMalloc(const VOID *ptr, UINT32 size)
{
    return;
}
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* _LOS_MEMRECORD_PRI_H */

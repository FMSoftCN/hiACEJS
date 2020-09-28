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

#include "shcmd.h"
#include "los_memory.h"
#ifdef LOSCFG_SHELL_EXCINFO
#include "los_excinfo_pri.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

INT32 osShellCmdReadExcInfo(INT32 argc, CHAR **argv)
{
    UINT32 recordSpace = GetRecordSpace();

    (VOID)argc;
    (VOID)argv;

    CHAR *buf = (CHAR*)LOS_MemAlloc((void *)OS_SYS_MEM_ADDR, recordSpace + 1);
    if (buf == NULL) {
        return LOS_NOK;
    }
    (void)memset_s(buf, recordSpace + 1, 0, recordSpace + 1);

    log_read_write_fn hook = GetExcInfoRW();
    if (hook != NULL) {
        hook(GetRecordAddr(), recordSpace, 1, buf);
    }
    PRINTK("%s\n", buf);
    (VOID)LOS_MemFree((void *)OS_SYS_MEM_ADDR, buf);
    buf = NULL;
    return LOS_OK;
}
SHELLCMD_ENTRY(readExcInfo_shellcmd, CMD_TYPE_EX, "excInfo", 0, (CmdCallBackFunc)osShellCmdReadExcInfo);
#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
#endif

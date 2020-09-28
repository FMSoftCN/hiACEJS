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

/*
 * @defgroup los_heap Heap
 * @ingroup kernel
 */

#ifndef _LOS_HEAP_PRI_H
#define _LOS_HEAP_PRI_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#define ALIGNE(sz)                            (((sz) + HEAP_ALIGN - 1) & (~(HEAP_ALIGN - 1)))
#define OS_MEM_ALIGN(value, align)            (((UINT32)(UINTPTR)(value) + (UINT32)((align) - 1)) & \
                                               (~(UINT32)((align) - 1)))
#define OS_MEM_ALIGN_FLAG                     0x80000000
#define OS_MEM_SET_ALIGN_FLAG(align)          ((align) = ((align) | OS_MEM_ALIGN_FLAG))
#define OS_MEM_GET_ALIGN_FLAG(align)          ((align) & OS_MEM_ALIGN_FLAG)
#define OS_MEM_GET_ALIGN_GAPSIZE(align)       ((align) & (~OS_MEM_ALIGN_FLAG))

typedef struct tagLosHeapStatus {
    UINT32 totalUsedSize;
    UINT32 totalFreeSize;
    UINT32 maxFreeNodeSize;
    UINT32 usedNodeNum;
    UINT32 freeNodeNum;
} LosHeapStatus;

struct LosHeapNode {
    struct LosHeapNode* prev;
    UINT32 size : 30;
    UINT32 used : 1;
    UINT32 align : 1;
    UINT8  data[0];
};

struct LosHeapManager {
    struct LosHeapNode *head;
    struct LosHeapNode *tail;
    UINT32 size;
#if (LOSCFG_MEM_MUL_POOL == YES)
    VOID *nextPool;
#endif
};

/**
 * @ingroup los_heap
 * @brief Look up the next memory node according to one memory node in the memory block list.
 *
 * @par Description:
 * This API is used to look up the next memory node according to one memory node in the memory block list.
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 * @param heapMan   [IN]    Type #LosHeapManager *  Pointer to the manager,to distinguish heap.
 * @param node      [IN]    Type #LosHeapNode *   Size of memory in bytes to allocate.
 *
 * @retval   LosHeapNode * Pointer to next memory node.
 *
 * @par Dependency:
 * <ul><li>los_heap_pri.h: the header file that contains the API declaration.</li></ul>
 * @see None.
 */
extern struct LosHeapNode* OsHeapPrvGetNext(struct LosHeapManager *heapMan, struct LosHeapNode* node);

/**
 * @ingroup los_heap
 * @brief Obtain the heap information.
 *
 * @par Description:
 * This API is used to obtain the heap information.
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 * @param pool  [IN]    Type #VOID *  A pointer pointed to the heap memory pool.
 *
 * @retval       None.
 *
 * @par Dependency:
 * <ul><li>los_heap_pri.h: the header file that contains the API declaration.</li></ul>
 * @see None.
 */
extern VOID OsAlarmHeapInfo(VOID *pool);

/**
 * @ingroup los_heap
 * @brief Obtain the heap status.
 *
 * @par Description:
 * This API is used to obtain the heap status.
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 * @param pool      [IN]    Type #VOID *  A pointer pointed to the heap memory pool.
 * @param status    [OUT]   Type #LosHeapStatus *  Heap status.
 *
 * @retval   UINT32  Get status result.
 *
 * @par Dependency:
 * <ul><li>los_heap_pri.h: the header file that contains the API declaration.</li></ul>
 * @see None.
 */
extern UINT32 OsHeapStatisticsGet(VOID *pool, LosHeapStatus *status);

/**
 * @ingroup los_heap
 * @brief Get the max free block size.
 *
 * @par Description:
 * This API is used to Get the max free block size.
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 * @param pool   [IN]    Type #VOID *  A pointer pointed to the heap memory pool.
 *
 * @retval   UINT32  Max free block size.
 *
 * @par Dependency:
 * <ul><li>los_heap_pri.h: the header file that contains the API declaration.</li></ul>
 * @see None.
 */
extern UINT32 OsHeapGetMaxFreeBlkSize(VOID *pool);

/**
 * @ingroup OsHeapInit
 * @brief Initialize the heap memory pool.
 *
 * @par Description:
 * This API is used to initialize the heap memory and get the begin address and
 * size of heap memory,then initialize LosHeapManager .
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 * @param pool   [IN]    Type #VOID *  A pointer pointed to the heap memory pool.
 * @param size   [IN]    Type #UINT32   Size of memory in bytes to initialized.
 *
 * @retval   BOOL  Get status return.
 *
 * @par Dependency:
 * <ul><li>los_heap_pri.h: the header file that contains the API declaration.</li></ul>
 * @see None.
 */
extern BOOL OsHeapInit(VOID *pool, UINT32 size);

/**
 * @ingroup OsHeapAlloc
 * @brief Alloc memory block from the heap.
 *
 * @par Description:
 * This API is used to alloc memory block from the heap memory pool.
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 * @param pool   [IN]    Type #VOID *   Pointer to the manager,to distinguish heap
 * @param size   [IN]    Type #UINT32   Size of memory in bytes to alloc.
 *
 * @retval   VOID * Get the address of the memory we alloced or NULL.
 *
 * @par Dependency:
 * <ul><li>los_heap_pri.h: the header file that contains the API declaration.</li></ul>
 * @see None.
 */
extern VOID* OsHeapAlloc(VOID *pool, UINT32 size);

/**
 * @ingroup OsHeapAllocAlign
 * @brief Alloc memory block from the heap with align.
 *
 * @par Description:
 * This API is used to alloc memory block from the heap memory pool with align.
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 * @param pool   [IN]    Type #VOID *   Pointer to the manager,to distinguish heap
 * @param size   [IN]    Type #UINT32   Size of memory in bytes to alloc.
 * @param boundary   [IN]    Type #UINT32  Boundary the heap needs align.
 *
 * @retval   VOID * Get the address of the memory we alloced or NULL.
 *
 * @par Dependency:
 * <ul><li>los_heap_pri.h: the header file that contains the API declaration.</li></ul>
 * @see None.
 */
extern VOID* OsHeapAllocAlign(VOID *pool, UINT32 size, UINT32 boundary);

/**
 * @ingroup OsHeapFree
 * @brief Free memory block from heap memory pool.
 *
 * @par Description:
 * This API is used to To free the  memory block from  heap memory pool.
 * @attention
 * <ul>
 * <li>None.</li>
 * </ul>
 * @param pool   [IN]    Type #VOID *   Pointer to the manager,to distinguish heap
 * @param ptr    [IN]    Type #VOID *   Pinter of heap memory we want to free.
 *
 * @retval   BOOL  Get result return.
 *
 * @par Dependency:
 * <ul><li>los_heap_pri.h: the header file that contains the API declaration.</li></ul>
 * @see None.
 */
extern BOOL OsHeapFree(VOID *pool, VOID* ptr);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* _LOS_HEAP_PRI_H */

/*
 * Copyright (c) 2020 FMSoft.
 */

#ifndef JS_NATIVE_API_FS_IMPL_H
#define JS_NATIVE_API_FS_IMPL_H

#include <stdbool.h>
#include <stdio.h>
#include <sys/stat.h>

#include "nativeapi_config.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

typedef struct {
    char fileName[FILE_NAME_MAX_LEN + 1];
    off_t fileSize;
    time_t fileMtime;
    mode_t fileMode;
} FileMetaInfo;

int StatImpl(const char* path, struct stat* buf);
int DeleteFileImpl(const char* src);
int CopyFileImpl(const char* src, const char* dest);
int WriteTextFile(const char* fileName, const void* buf, size_t len, bool append);
int WriteArrayFile(const char* fileName, const void* buf, size_t len, unsigned int position, bool append);
int ReadFileImpl(const char* fileName, void* text, size_t len, unsigned int position, size_t* actualLen);
int GetFileListImpl(const char* dirName, FileMetaInfo* fileList, unsigned int listNum);
int GetFileNum(const char* dirName);
int AccessImpl(const char* fileName);
int CreateDirImpl(const char* fileName, bool recursive);
int RemoveDirImpl(const char* fileName, bool recursive);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* JS_NATIVE_API_FS_IMPL_H */

/*
 * Copyright (c) 2020 FMSoft.
 */

#ifndef JS_FS_KV_API_H
#define JS_FS_KV_API_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#define KEY_MAX_LEN 32
#define VALUE_MAX_LEN 128

int InitKv(const char* dataPath);
int GetValue(const char* key, char* value);
int SetValue(const char* key, const char* value);
int DeleteValue(const char* key);
int ClearKVStore(const char* dataPath);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* JS_FS_KV_API_H */

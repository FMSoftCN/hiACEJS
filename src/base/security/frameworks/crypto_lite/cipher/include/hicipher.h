/*
 * Copyright (c) 2020 FMSoft.
 */

#ifndef HICIPHER_H
#define HICIPHER_H

#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#define KEY_LEN              32
#define AES_BLOCK_SIZE       16
#define ERROR_CODE_GENERAL   -1
#define ERROR_SUCCESS         0

typedef enum {
    CIPHER_AES_ECB,
    CIPHER_AES_CBC
} CipherAesMode;

typedef struct {
    char *text;
    char *key;
    int32_t action;
    int32_t textLen;
    int32_t keyLen;
} CryptData;

typedef struct {
    char *transformation;
    char *ivBuf;
    int32_t ivOffset;
    int32_t ivLen;
} AesIvMode;

typedef struct {
    CryptData data;
    CipherAesMode mode;
    AesIvMode iv;
} AesCryptContext;

typedef struct {
    char *data;
    size_t length;
} RsaData;

typedef struct {
    char *trans;
    char *action;
    char *key;
    size_t keyLen;
} RsaKeyData;

int32_t InitAesCryptData(const char *action, const char *text, const char *key,
    const AesIvMode *iv, AesCryptContext *aesCryptCxt);
int32_t AesCrypt(AesCryptContext *aesCryptCxt);
void DeinitAesCryptData(AesCryptContext *aesCryptCxt);
int32_t RsaCrypt(RsaKeyData *key, RsaData *inData, RsaData *outData);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif // HICIPHER_H

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

#include "parameter.h"
#include <securec.h>
#include "hal_sys_param.h"
#include "ohos_errno.h"
#include "param_adaptor.h"

#define FILE_RO "ro."
#define VERSION_ID_LEN 256

static char g_roBuildOs[] = {"OpenHarmony"};
static char g_roBuildVerShow[] = {"OpenHarmony 1.0"};
static char g_roSdkApiLevel[] = {"3"};
static char g_roFirstApiLevel[] = {"1"};


// xsm 20201218 TODO: define into CMakeLists.txt
static char INCREMENTAL_VERSION[] = "";
static char BUILD_TYPE[] = "";
static char BUILD_USER[] = "";
static char BUILD_HOST[] = "";
static char BUILD_TIME[] = "";
static char BUILD_ROOTHASH[] = "";

#if 0
static boolean IsValidValue(const char* value, unsigned int len)
{
    if ((value == NULL) || !strlen(value) || (strlen(value) + 1 > len)) {
        return FALSE;
    }
    return TRUE;
}
#endif

int GetParameter(const char* key, const char* def, char* value, unsigned int len)
{
#if 0 //TODO: xsm
    if ((key == NULL) || (value == NULL)) {
        return EC_INVALID;
    }
    if (!CheckPermission()) {
        return EC_FAILURE;
    }
    int ret = GetSysParam(key, value, len);
    if (ret == EC_INVALID) {
        return EC_INVALID;
    }
    if ((ret < 0) && IsValidValue(def, len)) {
        if (strcpy_s(value, len, def) != 0) {
            return EC_FAILURE;
        }
        ret = strlen(def);
    }
    return ret;
#endif
        return EC_INVALID;
}

int SetParameter(const char* key, const char* value)
{
#if 0 // TODO: xsm
    if ((key == NULL) || (value == NULL)) {
        return EC_INVALID;
    }
    if (!CheckPermission()) {
        return EC_FAILURE;
    }
    if (strncmp(key, FILE_RO, strlen(FILE_RO)) == 0) {
        return EC_INVALID;
    }

    return SetSysParam(key, value);
#endif
    return EC_INVALID;
}

char* GetProductType(void)
{
    return HalGetProductType();
}

char* GetManufacture(void)
{
    return HalGetManufacture();
}

char* GetBrand(void)
{
    return HalGetBrand();
}

char* GetMarketName(void)
{
    return HalGetMarketName();
}

char* GetProductSeries(void)
{
    return HalGetProductSeries();
}

char* GetProductModel(void)
{
    return HalGetProductModel();
}

char* GetSoftwareModel(void)
{
    return HalGetSoftwareModel();
}

char* GetHardwareModel(void)
{
    return HalGetHardwareModel();
}

char* GetHardwareProfile(void)
{
    return HalGetHardwareProfile();
}

char* GetSerial(void)
{
    return HalGetSerial();
}

char* GetBootloaderVersion(void)
{
    return HalGetBootloaderVersion();
}

char* GetSecurityPatchTag(void)
{
    return HalGetSecurityPatchTag();
}

char* GetAbiList(void)
{
    return HalGetAbiList();
}

static char* GetSysProperty(const char* propertyInfo, const size_t propertySize)
{
    char* prop = (char*)malloc(propertySize);
    if (prop == NULL) {
        return NULL;
    }
    if (strcpy_s(prop, propertySize, propertyInfo) != 0) {
        free(prop);
        prop = NULL;
        return NULL;
    }
    return prop;
}

char* GetOsName(void)
{
    return GetSysProperty(g_roBuildOs, strlen(g_roBuildOs) + 1);
}

char* GetDisplayVersion(void)
{
    return GetSysProperty(g_roBuildVerShow, strlen(g_roBuildVerShow) + 1);
}

char* GetSdkApiLevel(void)
{
    return GetSysProperty(g_roSdkApiLevel, strlen(g_roSdkApiLevel) + 1);
}

char* GetFirstApiLevel(void)
{
    return GetSysProperty(g_roFirstApiLevel, strlen(g_roFirstApiLevel) + 1);
}

char* GetIncrementalVersion(void)
{
    return GetSysProperty(INCREMENTAL_VERSION, strlen(INCREMENTAL_VERSION) + 1);
}

char* GetVersionId(void)
{
    char* value = (char*)malloc(VERSION_ID_LEN);
    if (value == NULL) {
        return NULL;
    }
    if (memset_s(value, VERSION_ID_LEN, 0, VERSION_ID_LEN) != 0) {
        goto MALLOC_ERROR;
    }

    char* productType = GetProductType();
    char* manufacture = GetManufacture();
    char* brand = GetBrand();
    char* productSerial = GetProductSeries();
    char* productModel = GetProductModel();
    char* softwareModel = GetSoftwareModel();
    int ret = -1;
    if (productType == NULL || manufacture == NULL || brand == NULL ||
        productSerial == NULL || productModel == NULL || softwareModel == NULL) {
            goto GET_PARA_ERROR;
    }
    ret = sprintf_s(value, VERSION_ID_LEN, "%s/%s/%s/%s/%s/%s/%s/%s/%s/%s",
        productType, manufacture, brand, productSerial, g_roBuildOs, productModel,
        softwareModel, g_roSdkApiLevel, INCREMENTAL_VERSION, BUILD_TYPE);

GET_PARA_ERROR:
    free(productType);
    free(manufacture);
    free(brand);
    free(productSerial);
    free(productModel);
    free(softwareModel);
    if (ret >= 0) {
        return value;
    }
MALLOC_ERROR:
    free(value);
    value = NULL;
    return NULL;
}

char* GetBuildType(void)
{
    return GetSysProperty(BUILD_TYPE, strlen(BUILD_TYPE) + 1);
}

char* GetBuildUser(void)
{
    return GetSysProperty(BUILD_USER, strlen(BUILD_USER) + 1);
}

char* GetBuildHost(void)
{
    return GetSysProperty(BUILD_HOST, strlen(BUILD_HOST) + 1);
}

char* GetBuildTime(void)
{
    return GetSysProperty(BUILD_TIME, strlen(BUILD_TIME) + 1);
}

char* GetBuildRootHash(void)
{
    return GetSysProperty(BUILD_ROOTHASH, strlen(BUILD_ROOTHASH) + 1);
}

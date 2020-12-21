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

#include "hal_sys_param.h"
#include <securec.h>

static const char OHOS_PRODUCT_TYPE[] = {"****"};
static const char OHOS_MANUFACTURE[] = {"****"};
static const char OHOS_BRAND[] = {"****"};
static const char OHOS_MARKET_NAME[] = {"****"};
static const char OHOS_PRODUCT_SERIES[] = {"****"};
static const char OHOS_PRODUCT_MODEL[] = {"****"};
static const char OHOS_SOFTWARE_MODEL[] = {"****"};
static const char OHOS_HARDWARE_MODEL[] = {"****"};
static const char OHOS_HARDWARE_PROFILE[] = {"aout:true,display:true"};
static const char OHOS_BOOTLOADER_VERSION[] = {"bootloader"};
static const char OHOS_SECURITY_PATCH_TAG[] = {"2020-12-18"};
static const char OHOS_ABI_LIST[] = {"****"};
static const char OHOS_SERIAL[] = {"1234567890"};  // provided by OEM.

static char* HalGetSysParam(const char* paramType, size_t paramSize)
{
    char* param = (char*)malloc(paramSize);
    if (param == NULL) {
        return NULL;
    }
    if (strcpy_s(param, paramSize, paramType) != EOK) {
        free(param);
        return NULL;
    }
    return param;
}

char* HalGetProductType(void)
{
    return HalGetSysParam(OHOS_PRODUCT_TYPE, sizeof(OHOS_PRODUCT_TYPE));
}

char* HalGetManufacture(void)
{
    return HalGetSysParam(OHOS_MANUFACTURE, sizeof(OHOS_MANUFACTURE));
}

char* HalGetBrand(void)
{
    return HalGetSysParam(OHOS_BRAND, sizeof(OHOS_BRAND));
}

char* HalGetMarketName(void)
{
    return HalGetSysParam(OHOS_MARKET_NAME, sizeof(OHOS_MARKET_NAME));
}

char* HalGetProductSeries(void)
{
    return HalGetSysParam(OHOS_PRODUCT_SERIES, sizeof(OHOS_PRODUCT_SERIES));
}

char* HalGetProductModel(void)
{
    return HalGetSysParam(OHOS_PRODUCT_MODEL, sizeof(OHOS_PRODUCT_MODEL));
}

char* HalGetSoftwareModel(void)
{
    return HalGetSysParam(OHOS_SOFTWARE_MODEL, sizeof(OHOS_SOFTWARE_MODEL));
}

char* HalGetHardwareModel(void)
{
    return HalGetSysParam(OHOS_HARDWARE_MODEL, sizeof(OHOS_HARDWARE_MODEL));
}

char* HalGetHardwareProfile(void)
{
    return HalGetSysParam(OHOS_HARDWARE_PROFILE, sizeof(OHOS_HARDWARE_PROFILE));
}

char* HalGetSerial(void)
{
    return HalGetSysParam(OHOS_SERIAL, sizeof(OHOS_SERIAL));
}

char* HalGetBootloaderVersion(void)
{
    return HalGetSysParam(OHOS_BOOTLOADER_VERSION, sizeof(OHOS_BOOTLOADER_VERSION));
}

char* HalGetSecurityPatchTag(void)
{
    return HalGetSysParam(OHOS_SECURITY_PATCH_TAG, sizeof(OHOS_SECURITY_PATCH_TAG));
}

char* HalGetAbiList(void)
{
    return HalGetSysParam(OHOS_ABI_LIST, sizeof(OHOS_ABI_LIST));
}

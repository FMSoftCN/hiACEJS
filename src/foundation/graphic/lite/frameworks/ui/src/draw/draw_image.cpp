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

#include "draw/draw_image.h"

#include "color.h"
#include "graphic_log.h"
#include "imgdecode/cache_manager.h"

#include <minigui/gdi.h>

namespace OHOS {

void DrawImage::DrawCommon(const Rect& coordsIn, const Rect& maskIn,
    const ImageInfo* img, const Style& style, uint8_t opaScale)
{
    if (img == nullptr) {
        return;
    }
    OpacityType opa = (opaScale == OPA_OPAQUE) ? style.imageOpa_ :
        ((static_cast<uint16_t>(style.imageOpa_) * opaScale) >> SHIFT_8);

    Rect coords = coordsIn;
    Rect mask = maskIn;

#if defined(ENABLE_FULL_ADAPTIVE_LAYOUT)
    coords = OHOS::ScreenDeviceProxy::GetInstance()->calcRect(coordsIn);
    mask = OHOS::ScreenDeviceProxy::GetInstance()->calcRect(maskIn);

    BITMAP srcBitmap;
    srcBitmap.bmType = BMP_TYPE_NORMAL;
    srcBitmap.bmBitsPerPixel = 32;
    srcBitmap.bmBytesPerPixel = 4;
    srcBitmap.bmAlpha = 0;
    srcBitmap.bmColorKey = 0;
    srcBitmap.bmWidth = img->header.width;
    srcBitmap.bmHeight = img->header.height;
    srcBitmap.bmBits = (Uint8*)img->data;
    srcBitmap.bmPitch = srcBitmap.bmWidth * srcBitmap.bmBytesPerPixel;

    ImageInfo imgInfoScale = *img;
    imgInfoScale.header.width = OHOS::ScreenDeviceProxy::GetInstance()->calcScale(imgInfoScale.header.width);
    imgInfoScale.header.height =  OHOS::ScreenDeviceProxy::GetInstance()->calcScale(imgInfoScale.header.height);
    imgInfoScale.dataSize = imgInfoScale.header.height * imgInfoScale.header.width * 4;
    imgInfoScale.data = static_cast<uint8_t*>(UIMalloc(imgInfoScale.dataSize));
    memset((void*)imgInfoScale.data, 0, imgInfoScale.dataSize);

    BITMAP dstBitmap;
    dstBitmap.bmType = BMP_TYPE_NORMAL;
    dstBitmap.bmBitsPerPixel = 32;
    dstBitmap.bmBytesPerPixel = 4;
    dstBitmap.bmAlpha = 0;
    dstBitmap.bmColorKey = 0;
    dstBitmap.bmWidth = imgInfoScale.header.width;
    dstBitmap.bmHeight = imgInfoScale.header.height;
    dstBitmap.bmPitch = dstBitmap.bmWidth * dstBitmap.bmBytesPerPixel;
    dstBitmap.bmBits = (Uint8*)imgInfoScale.data;

    ScaleBitmap(&dstBitmap, &srcBitmap);

    /* 3 : when single pixel change bit to byte, the buffer should divide by 8, equal to shift right 3 bits. */
    uint8_t pxByteSize = DrawUtils::GetPxSizeByImageInfo(imgInfoScale) >> 3;
    DrawUtils::GetInstance()->DrawImage(coords, mask, imgInfoScale.data, opa, pxByteSize);

    UIFree((void*)imgInfoScale.data);
#else
    /* 3 : when single pixel change bit to byte, the buffer should divide by 8, equal to shift right 3 bits. */
    uint8_t pxByteSize = DrawUtils::GetPxSizeByImageInfo(*img) >> 3;
    DrawUtils::GetInstance()->DrawImage(coords, mask, img->data, opa, pxByteSize);
#endif

}

void DrawImage::DrawCommon(const Rect& coordsIn, const Rect& maskIn,
    const char* path, const Style& style, uint8_t opaScale)
{
    if (path == nullptr) {
        return;
    }
    OpacityType opa = (opaScale == OPA_OPAQUE) ? style.imageOpa_ :
        ((static_cast<uint16_t>(style.imageOpa_) * opaScale) >> SHIFT_8);

    CacheEntry entry;
    if (CacheManager::GetInstance().Open(path, style, entry) != RetCode::OK) {
        return;
    }

    Rect coords = coordsIn;
    Rect mask = maskIn;

#if defined(ENABLE_FULL_ADAPTIVE_LAYOUT)
    coords = OHOS::ScreenDeviceProxy::GetInstance()->calcRect(coordsIn);
    mask = OHOS::ScreenDeviceProxy::GetInstance()->calcRect(maskIn);
#endif

    /* 3 : when single pixel change bit to byte, the buffer should divide by 8, equal to shift right 3 bits. */
    uint8_t pxByteSize = DrawUtils::GetPxSizeByImageInfo(entry.GetImageInfo()) >> 3;
    if (entry.InCache()) {
        DrawUtils::GetInstance()->DrawImage(coords, mask, entry.GetImgData(), opa, pxByteSize);
    } else {
        Rect valid = coords;
        if (!valid.Intersect(valid, mask)) {
            return;
        }

        int16_t width = valid.GetWidth();
        if (width <= 0) {
            return;
        }
        uint8_t* buf = static_cast<uint8_t*>(UIMalloc(static_cast<uint32_t>(width) * ((COLOR_DEPTH >> SHIFT_3) + 1)));
        if (buf == nullptr) {
            return;
        }

        Rect line = valid;
        line.SetHeight(1);
        Point start;
        start.x = valid.GetLeft() - coords.GetLeft();
        start.y = valid.GetTop() - coords.GetTop();
        int16_t row;
        for (row = valid.GetTop(); row <= valid.GetBottom(); row++) {
            if (entry.ReadLine(start, width, buf) != RetCode::OK) {
                CacheManager::GetInstance().Close(path);
                UIFree(buf);
                return;
            }
            DrawUtils::GetInstance()->DrawImage(line, mask, buf, opa, pxByteSize);
            line.SetTop(line.GetTop() + 1);
            line.SetBottom(line.GetBottom() + 1);
            start.y++;
        }
        UIFree(buf);
    }
}
} // namespace OHOS

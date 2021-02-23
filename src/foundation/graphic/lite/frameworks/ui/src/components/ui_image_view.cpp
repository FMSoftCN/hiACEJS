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

#include "components/ui_image_view.h"
#include "common/image.h"
#include "common/typed_text.h"
#include "draw/draw_image.h"
#include "draw/draw_label.h"
#include "draw/draw_rect.h"
#include "image_info.h"
#include "imgdecode/cache_manager.h"
#include "mem_api.h"
#include <minigui/gdi.h>

namespace OHOS {
UIImageView::UIImageView()
    : imageWidth_(0), imageHeight_(0),
      autoEnable_(true), needRefresh_(false), colorFormat_(UNKNOW),
      blurLevel_(BlurLevel::LEVEL0), algorithm_(TransformAlgorithm::BILINEAR), reserve_(0)
{
    style_ = &(StyleDefault::GetBackgroundTransparentStyle());
}

UIImageView::~UIImageView()
{
    DeleteMeasureView();
}

bool UIImageView::OnPreDraw(const Rect& invalidatedArea)
{
    bool cover = false;
    if ((image_.GetSrcType() == IMG_SRC_UNKNOWN)) {
        return false;
    }

    if ((colorFormat_ == RGB565 || colorFormat_ == RGB888)) {
        cover = GetRect().IsContains(invalidatedArea);
    }

    return cover;
}

void UIImageView::OnDraw(const Rect& invalidatedArea)
{
#if defined(ENABLE_FULL_ADAPTIVE_LAYOUT)
    Rect area = OHOS::ScreenDeviceProxy::GetInstance()->calcRect(invalidatedArea);
    Rect rect = OHOS::ScreenDeviceProxy::GetInstance()->calcRect(GetRect());
    DrawRect::Draw(rect, area, *style_);
#else
    DrawRect::Draw(GetRect(), invalidatedArea, *style_);
#endif
    if ((imageHeight_ == 0) || (imageWidth_ == 0)) {
        return;
    }

    Rect viewRect = GetContentRect();
    Rect trunc(invalidatedArea);
    if (trunc.Intersect(trunc, viewRect)) {
        uint8_t srcType = image_.GetSrcType();
        if ((srcType == IMG_SRC_FILE) || (srcType == IMG_SRC_VARIABLE)) {
            Rect cordsTmp;
            cordsTmp.SetTop(viewRect.GetY());
            cordsTmp.SetBottom(viewRect.GetY() + imageHeight_ - 1);

            if ((transMap_ == nullptr) || transMap_->IsInvalid()) {
                while (cordsTmp.GetTop() <= viewRect.GetBottom()) {
                    cordsTmp.SetLeft(viewRect.GetX());
                    cordsTmp.SetRight(viewRect.GetX() + imageWidth_ - 1);
                    while (cordsTmp.GetLeft() <= viewRect.GetRight()) {
                        image_.DrawImage(cordsTmp, trunc, *style_, opaScale_);
                        cordsTmp.SetLeft(cordsTmp.GetLeft() + imageWidth_);
                        cordsTmp.SetRight(cordsTmp.GetRight() + imageWidth_);
                    }
                    cordsTmp.SetTop(cordsTmp.GetTop() + imageHeight_);
                    cordsTmp.SetBottom(cordsTmp.GetBottom() + imageHeight_);
                }
            } else if ((transMap_ != nullptr) && !transMap_->IsInvalid()) {
                ImageInfo imgInfo;
                if (srcType == IMG_SRC_FILE) {
                    CacheEntry entry;
                    RetCode ret = CacheManager::GetInstance().Open(GetPath(), *style_, entry);
                    if (ret != RetCode::OK) {
                        return;
                    }
                    imgInfo = entry.GetImageInfo();
                } else {
                    imgInfo = *(GetImageInfo());
                }

#if defined(ENABLE_FULL_ADAPTIVE_LAYOUT)
                BITMAP srcBitmap;
                srcBitmap.bmType = BMP_TYPE_NORMAL;
                srcBitmap.bmBitsPerPixel = 32;
                srcBitmap.bmBytesPerPixel = 4;
                srcBitmap.bmAlpha = 0;
                srcBitmap.bmColorKey = 0;
                srcBitmap.bmWidth = imgInfo.header.width;
                srcBitmap.bmHeight = imgInfo.header.height;
                srcBitmap.bmBits = (Uint8*)imgInfo.data;
                srcBitmap.bmPitch = srcBitmap.bmWidth * srcBitmap.bmBytesPerPixel;

                ImageInfo imgInfoScale = imgInfo;
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

                uint8_t pxSize = DrawUtils::GetPxSizeByColorMode(imgInfoScale.header.colorMode);
                TransformDataInfo imageTranDataInfo = {
                    imgInfoScale.header, imgInfoScale.data, pxSize,
                    static_cast<BlurLevel>(blurLevel_), static_cast<TransformAlgorithm>(algorithm_)
                };

                Rect origRect = OHOS::ScreenDeviceProxy::GetInstance()->calcRect(GetOrigRect());
                Rect tsMapRect = transMapScale_.GetTransMapRect();
                int16_t deltaX = origRect.GetX() - tsMapRect.GetX();
                int16_t deltaY = origRect.GetY() - tsMapRect.GetY();

                DrawUtils::GetInstance()->DrawTransform(area, Point{ deltaX, deltaY }, Color::Black(),
                        transMapScale_, imageTranDataInfo);

                UIFree((void*)imgInfoScale.data);
#else
                uint8_t pxSize = DrawUtils::GetPxSizeByColorMode(imgInfo.header.colorMode);
                TransformDataInfo imageTranDataInfo = {
                    imgInfo.header, imgInfo.data, pxSize,
                    static_cast<BlurLevel>(blurLevel_), static_cast<TransformAlgorithm>(algorithm_)
                };

                Rect origRect = GetOrigRect();
                int16_t deltaX = origRect.GetX() - transMap_->GetTransMapRect().GetX();
                int16_t deltaY = origRect.GetY() - transMap_->GetTransMapRect().GetY();
                DrawUtils::GetInstance()->DrawTransform(invalidatedArea, Point{ deltaX, deltaY }, Color::Black(),
                    *transMap_, imageTranDataInfo);
#endif
            }
        }
    }
}

void UIImageView::SetSrc(const char* src)
{
    bool updated = image_.SetSrc(src);
    if (updated == false) {
        return;
    }
    needRefresh_ = true;
    if (autoEnable_) {
        ReMeasure();
    } else {
        AddMeasureView();
    }
    Invalidate();
}

void UIImageView::ReMeasure()
{
    if (!needRefresh_) {
        return;
    }
    needRefresh_ = false;

    ImageHeader header = {0};
    image_.GetHeader(header);

    imageWidth_ = header.width;
    imageHeight_ = header.height;
    colorFormat_ = header.colorMode;

    if (autoEnable_) {
        Resize(imageWidth_, imageHeight_);
        Invalidate();
    }
}

void UIImageView::SetSrc(const ImageInfo* src)
{
    bool updated = image_.SetSrc(src);
    if (updated == false) {
        return;
    }
    needRefresh_ = true;
    if (autoEnable_) {
        ReMeasure();
    } else {
        AddMeasureView();
    }
    Invalidate();
}
}

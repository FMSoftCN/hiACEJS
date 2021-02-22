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

#include "draw/draw_curve.h"
#include "animator/interpolation.h"
#include "draw/draw_line.h"
#include <common/screen_device_proxy.h>

namespace OHOS {
void DrawCurve::DrawCubicBezier(const Point& startIn, const Point& control1In, const Point& control2In, const Point& endIn,
    const Rect& maskIn, int16_t widthIn, const ColorType& color, OpacityType opacity)
{
    if (widthIn == 0 || opacity == OPA_TRANSPARENT) {
        return;
    }

    Point start = startIn;
    Point control1 = control1In;
    Point control2 = control2In;
    Point end = endIn;
    Rect mask = maskIn;
    int16_t width = widthIn;

#if defined(ENABLE_FULL_ADAPTIVE_LAYOUT)
    start = OHOS::ScreenDeviceProxy::GetInstance()->calcPoint(startIn);
    control1 = OHOS::ScreenDeviceProxy::GetInstance()->calcPoint(control1In);
    control2 = OHOS::ScreenDeviceProxy::GetInstance()->calcPoint(control2In);
    end = OHOS::ScreenDeviceProxy::GetInstance()->calcPoint(endIn);
    mask = OHOS::ScreenDeviceProxy::GetInstance()->calcRect(maskIn);
    width = OHOS::ScreenDeviceProxy::GetInstance()->calcScale(widthIn);
#endif

    Point prePoint = start;
    for (int16_t t = 1; t <= INTERPOLATION_RANGE; t++) {
        Point point;
        point.x = Interpolation::GetBezierInterpolation(t, start.x, control1.x, control2.x, end.x);
        point.y = Interpolation::GetBezierInterpolation(t, start.y, control1.y, control2.y, end.y);
        if (prePoint.x == point.x && prePoint.y == point.y) {
            continue;
        }

        DrawLine::Draw(prePoint, point, mask, width, color, opacity);
        prePoint = point;
    }
}
}

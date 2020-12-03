#ifndef HYBRIDOS_SURFACE_H
#define HYBRIDOS_SURFACE_H

#include "client/isurface.h"
#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>

namespace OHOS {
class HybridosSurface : public ISurface {
public:
    HybridosSurface(HDC hdc, RECT* rect);
    virtual ~HybridosSurface();

    virtual void Lock(void** buf, void** phyMem, uint32_t* strideLen) override;
    virtual void Unlock() override;

private:
    HDC m_hdc;
    RECT* m_rect;
};
}
#endif

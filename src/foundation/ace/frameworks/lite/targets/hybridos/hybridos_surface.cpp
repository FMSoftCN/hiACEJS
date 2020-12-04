#include "hybridos_surface.h"
#include "graphic_log.h"

namespace OHOS {
HybridosSurface::HybridosSurface(HDC hdc, RECT* rect)
    : m_hdc(hdc), m_rect(rect)
{
}

HybridosSurface::~HybridosSurface()
{
}

void HybridosSurface::Lock(void** buf, void** phyMem, uint32_t* strideLen)
{
    int width = 0;
    int height = 0;
    int pitch = 0;
    *buf = LockDC (m_hdc, m_rect, &width, &height, &pitch);
    *strideLen = pitch;
}

void HybridosSurface::Unlock()
{
    UnlockDC(m_hdc);
}

}

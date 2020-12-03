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
}

void HybridosSurface::Unlock()
{
}

}

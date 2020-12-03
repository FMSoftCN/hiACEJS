#include "hybridos_surface.h"
#include "graphic_log.h"

namespace OHOS {
HybridosSurface::HybridosSurface(HDC hdc)
    : m_hdc(hdc)
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

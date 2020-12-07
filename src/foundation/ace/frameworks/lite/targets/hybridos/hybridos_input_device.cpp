#include "hybridos_input_device.h"
#include "input_event_info.h"
#include "client/iwindows_manager.h"

namespace OHOS {
HybridosInputDevice* HybridosInputDevice::GetInstance()
{
    static HybridosInputDevice inputDevice;
    return &inputDevice;
}


void HybridosInputDevice::Dispatch(const DeviceData& data)
{
    DispatchEvent(data);
}

bool HybridosInputDevice::Read(DeviceData& data)
{
    return false;
}
}

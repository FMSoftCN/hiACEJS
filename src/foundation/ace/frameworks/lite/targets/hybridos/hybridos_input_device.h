
#ifndef HYBRIDOS_INPUT_DEVICE_H
#define HYBRIDOS_INPUT_DEVICE_H

#include "dock/pointer_input_device.h"

namespace OHOS {
class HybridosInputDevice : public PointerInputDevice {
public:
    HybridosInputDevice() {}

    virtual ~HybridosInputDevice() {}

    static HybridosInputDevice* GetInstance();

    void Dispatch(const DeviceData& data);

    bool Read(DeviceData& data) override;
};
}
#endif

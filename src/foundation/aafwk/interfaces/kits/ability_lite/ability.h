///////////////////////////////////////////////////////////////////////////////
//
//                          IMPORTANT NOTICE
//
// The following open source license statement does not apply to any
// entity in the Exception List published by FMSoft.
//
// For more information, please visit:
//
// https://www.fmsoft.cn/exception-list
//
//////////////////////////////////////////////////////////////////////////////
/**
 \verbatim

    This file is part of HybridOS, a developing operating system based on
    MiniGUI. HybridOs will support embedded systems and smart IoT devices.

    Copyright (C) 2020 Beijing FMSoft Technologies Co., Ltd.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    Or,

    As this program is a library, any link to this program must follow
    GNU General Public License version 3 (GPLv3). If you cannot accept
    GPLv3, you need to be licensed from FMSoft.

    If you have got a commercial license of this program, please use it
    under the terms and conditions of the commercial license.

    For more information about the commercial license, please refer to
    <http://www.minigui.com/blog/minigui-licensing-policy/>.

 \endverbatim
 */

#ifndef OHOS_ABILITY_H
#define OHOS_ABILITY_H

#include <string>

#include "components/root_view.h"

typedef struct {
    /**
     * Pointer to the carried data
     */
    void *data;

    /**
     * Data length
     */
    uint16_t dataLength;
} Want;

namespace OHOS {

class AbilityWindow;

class Ability {
public:
    Ability() = default;
    virtual ~Ability() = default;

    /**
     * @brief Called when this ability is started. You must override this function if you want to perform some
     *        initialization operations during ability startup.
     *
     * This function can be called only once in the entire lifecycle of an ability.
     * @param want Indicates the {@link Want} structure containing startup information about the ability.
     */
    virtual void OnStart(const Want &want);

    /**
     * @brief Called when this ability enters the <b>STATE_INACTIVE</b> state.
     *
     * <b>STATE_INACTIVE</b> is an instantaneous state. The ability in this state may be visible but does not have
     * focus. You can override this function to implement your own processing logic.
     */
    virtual void OnInactive();

    /**
     * @brief Called when this ability enters the <b>STATE_ACTIVE</b> state.
     *
     * The ability in the <b>STATE_ACTIVE</b> state is visible and has focus.
     * You can override this function to implement your own processing logic.
     *
     * @param want Indicates the {@link Want} structure containing activation information about the ability.
     */
    virtual void OnActive(const Want &want);

    /**
     * @brief Called when this ability enters the <b>STATE_BACKGROUND</b> state.
     *
     *
     * The ability in the <b>STATE_BACKGROUND</b> state is invisible.
     * You can override this function to implement your own processing logic.
     */
    virtual void OnBackground();

    /**
     * @brief Called when this ability enters the <b>STATE_STOP</b> state.
     *
     * The ability in the <b>STATE_STOP</b> is being destroyed.
     * You can override this function to implement your own processing logic.
     */
    virtual void OnStop();

    /**
     * @brief Called when all abilities connected to this Service ability are disconnected.
     *
     * You can override this function to implement your own processing logic.
     *
     * @param want Indicates the {@link Want} structure containing disconnection information about the Service
     *             ability.
     */
    virtual void OnDisconnect(const Want &want);

    /**
     * @brief Sets the main route for this ability.
     *
     * The main route, also called main entry, refers to the default <b>AbilitySlice</b> to present for this ability.
     * This function should be called only on Feature Abilities. If this function is not called in the
     * {@link OnStart(const Want &want)} function for a Feature Ability, the Feature Ability will fail to start.
     *
     * @param entry Indicates the main entry, which is the class name of the <b>AbilitySlice</b> instance to start.
     */
    void SetMainRoute(const std::string &entry);

    /**
     * @brief Sets the UI layout for this ability.
     * You can call {@link GetWindowRootView()} to create a layout and add controls.
     *
     * @param rootView Indicates the pointer to the custom layout view you have created.
     */
    void SetUIContent(RootView *rootView);

    /**
     * @brief Prints ability information to the console.
     *
     * You can override this function to obtain or print extra parameters.
     *
     * @param extra Indicates the extra parameter to be obtained or printed to the console.
     */
    virtual void Dump(const std::string &extra);

    int TerminateAbility();


    void Init(uint64_t token, int abilityType, bool isNativeApp);
    int GetState() const { return abilityState_; }
private:
    typedef enum {
        START,
        INACTIVE,
        ACTIVE,
        BACKGROUND,
        STOP,
    } Action;

    void DispatchAbilityLifecycle(Action action, const Want *want = nullptr);

    AbilityWindow *abilityWindow_ { nullptr };

    int abilityState_ { 0 };
    int abilityType_ { 0 };
    uint64_t token_ { 0 };
};
} // namespace OHOS
#endif // OHOS_ABILITY_H

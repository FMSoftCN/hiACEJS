/*
 * Copyright (c) 2020 FMSoft.
 */

/**
 * @addtogroup AbilityKit
 * @{
 *
 * @brief Provides ability-related functions, including ability lifecycle callbacks and functions for connecting to or
 *        disconnecting from Particle Abilities.
 *
 * Abilities are classified into Feature Abilities and Particle Abilities. Feature Abilities support the Page template,
 * and Particle Abilities support the Service template. An ability using the Page template is called a Page ability for
 * short and that using the Service template is called a Service ability.
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file ability.h
 *
 * @brief Declares ability-related functions, including ability lifecycle callbacks and functions for connecting to or
 *        disconnecting from Particle Abilities.
 *
 * As the fundamental unit of OpenHarmony applications, abilities are classified into Feature Abilities and Particle
 * Abilities. Feature Abilities support the Page template, and Particle Abilities support the Service template.
 * An ability using the Page template is called Page ability for short and that using the Service template
 * is called Service ability.
 *
 * @since 1.0
 * @version 1.0
 */
#ifndef OHOS_ABILITY_H
#define OHOS_ABILITY_H

#include <string>
#include <components/root_view.h>

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

/**
 * @brief Declares ability-related functions, including ability lifecycle callbacks and functions for connecting to or
 *        disconnecting from Particle Abilities.
 *
 * As the fundamental unit of OpenHarmony applications, abilities are classified into Feature Abilities and Particle
 * Abilities. Feature Abilities support the Page template, and Particle Abilities support the Service template.
 * An ability using the Page template is called Page ability for short and that using the Service template
 * is called Service ability.
 *
 * @since 1.0
 * @version 1.0
 */
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

private:
    typedef enum {
        START,
        INACTIVE,
        ACTIVE,
        BACKGROUND,
        STOP,
    } Action;

    void Init(uint64_t token, int abilityType, bool isNativeApp);
    int GetState() const;
    std::string GetDumpInfo() const;

    int abilityState_ { 0 };
    int abilityType_ { 0 };
    uint64_t token_ { 0 };
    static const int MAX_OBJECTS = 6;
};
} // namespace OHOS
#endif // OHOS_ABILITY_H

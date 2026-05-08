#pragma once

/*
 * VaneWindward Cirque tuning — applied LAST in the QMK config chain via the
 * users/<USER_NAME>/post_config.h mechanism. Earlier attempts via the keymap's
 * config.h ran before keyboards/bastardkb/dilemma/config.h, so its
 * POINTING_DEVICE_TASK_THROTTLE_MS=10 silently overrode our override.
 *
 * USER_NAME defaults to KEYMAP in build_keyboard.mk; with KEYMAP=vanewindward
 * the build's USER_PATH resolves to users/vanewindward/ (this directory) and
 * picks up post_config.h via POST_CONFIG_H, which is appended after the full
 * CONFIG_H chain.
 */

#undef POINTING_DEVICE_TASK_THROTTLE_MS
#define POINTING_DEVICE_TASK_THROTTLE_MS 1

#define CIRQUE_PINNACLE_TAP_ENABLE
#define CIRQUE_PINNACLE_TAPPING_TERM 200
#define CIRQUE_PINNACLE_TOUCH_DEBOUNCE 50

#define POINTING_DEVICE_GESTURES_CURSOR_GLIDE_ENABLE

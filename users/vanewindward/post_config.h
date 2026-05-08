#pragma once

#ifdef POINTING_DEVICE_TASK_THROTTLE_MS
#  if POINTING_DEVICE_TASK_THROTTLE_MS == 10
#    error "VANE-POST: dilemma ran first (THROTTLE=10) — post_config.h CAN override"
#  else
#    error "VANE-POST: throttle is something else"
#  endif
#else
#  error "VANE-POST: post_config.h ran BEFORE dilemma — same problem as keymap config.h"
#endif

#undef POINTING_DEVICE_TASK_THROTTLE_MS
#define POINTING_DEVICE_TASK_THROTTLE_MS 1

#define CIRQUE_PINNACLE_TAP_ENABLE
#define CIRQUE_PINNACLE_TAPPING_TERM 200
#define CIRQUE_PINNACLE_TOUCH_DEBOUNCE 50

#define POINTING_DEVICE_GESTURES_CURSOR_GLIDE_ENABLE

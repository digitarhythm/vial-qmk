
// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#define _BASE    0
#define _BASE2   1
#define _LOWER   2
#define _RAISE   3
#define _ADJUST  4
#define _ADJUST2 5

enum {
  _MAC,
  _WIN
} os_layer_num;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
            _______,        _______,     RGUI(KC_0),        KC_MUTE,        _______,
            _______,        _______,        _______,        _______,        _______,
            _______,        _______,        _______,        _______,        _______,
            _______,        _______,        _______,        _______,        _______
  ),
  [1] = LAYOUT(
            _______,        _______,        _______,        _______,        _______,
            _______,        _______,        _______,        _______,        _______,
            _______,        _______,        _______,        _______,        _______,
            _______,        _______,        _______,        _______,        _______
  ),
  [2] = LAYOUT(
            _______,        _______,        _______,        _______,        _______,
            _______,        _______,        _______,        _______,        _______,
            _______,        _______,        _______,        _______,        _______,
            _______,        _______,        _______,        _______,        _______
  ),
  [3] = LAYOUT(
            _______,        _______,        _______,        _______,        _______,
            _______,        _______,        _______,        _______,        _______,
            _______,        _______,        _______,        _______,        _______,
            _______,        _______,        _______,        _______,        _______
  ),
  [4] = LAYOUT(
            _______,        _______,        _______,        _______,        _______,
            _______,        _______,        _______,        _______,        _______,
            _______,        _______,        _______,        _______,        _______,
            _______,        _______,        _______,        _______,        _______
  ),
  [5] = LAYOUT(
            _______,        _______,        _______,        _______,        _______,
            _______,        _______,        _______,        _______,        _______,
            _______,        _______,        _______,        _______,        _______,
            _______,        _______,        _______,        _______,        _______
  )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
  [_BASE]    = { ENCODER_CCW_CW(     LGUI(KC_Z),     SGUI(KC_Z)), ENCODER_CCW_CW(  RGUI(KC_PLUS),  RGUI(KC_MINS)), ENCODER_CCW_CW(        KC_VOLD,        KC_VOLU),
  [_BASE2]   = { ENCODER_CCW_CW(        _______,        _______), ENCODER_CCW_CW(        _______,        _______), ENCODER_CCW_CW(        _______,        _______),
  [_LOWER]   = { ENCODER_CCW_CW(        _______,        _______), ENCODER_CCW_CW(        _______,        _______), ENCODER_CCW_CW(        _______,        _______),
  [_RAISE]   = { ENCODER_CCW_CW(        _______,        _______), ENCODER_CCW_CW(        _______,        _______), ENCODER_CCW_CW(        _______,        _______),
  [_ADJUST]  = { ENCODER_CCW_CW(        _______,        _______), ENCODER_CCW_CW(        _______,        _______), ENCODER_CCW_CW(        _______,        _______),
  [_ADJUST2] = { ENCODER_CCW_CW(        _______,        _______), ENCODER_CCW_CW(        _______,        _______), ENCODER_CCW_CW(        _______,        _______)
};
#endif

#include "qmk_analog_stick.h"

#ifdef OS_DETECTION_ENABLE
#include "os_detection.h"
#endif

void keyboard_post_init_user(void) {
    analog_stick_init();

#ifdef OS_DETECTION_ENABLE
    wait_ms(400);
    switch (detected_host_os()) {
        case OS_WINDOWS:
        case OS_LINUX:
            layer_move(_WIN);
            break;
        case OS_MACOS:
        case OS_IOS:
        default:
            layer_move(_MAC);
            break;
    }
#endif
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    return analog_stick_update(mouse_report);
}


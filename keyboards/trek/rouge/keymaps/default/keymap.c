
// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#ifdef OS_DETECTION_ENABLE
#include "os_detection.h"
#endif

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

enum custom_keycodes {
    JS_CALIB_START = SAFE_RANGE,  // キャリブレーション開始
    JS_CALIB_END,                 // キャリブレーション終了・EEPROM 保存
    JS_CALIB_RESET                // EEPROM 消去・デフォルト値に戻す
};

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

void keyboard_post_init_user(void) {
#ifdef OS_DETECTION_ENABLE
    wait_ms(100);
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

    analog_stick_init();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case JS_CALIB_START:
                analog_stick_calibration_start();
                return false;
            case JS_CALIB_END:
                analog_stick_calibration_end();
                return false;
            case JS_CALIB_RESET:
                analog_stick_calibration_reset();
                return false;
        }
    }
    return true;
}

#define SCROLL_SPEED_DIV 2048

static int16_t scroll_accum_h = 0;
static int16_t scroll_accum_v = 0;

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    mouse_report = analog_stick_update(mouse_report);

    if (IS_LAYER_ON(_ADJUST2)) {
        scroll_accum_h += mouse_report.x;
        scroll_accum_v -= mouse_report.y;
        mouse_report.x = 0;
        mouse_report.y = 0;
        mouse_report.h = scroll_accum_h / SCROLL_SPEED_DIV;
        mouse_report.v = scroll_accum_v / SCROLL_SPEED_DIV;
        scroll_accum_h %= SCROLL_SPEED_DIV;
        scroll_accum_v %= SCROLL_SPEED_DIV;
    } else {
        scroll_accum_h = 0;
        scroll_accum_v = 0;
    }

    return mouse_report;
}


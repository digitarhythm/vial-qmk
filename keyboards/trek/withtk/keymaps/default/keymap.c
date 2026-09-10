// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#define _BASE    0
#define _BASE2   1
#define _LOWER   2
#define _RAISE   3
#define _ADJUST  4
#define _ADJUST2 5

// OS-specific keys are handled by HostOS (HOS(n), quantum/host_os).
// Layer switching on OS detection was removed, so per-OS base layers are no longer needed.

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
    LGUI(KC_0),      KC_MUTE,      KC_ESC,       KC_ENT,       KC_BSPC,
       KC_HOME,       KC_END,       KC_P7,        KC_P8,         KC_P9,
            TG(1),                  KC_P4,        KC_P5,         KC_P6,
                                    KC_P1,        KC_P2,         KC_P3,
                                    KC_P0,      KC_PDOT, LT(2,KC_PPLS)
  ),
  [1] = LAYOUT(
    LCTL(KC_0),      _______,     _______,      _______,       _______,
       _______,      _______,     _______,      _______,       _______,
            TG(1),                _______,      _______,       _______,
                                  _______,      _______,       _______,
                                  _______,      _______,       _______
  ),
  [2] = LAYOUT(
       _______,      _______,     _______,      _______,       _______,
       _______,      _______,     _______,      _______,       _______,
          _______,                _______,      _______,       _______,
                                  _______,        KC_UP,       _______,
                                  KC_LEFT,      KC_DOWN,      KC_RIGHT
  ),
  [3] = LAYOUT(
       _______,      _______,     _______,      _______,       _______,
       _______,      _______,     _______,      _______,       _______,
          _______,                _______,      _______,       _______,
                                  _______,      _______,       _______,
                                  _______,      _______,       _______
  ),
  [4] = LAYOUT(
       _______,      _______,     RGB_MOD,     RGB_RMOD,       RGB_TOG,
       _______,      _______,     RGB_SPD,      RGB_SPI,       _______,
          _______,                RGB_VAD,      RGB_VAI,       _______,
                                  RGB_HUD,      RGB_HUI,       _______,
                                  RGB_SAD,      RGB_SAI,       _______
  ),
  [5] = LAYOUT(
       _______,      _______,        KC_H,   LGUI(KC_Z),     LSG(KC_Z),
       _______,      _______,      KC_ESC,         KC_X,       KC_BSPC,
            TG(1),                   KC_D,         KC_M,          KC_R,
                            LGUI(KC_SLSH),         KC_E,          KC_W,
                                  KC_LGUI, LSFT_T(KC_V),        KC_ENT
  )
};

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = {
  {
    {      7,      6,      0,      1,      2 },
    {      8,      9,      5,      4,      3 },
    { NO_LED,     16,     10,     11,     12 },
    { NO_LED, NO_LED,     15,     14,     13 },
    { NO_LED, NO_LED,     17,     18,     19 }
  }, {
    { 112,   0 }, { 168,   0 }, { 224,   0 }, { 224,  16 }, { 168,  16 },
    { 112,  16 }, {  56,  24 }, {   0,  24 }, {   0,  40 }, {  56,  40 },
                  { 112,  32 }, { 168,  32 }, { 224,  32 }, { 224,  48 },
                                { 168,  48 }, { 112,  48 }, {  28,  56 },
                                { 112,  64 }, { 168,  64 }, { 224,  64 }
  }, {
    4,4,4,4,4,
    4,4,4,4,4,
    4,4,4,4,4,
    4,4,4,4,4
  }
};
#endif

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
  [_BASE]    = { ENCODER_CCW_CW(LGUI(KC_MINS), LGUI(KC_PLUS)), ENCODER_CCW_CW(KC_VOLD, KC_VOLU),  ENCODER_CCW_CW(KC_WH_D, KC_WH_U) },
  [_BASE2]   = { ENCODER_CCW_CW(LCTL(KC_MINS), LCTL(KC_PLUS)), ENCODER_CCW_CW(KC_VOLU, KC_VOLD),  ENCODER_CCW_CW(KC_WH_U, KC_WH_D) },
  [_LOWER]   = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI),             ENCODER_CCW_CW(RGB_RMOD, RGB_MOD), ENCODER_CCW_CW(_______, _______) },
  [_RAISE]   = { ENCODER_CCW_CW(_______, _______),             ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______) },
  [_ADJUST]  = { ENCODER_CCW_CW(_______, _______),             ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______) },
  [_ADJUST2] = { ENCODER_CCW_CW(_______, _______),             ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______) }
};
#endif

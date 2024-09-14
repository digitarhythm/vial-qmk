// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
    LGUI(KC_D),   KC_MUTE,       KC_PMNS,      KC_PAST,       KC_PSLS,
    LGUI(KC_Z), LSG(KC_Z),         KC_P7,        KC_P8,         KC_P9,
                    TG(1),         KC_P4,        KC_P5,         KC_P6,
                                   KC_P1,        KC_P2,         KC_P3,
                                   KC_P0,      KC_PDOT, LT(2,KC_PPLS)
  ),
  [1] = LAYOUT(
       _______,   _______,          KC_H,   LGUI(KC_Z),     LSG(KC_Z),
       _______,   _______,        KC_ESC,         KC_X,       KC_BSPC,
                    TG(1),          KC_D,         KC_M,          KC_R,
                           LGUI(KC_SLSH),         KC_E,          KC_W,
                                 KC_LGUI, LSFT_T(KC_V),        KC_ENT
  ),
  [2] = LAYOUT(
       _______,   _______,       RGB_MOD,     RGB_RMOD,       RGB_TOG,
       _______,   _______,       RGB_SPD,      RGB_SPI,       _______,
                  _______,       RGB_VAD,      RGB_VAI,       _______,
                                 RGB_HUD,      RGB_HUI,       _______,
                                 RGB_SAD,      RGB_SAI,       _______
  ),
  [3] = LAYOUT(
       _______,   _______,       _______,      _______,       _______,
       _______,   _______,       _______,      _______,       _______,
                  _______,       _______,      _______,       _______,
                                 _______,      _______,       _______,
                                 _______,      _______,       _______
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
/* layer 0 */    [0] = { ENCODER_CCW_CW(LGUI(KC_MINS), LGUI(KC_PLUS)), ENCODER_CCW_CW(KC_WH_D, KC_WH_U),  ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
/* layer 1 */    [1] = { ENCODER_CCW_CW(_______, _______),             ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______) },
/* layer 2 */    [2] = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI),             ENCODER_CCW_CW(RGB_RMOD, RGB_MOD), ENCODER_CCW_CW(_______, _______) },
/* layer 3 */    [3] = { ENCODER_CCW_CW(_______, _______),             ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______) }
};
#endif


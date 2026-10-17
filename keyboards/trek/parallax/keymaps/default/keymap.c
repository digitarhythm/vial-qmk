/*
Copyright 2021 Salicylic_Acid
Copyright 2026 Hajime Oh-yake (@Hajime Oh-yake)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "host_os.h"

#define _BASE   0
#define _RAISE  1
#define _ADJUST 2

// OS-specific keys are HostOS keys (HOS(n), quantum/host_os): the firmware picks the
// macOS / Windows / Linux keycode at run time, so the former rgbmatrix_mac and
// rgbmatrix_win keymaps are merged into this one.
//
//  HOS | where                 | macOS           | Windows         | Linux / default
//  ----+-----------------------+-----------------+-----------------+-----------------
//   0  | L0 left thumb         | LGUI_T(KC_BSPC) | LCTL_T(KC_BSPC) | LCTL_T(KC_BSPC)
//   1  | L0 right thumb        | RGUI_T(KC_ENT)  | RCTL_T(KC_ENT)  | RCTL_T(KC_ENT)
//   2  | L0 right thumb        | RCTL_T(KC_LNG1) | RGUI_T(KC_LNG1) | RGUI_T(KC_LNG1)
//   3  | L1 "G"                | -               | LGUI(KC_G)      | -
//   4  | L1 "V"                | -               | LGUI(KC_V)      | -
//   5  | L1 "N"                | LGUI(KC_LBRC)   | KC_WBAK         | KC_WBAK
//   6  | L1 "M"                | LGUI(KC_RBRC)   | KC_WFWD         | KC_WFWD
//   7  | L0 left outer thumb   | (empty: was TG(1), assign per OS in Vial)       |
//  8-15| (spare)               |                 |                 |
//
// Layers: 0 base, 1 raise (LT(1,KC_SPC)), 2 adjust (MO(2)). The former layer 1 (a fixed
// macOS thumb layout for manual override) was dropped: HostOS makes it redundant and its
// 112 EEPROM bytes pay for 32 tap dance slots (16 HostOS + 16 ordinary).
//
// These defaults are written into a HostOS slot only while it is empty (right after an
// EEPROM reset); anything set from the Vial GUI wins.
const host_os_entry_t host_os_actions[HOST_OS_COUNT] = {
    [0] = HOST_OS(.kc_macos = LGUI_T(KC_BSPC), .kc_windows = LCTL_T(KC_BSPC), .kc_linux = LCTL_T(KC_BSPC), .kc_default = LCTL_T(KC_BSPC)),
    [1] = HOST_OS(.kc_macos = RGUI_T(KC_ENT),  .kc_windows = RCTL_T(KC_ENT),  .kc_linux = RCTL_T(KC_ENT),  .kc_default = RCTL_T(KC_ENT)),
    [2] = HOST_OS(.kc_macos = RCTL_T(KC_LNG1), .kc_windows = RGUI_T(KC_LNG1), .kc_linux = RGUI_T(KC_LNG1), .kc_default = RGUI_T(KC_LNG1)),
    [3] = HOST_OS(.kc_windows = LGUI(KC_G)),
    [4] = HOST_OS(.kc_windows = LGUI(KC_V)),
    [5] = HOST_OS(.kc_macos = LGUI(KC_LBRC), .kc_windows = KC_WBAK, .kc_linux = KC_WBAK, .kc_default = KC_WBAK),
    [6] = HOST_OS(.kc_macos = LGUI(KC_RBRC), .kc_windows = KC_WFWD, .kc_linux = KC_WFWD, .kc_default = KC_WFWD),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
  //.---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------.
              QK_GESC,            KC_Q,            KC_W,            KC_E,            KC_R,            KC_T,         KC_HOME,         KC_PGUP,            KC_Y,            KC_U,            KC_I,            KC_O,         KC_SCLN,         KC_MINS,
  //|----------------+----------------+----------------+----------------+----------------+----------------+----------------+----------------+----------------+----------------+----------------+----------------+----------------+----------------|
       LCTL_T(KC_TAB),            KC_A,            KC_S,            KC_D,            KC_F,            KC_G,          KC_END,         KC_PGDN,            KC_H,            KC_J,            KC_K,            KC_L,            KC_P,         KC_QUOT,
  //|----------------+----------------+----------------+----------------+----------------+----------------+----------------+----------------+----------------+----------------+----------------+----------------+----------------+----------------|
              KC_LSFT,            KC_Z,            KC_X,            KC_C,            KC_V,            KC_B,           MO(2),           MO(2),            KC_B,            KC_N,            KC_M,         KC_COMM,          KC_DOT, RSFT_T(KC_SLSH),
  //|----------------+----------------+----------------+----------------+----------------+----------------+----------------+----------------+----------------+----------------+----------------+----------------+----------------+----------------|
               HOS(7),                  LALT_T(KC_LNG2),          HOS(0),    LT(1,KC_SPC),                          KC_MUTE,                                      LT(1,KC_SPC),          HOS(1),          HOS(2),                          KC_MPLY
  //.---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------.
  ),
  [_RAISE] = LAYOUT(
  //.---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------.
               KC_GRV,            KC_1,            KC_2,            KC_3,            KC_4,            KC_5,            KC_6,            KC_7,            KC_6,            KC_7,            KC_8,            KC_9,            KC_0,          KC_EQL,
  //|----------------+----------------+----------------+----------------+----------------+----------------+----------------+----------------+----------------+----------------+----------------+----------------+----------------+----------------|
              _______,         _______,         _______,         _______,         _______,          HOS(3),         _______,         _______,         KC_LEFT,         KC_DOWN,           KC_UP,        KC_RIGHT,         _______,         KC_BSLS,
  //|----------------+----------------+----------------+----------------+----------------+----------------+----------------+----------------+----------------+----------------+----------------+----------------+----------------+----------------|
              _______,         _______,         _______,         _______,          HOS(4),         _______,         _______,         _______,         _______,          HOS(5),          HOS(6),         KC_LBRC,         KC_RBRC,         _______,
  //|----------------+----------------+----------------+----------------+----------------+----------------+----------------+----------------+----------------+----------------+----------------+----------------+----------------+----------------|
              _______,                          _______,          KC_DEL,           MO(2),                          RGB_TOG,                                             MO(2),           KC_F2,         _______,                          _______
  //.---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------.
  ),
  [_ADJUST] = LAYOUT(
  //.---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------.
              KC_SLEP,           KC_F1,           KC_F2,           KC_F3,           KC_F4,           KC_F5,           KC_F6,           KC_F7,           KC_F8,           KC_F9,          KC_F10,          KC_F11,          KC_F12,          KC_F13,
  //|----------------+----------------+----------------+----------------+----------------+----------------+----------------+----------------+----------------+----------------+----------------+----------------+----------------+----------------|
              _______,         RGB_VAI,         RGB_VAD,         RGB_SPI,         RGB_SPD,         RGB_MOD,        RGB_RMOD,         _______,         _______,         _______,         _______,         _______,         _______,         _______,
  //|----------------+----------------+----------------+----------------+----------------+----------------+----------------+----------------+----------------+----------------+----------------+----------------+----------------+----------------|
              _______,         RGB_HUI,         RGB_HUD,         RGB_SAI,         RGB_SAD,         _______,         _______,         _______,         _______,         _______,         _______,         _______,         _______,         _______,
  //|----------------+----------------+----------------+----------------+----------------+----------------+----------------+----------------+----------------+----------------+----------------+----------------+----------------+----------------|
              _______,                          _______,         _______,         _______,                          _______,                                           _______,         _______,         _______,                          _______
  //.---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------.
  )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
  [_BASE]   = { ENCODER_CCW_CW(LCTL(KC_PGUP), LCTL(KC_PGDN)), ENCODER_CCW_CW(KC_WH_D, KC_WH_U), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
  [_RAISE]  = { ENCODER_CCW_CW(_______, _______),             ENCODER_CCW_CW(KC_WH_L, KC_WH_R), ENCODER_CCW_CW(_______, _______) },
  [_ADJUST] = { ENCODER_CCW_CW(_______, _______),             ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
};
#endif

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = {{
    // Key Matrix to LED Index
    { NO_LED,      0,      1,      2,      3,      4,      5 },
    { NO_LED,     23,     22,     21,     20,     19,     18 },
    { NO_LED,     24,     25,     26,     27,     28,     29 },
    { NO_LED, NO_LED,     41,     40,     39, NO_LED, NO_LED },
    {      6,      7,      8,      9,     10,     11, NO_LED },
    {     17,     16,     15,     14,     13,     12, NO_LED },
    {     30,     31,     32,     33,     34,     35, NO_LED },
    { NO_LED, NO_LED,     38,     37,     36, NO_LED, NO_LED }
  }, {
      // LED Index to Physical Position
    {   0,   0 }, {  20,   0 }, {  40,   0 }, {  61,   0 }, {  81,   0 }, { 101,   0 },
    { 122,   0 }, { 142,   0 }, { 162,   0 }, { 183,   0 }, { 203,   0 }, { 224,   0 },
    { 224,  20 }, { 203,  20 }, { 183,  20 }, { 162,  20 }, { 142,  21 }, { 122,  21 },
    { 101,  20 }, {  81,  20 }, {  61,  20 }, {  40,  20 }, {  20,  20 }, {   0,  20 },
    {   0,  42 }, {  20,  42 }, {  40,  42 }, {  61,  42 }, {  81,  42 }, { 101,  42 },
    { 122,  42 }, { 142,  42 }, { 162,  42 }, { 183,  42 }, { 203,  42 }, { 223,  42 },
                  { 203,  64 }, { 183,  64 }, { 162,  64 },
                                {  61,  64 }, {  40,  64 }, {  20,  64 }
  }, {
  // LED Index to Flag
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4
}};
#endif

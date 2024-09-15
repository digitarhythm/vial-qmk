// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#define _BASE   0
#define _LOWER  1
#define _RAISE  2
#define _ADJUST 3

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
  //|---------------+----------------+----------------+-------------+----------+--------+--------------+-------------+---------------+-----------------+--------+----------------|
             QK_GESC,            KC_Q,            KC_W,         KC_E,      KC_R,    KC_T,          KC_Y,         KC_U,           KC_I,             KC_O,    KC_P,         KC_MINS,
  //|---------------+----------------+----------------+-------------+----------+--------+--------------+-------------+---------------+-----------------+--------+----------------|
      LCTL_T(KC_TAB),            KC_A,            KC_S,         KC_D,      KC_F,    KC_G,          KC_H,         KC_J,           KC_K,             KC_L, KC_SCLN,         KC_QUOT,
  //|---------------+----------------+----------------+-------------+----------+--------+--------------+-------------+---------------+-----------------+--------+----------------|
             KC_LSFT,            KC_Z,            KC_X,         KC_C,      KC_V,    KC_B,          KC_B,         KC_N,           KC_M,          KC_COMM,  KC_DOT, RSFT_T(KC_SLSH),
  //|---------------+----------------+----------------+-------------+----------+--------+--------------+-------------+---------------+-----------------+--------+----------------|
             _______, LALT_T(KC_LNG2), LGUI_T(KC_BSPC), LT(2,KC_SPC),            _______,                LT(2,KC_SPC), RGUI_T(KC_ENT),  RCTL_T(KC_LNG1),                  _______
  //|---------------+----------------+----------------+-------------+----------+--------+--------------+-------------+---------------+-----------------+--------+----------------|
  ),
  [1] = LAYOUT(
  //|---------------+----------------+----------------+-------------+----------+--------+--------------+-------------+---------------+-----------------+--------+----------------|
             _______,         _______,         _______,      _______,   _______, _______,       _______,      _______,        _______,          _______, _______,         _______,
  //|---------------+----------------+----------------+-------------+----------+--------+--------------+-------------+---------------+-----------------+--------+----------------|
             _______,         _______,         _______,      _______,   _______, _______,       _______,      _______,        _______,          _______, _______,         _______,
  //|---------------+----------------+----------------+-------------+----------+--------+--------------+-------------+---------------+-----------------+--------+----------------|
             _______,         _______,         _______,      _______,   _______, _______,       _______,      _______,        _______,          _______, _______,         _______,
  //|---------------+----------------+----------------+-------------+----------+--------+--------------+-------------+---------------+-----------------+--------+----------------|
             _______,         _______, LCTL_T(KC_BSPC),      _______,            _______,                     _______, RCTL_T(KC_ENT),  RGUI_T(KC_LNG1),                  _______
  //|---------------+----------------+----------------+-------------+----------+--------+--------------+-------------+---------------+-----------------+--------+----------------|
  ),
  [2] = LAYOUT(
  //|---------------+----------------+----------------+-------------+----------+--------+--------------+-------------+---------------+-----------------+--------+----------------|
              KC_GRV,            KC_1,            KC_2,         KC_3,      KC_4,    KC_5,          KC_6,         KC_7,           KC_8,             KC_9,    KC_0,          KC_EQL,
  //|---------------+----------------+----------------+-------------+----------+--------+--------------+-------------+---------------+-----------------+--------+----------------|
           LSG(KC_4),         _______,         _______,      _______,   _______, _______,       KC_LEFT,      KC_DOWN,          KC_UP,         KC_RIGHT, _______,         KC_BSLS,
  //|---------------+----------------+----------------+-------------+----------+--------+--------------+-------------+---------------+-----------------+--------+----------------|
             _______,         _______,         _______,      _______, LSG(KC_V), _______, LGUI(KC_LBRC),      KC_PGDN,        KC_PGUP,          KC_LBRC, KC_RBRC,         _______,
  //|---------------+----------------+----------------+-------------+----------+--------+--------------+-------------+---------------+-----------------+--------+----------------|
             _______,         _______,          KC_DEL,        MO(3),            _______,                       MO(3),          KC_F2,          _______,                  _______
  //|---------------+----------------+----------------+-------------+----------+--------+--------------+-------------+---------------+-----------------+--------+----------------|
  ),
  [3] = LAYOUT(
  //|---------------+----------------+----------------+-------------+----------+--------+--------------+-------------+---------------+-----------------+--------+----------------|
               TG(1),           KC_F1,           KC_F2,        KC_F3,     KC_F4,   KC_F5,         KC_F6,        KC_F7,          KC_F8,            KC_F9,  KC_F10,         KC_SLEP,
  //|---------------+----------------+----------------+-------------+----------+--------+--------------+-------------+---------------+-----------------+--------+----------------|
             _______,         _______,         _______,      _______,   _______, _______,       _______,      _______,        _______,          _______, _______,         _______,
  //|---------------+----------------+----------------+-------------+----------+--------+--------------+-------------+---------------+-----------------+--------+----------------|
             _______,         _______,         _______,      _______,   _______, _______,       _______,      _______,        _______,          _______, _______,         _______,
  //|---------------+----------------+----------------+-------------+----------+--------+--------------+-------------+---------------+-----------------+--------+----------------|
             _______,         _______,         _______,      _______,            _______,                     _______,        _______,          _______,                  _______
  //|---------------+----------------+----------------+-------------+----------+--------+--------------+-------------+---------------+-----------------+--------+----------------|
  )
};

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = {
  {
    {      5,      4,      3,      2,      1,      0 },
    {      6,      7,      8,      9,     10,     11 },
    {     17,     16,     15,     14,     13,     12 },
    { NO_LED,     18,     19,     20, NO_LED, NO_LED },
    {     41,     40,     39,     38,     37,     36 },
    {     30,     31,     32,     33,     34,     35 },
    {     29,     28,     27,     26,     25,     24 },
    { NO_LED,     21,     22,     23, NO_LED, NO_LED }
  }, {
    {  93,   0 }, {  74,   0 }, {  56,   0 }, {  37,   0 }, {  18,   0 }, {   0,   0 },
    {   0,  21 }, {  18,  21 }, {  37,  21 }, {  56,  21 }, {  74,  21 }, {  93,  21 },
    {  93,  42 }, {  74,  42 }, {  56,  42 }, {  37,  42 }, {  18,  42 }, {   0,  42 },
                  {  18,  64 }, {  37,  64 }, {  56,  64 },
    { 149,  64 }, { 168,  64 }, { 186,  64 }, { 224,  42 }, { 205,  42 }, { 186,  42 },
    { 168,  42 }, { 149,  42 }, { 130,  42 }, { 130,  21 }, { 149,  21 }, { 168,  21 },
    { 186,  21 }, { 205,  21 }, { 224,  21 }, { 224,   0 }, { 205,   0 }, { 186,   0 },
                  { 168,   0 }, { 149,   0 }, { 130,   0 }
  }, {
    4,4,4,4,4,4,4,4,4,4,4,4,
    4,4,4,4,4,4,4,4,4,4,4,4,
    4,4,4,4,4,4,4,4,4,4,4,4,
    4,4,4,4,4,4
  }
};
#endif

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
  [_BASE]   = { ENCODER_CCW_CW(LCTL(KC_PGUP), LCTL(KC_PGDN)), ENCODER_CCW_CW(LCTL(KC_VOLD), LCTL(KC_VOLU))            , ENCODER_CCW_CW(KC_WH_U, KC_WH_D) },
  [_LOWER]  = { ENCODER_CCW_CW(_______, _______),             ENCODER_CCW_CW(_______, _______)            , ENCODER_CCW_CW(_______, _______) },
  [_LOWER]  = { ENCODER_CCW_CW(_______, _______),             ENCODER_CCW_CW(_______, _______)            , ENCODER_CCW_CW(_______, _______) },
  [_ADJUST] = { ENCODER_CCW_CW(_______, _______),             ENCODER_CCW_CW(_______, _______)            , ENCODER_CCW_CW(_______, _______) }
};
#endif


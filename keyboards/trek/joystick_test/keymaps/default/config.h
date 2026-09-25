/* Copyright 2018 Salicylic_acid3
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#pragma once

#define VIAL_KEYBOARD_UID {0xA0, 0xF4, 0x5B, 0xC6, 0x12, 0x94, 0x05, 0x19}
#define VIAL_UNLOCK_COMBO_ROWS { 0, 0 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 1 }

// ===== アナログスティック: PSP1000（スイッチなし） =====
// 接続ピン（RP2040 ADC2 / ADC3）
#define JOYSTICK_X_PIN GP28
#define JOYSTICK_Y_PIN GP29
// PSP1000 スティックには押し込みスイッチが無いため JOYSTICK_SW_PIN は定義しない
// （未定義ならライブラリ側でクリック機能が無効になる）

// ADC レンジ（実測値: 2026-09-20、X/Y ともに 524〜1023）
// 4 つすべてを定義しているため固定レンジモードで動作する（自動レンジ学習は無効）。
// 中心値は起動時に計測され、中心から各レンジ端までを個別に ±1000 へ正規化するので
// 中心が 0〜1023 の中央に無くても問題ない。
#define JOYSTICK_ADC_X_MIN  480
#define JOYSTICK_ADC_X_MAX 1023
#define JOYSTICK_ADC_Y_MIN  525
#define JOYSTICK_ADC_Y_MAX 1023

// 取り付け向きの都合で上下のみ反転（左右はそのまま）
#define JOYSTICK_INVERT_Y 1
#define JOYSTICK_MAX_SPEED 4000
#define JOYSTICK_DEADZONE 256

/* Select hand configuration */

#ifdef RGBLED_NUM
  #undef RGBLED_NUM
#endif

#define RGB_MATRIX_LED_COUNT 54

#ifdef RGB_MATRIX_ENABLE
  #define RGB_DISABLE_WHEN_USB_SUSPENDED
  #define RGB_MATRIX_KEYPRESSES
  #define RGB_MATRIX_LED_PROCESS_LIMIT (RGB_MATRIX_LED_COUNT + 4) / 5
  #define RGB_MATRIX_LED_FLUSH_LIMIT 16
  #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 256
  #define RGB_MATRIX_DEFAULT_HUE 0
  #define RGB_MATRIX_DEFAULT_SAT 255
  #define RGB_MATRIX_DEFAULT_VAL 50
  #define RGB_MATRIX_DEFAULT_SPD 127

  #define ENABLE_RGB_MATRIX_ALPHAS_MODS
  #define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
  #define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
  #define ENABLE_RGB_MATRIX_BREATHING
  #define ENABLE_RGB_MATRIX_BAND_SAT
  #define ENABLE_RGB_MATRIX_BAND_VAL
  #define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
  #define ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
  #define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
  #define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
  #define ENABLE_RGB_MATRIX_CYCLE_ALL
  #define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
  #define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
  #define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
  #define ENABLE_RGB_MATRIX_CYCLE_OUT_IN
  #define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
  #define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
  #define ENABLE_RGB_MATRIX_CYCLE_SPIRAL
  #define ENABLE_RGB_MATRIX_DUAL_BEACON
  #define ENABLE_RGB_MATRIX_RAINBOW_BEACON
  #define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
  #define ENABLE_RGB_MATRIX_RAINDROPS
  #define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
  #define ENABLE_RGB_MATRIX_HUE_BREATHING
  #define ENABLE_RGB_MATRIX_HUE_PENDULUM
  #define ENABLE_RGB_MATRIX_HUE_WAVE
  #define ENABLE_RGB_MATRIX_PIXEL_FRACTAL
  #define ENABLE_RGB_MATRIX_PIXEL_FLOW
  #define ENABLE_RGB_MATRIX_PIXEL_RAIN
  #define ENABLE_RGB_MATRIX_TYPING_HEATMAP
  #define ENABLE_RGB_MATRIX_DIGITAL_RAIN
  #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
  #define ENABLE_RGB_MATRIX_SOLID_REACTIVE
  #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
  #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
  #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
  #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
  #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
  #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
  #define ENABLE_RGB_MATRIX_SPLASH
  #define ENABLE_RGB_MATRIX_MULTISPLASH
  #define ENABLE_RGB_MATRIX_SOLID_SPLASH
  #define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
#endif

#define LAYOUT( \
  k00, k01, k02, k03, k04, k05,       k07,       k41, k42, k43, k44, k45, k46, \
  k10, k11, k12, k13, k14, k15,  k06, k17, k40,  k51, k52, k53, k54, k55, k56, \
  k20, k21, k22, k23, k24, k25,  k16, k27, k50,  k61, k62, k63, k64, k65, k66, \
  k30,      k31, k33, k35,       k26, k37, k60,       k72, k73, k75,      k76, \
                                 k36, k70, k71                                 \
) \
{ \
  {   k00,   k01,   k02,   k03,   k04,   k05,   k06,   k07 }, \
  {   k10,   k11,   k12,   k13,   k14,   k15,   k16,   k17 }, \
  {   k20,   k21,   k22,   k23,   k24,   k25,   k26,   k27 }, \
  {   k30,   k31, KC_NO,   k33, KC_NO,   k35,   k36,   k37 }, \
\
  {   k40,   k41,   k42,   k43,   k44,   k45,   k46, KC_NO }, \
  {   k50,   k51,   k52,   k53,   k54,   k55,   k56, KC_NO }, \
  {   k60,   k61,   k62,   k63,   k64,   k65,   k66, KC_NO }, \
  {   k70,   k71,   k72,   k73, KC_NO,   k75,   k76, KC_NO }  \
}


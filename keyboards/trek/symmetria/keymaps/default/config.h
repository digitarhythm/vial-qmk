/* Copyright 2026 Hajime Oh-yake
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

#define VIAL_KEYBOARD_UID {0x37, 0xD3, 0x35, 0xC7, 0x90, 0xF0, 0xC9, 0xD1}
#define VIAL_UNLOCK_COMBO_COLS { 0, 0 }
#define VIAL_UNLOCK_COMBO_ROWS { 0, 1 }

/* Select hand configuration */

#ifdef RGBLED_NUM
  #undef RGBLED_NUM
#endif

#define RGB_MATRIX_LED_COUNT 48

#ifdef RGB_MATRIX_ENABLE
  #define RGB_DISABLE_WHEN_USB_SUSPENDED
  #define RGB_MATRIX_KEYPRESSES
  #define RGB_MATRIX_LED_PROCESS_LIMIT (RGB_MATRIX_LED_COUNT + 4) / 5
  #define RGB_MATRIX_LED_FLUSH_LIMIT 16
  #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 100
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
  K00, K01, K02, K03, K04, K05, K06, K50, K51, K52, K53, K54, K55, K56, \
  K10, K11, K12, K13, K14, K15, K16, K60, K61, K62, K63, K64, K65, K66, \
  K20, K21, K22, K23, K24, K25, K26, K70, K71, K72, K73, K74, K75, K76, \
  K30,      K32, K33, K34,      K36,           K82, K83, K84,      K86  \
) \
{ \
  {   K00,   K01,   K02,   K03,   K04,   K05,   K06 }, \
  {   K10,   K11,   K12,   K13,   K14,   K15,   K16 }, \
  {   K20,   K21,   K22,   K23,   K24,   K25,   K26 }, \
  {   K30, KC_NO,   K32,   K33,   K34, KC_NO,   K36 }, \
\
  {   K50,   K51,   K52,   K53,   K54,   K55,   K56 }, \
  {   K60,   K61,   K62,   K63,   K64,   K65,   K66 }, \
  {   K70,   K71,   K72,   K73,   K74,   K75,   K76 }, \
  { KC_NO, KC_NO,   K82,   K83,   K84, KC_NO,   K86 }  \
}


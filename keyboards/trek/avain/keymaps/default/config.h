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

#define VIAL_KEYBOARD_UID {0x00, 0xA3, 0x7D, 0x4B, 0xD5, 0x6C, 0xD0, 0x98}
#define VIAL_UNLOCK_COMBO_ROWS { 1, 2 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 0 }

/* Select hand configuration */

#define TAPPING_TERM 200
#define HOLD_ON_OTHER_KEY_PRESS
#define TAPPING_FORCE_HOLD
//#define RETRO_TAPPING

#ifdef RGBLED_NUM
  #undef RGBLED_NUM
#endif

#define RGB_MATRIX_LED_COUNT 64

#ifdef RGB_MATRIX_ENABLE
  #define RGB_DISABLE_WHEN_USB_SUSPENDED
  #define RGB_MATRIX_KEYPRESSES
  #define RGB_MATRIX_LED_PROCESS_LIMIT (RGB_MATRIX_LED_COUNT + 4) / 5
  #define RGB_MATRIX_LED_FLUSH_LIMIT 16
  #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 200
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
    k01, k02, k03, k04, k05,            k46,             k52, k53, k54, k55, k56, \
  k10, k11, k12, k13, k14, k15,    k06, k50, k51,     k62, k63, k64, k65, k75, k66, \
   k20, k21, k22, k23, k24, k25,   k16, k60, k61,    k71, k72, k73, k74, k85, k76, \
     k30, k31, k32, k33, k34, k44, k35, k26, k70,  k81, k82, k83, k84, k94, k86, \
   k40,        k41, k42,    k43,   k45, k36, k80,   k91,     k92, k93,        k96 \
) \
{ \
  { KC_NO,   k01,   k02,   k03,   k04,   k05,   k06 }, \
  {   k10,   k11,   k12,   k13,   k14,   k15,   k16 }, \
  {   k20,   k21,   k22,   k23,   k24,   k25,   k26 }, \
  {   k30,   k31,   k32,   k33,   k34,   k35,   k36 }, \
  {   k40,   k41,   k42,   k43,   k44,   k45,   k46 }, \
\
  {   k50,   k51,   k52,   k53,   k54,   k55,   k56 }, \
  {   k60,   k61,   k62,   k63,   k64,   k65,   k66 }, \
  {   k70,   k71,   k72,   k73,   k74,   k75,   k76 }, \
  {   k80,   k81,   k82,   k83,   k84,   k85,   k86 }, \
  { KC_NO,   k91,   k92,   k93,   k94, KC_NO,   k96 }  \
}

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

#define VIAL_KEYBOARD_UID {0x7B, 0x4D, 0xF0, 0xDA, 0x53, 0x0B, 0x89, 0xF7}
#define VIAL_UNLOCK_COMBO_COLS { 0, 0 }
#define VIAL_UNLOCK_COMBO_ROWS { 1, 0 }

#define HOLD_ON_OTHER_KEY_PRESS

// ジョイスティック校正値の保存先は qmk_analog_stick.c が
// JOYSTICK_EEPROM_ADDR = VIA_EEPROM_CUSTOM_CONFIG_ADDR として自動計算する。
// 予約バイト数は keyboards/trek/lettio/config.h の
// VIA_EEPROM_CUSTOM_CONFIG_SIZE で指定する（アドレスをここで直書きしてはいけない）。

/* Select hand configuration */


// K75 = アナログスティック（JS-16）の押し込みスイッチ
//       キーマトリクスには結線されておらず、matrix.c が GP13 を [7,5] に注入する
#define LAYOUT( \
  K00, K01, K02, K03, K04, K05,   K40,    K41, K42, K43, K44, K45, K55, \
  K10, K11, K12, K13, K14, K15, K25, K35, K50, K51, K52, K53, K54, K65, \
  K20, K21, K22, K23, K24, K34,           K60, K61, K62, K63, K73, K64, \
  K30,   K31,  K32,   K33,        K75,         K70,   K71,  K72,   K74  \
) \
{ \
  {   K00,   K01,   K02,   K03,   K04,   K05 }, \
  {   K10,   K11,   K12,   K13,   K14,   K15 }, \
  {   K20,   K21,   K22,   K23,   K24,   K25 }, \
  {   K30,   K31,   K32,   K33,   K34,   K35 }, \
\
  {   K40,   K41,   K42,   K43,   K44,   K45 }, \
  {   K50,   K51,   K52,   K53,   K54,   K55 }, \
  {   K60,   K61,   K62,   K63,   K64,   K65 }, \
  {   K70,   K71,   K72,   K73,   K74,   K75 }  \
}

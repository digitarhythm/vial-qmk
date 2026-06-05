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

#define VIAL_KEYBOARD_UID {0xE5, 0xEB, 0xD8, 0x0F, 0x77, 0x06, 0x13, 0x2C}
#define VIAL_UNLOCK_COMBO_COLS { 1, 3 }
#define VIAL_UNLOCK_COMBO_ROWS { 3, 3 }

#define HOLD_ON_OTHER_KEY_PRESS

// VIA custom config 領域の先頭アドレス
// = EECONFIG_SIZE(37) + VIA_MAGIC(3) + VIA_LAYOUT_OPTIONS(1) = 41
#define JOYSTICK_CALIB_EEPROM_ADDR 41

/* Select hand configuration */


#define LAYOUT( \
  K00, K01, K02, K03, K04, \
  K10, K11, K12, K13, K14, \
  K20, K21, K22, K23, K24, \
  K30, K31, K32, K33, K34  \
) \
{ \
  {   K00,   K01,   K02,   K03,   K04 }, \
  {   K10,   K11,   K12,   K13,   K14 }, \
  {   K20,   K21,   K22,   K23,   K24 }, \
  {   K30,   K31,   K32,   K33,   K34 }  \
}

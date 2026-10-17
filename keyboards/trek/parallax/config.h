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

#pragma once

/* key matrix size (pins are in keyboard.json; scanning is done by matrix.c) */
#define MATRIX_ROWS 8
#define MATRIX_COLS 7

//#define ENCODER_DIRECTION_FLIP
#define ENCODER_DEFAULT_POS 0x3

#define DEBOUNCE 50

#define TAPPING_TERM 200
#define HOLD_ON_OTHER_KEY_PRESS /* keymap default overrides this per key via qmk_settings_slim.c (Vial GUI toggle) */
#define QUICK_TAP_TERM 0
//#define RETRO_TAPPING

/* Vial: 3 layers; the 112 EEPROM bytes of a 4th layer went to 32 tap dance slots (16 HostOS + 16) */
#define DYNAMIC_KEYMAP_LAYER_COUNT 3
#define LAYER_STATE_8BIT

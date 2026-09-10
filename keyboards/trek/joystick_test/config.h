// Copyright 2024 Hajime Oh-yake (@Hajime Oh-yake)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define MATRIX_ROWS 8
#define MATRIX_COLS 8

#define DEBOUNCE 50

#define BOOTMAGIC_ROW 0
#define BOOTMAGIC_COLUMN 0

#define TAPPING_TERM 200
//#define PERMISSIVE_HOLD
#define HOLD_ON_OTHER_KEY_PRESS
//#define RETRO_TAPPING
#define QUICK_TAP_TERM 100

#define DYNAMIC_KEYMAP_LAYER_COUNT 6
#define LAYER_STATE_8BIT


// 自動レンジ学習の保存用（VIA カスタム設定領域 10 バイトを予約）
#define VIA_EEPROM_CUSTOM_CONFIG_SIZE 10

// Copyright 2026 Hajime Oh-yake (@Hajime Oh-yake)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define MATRIX_ROWS 4
#define MATRIX_COLS 5

#define JOYSTICK_X_PIN GP28
#define JOYSTICK_Y_PIN GP29

#define DEBOUNCE 50

#define BOOTMAGIC_ROW 3
#define BOOTMAGIC_COLUMN 2

#define TAPPING_TERM 200
//#define PERMISSIVE_HOLD
#define HOLD_ON_OTHER_KEY_PRESS
//#define RETRO_TAPPING
#define QUICK_TAP_TERM 100

#define DYNAMIC_KEYMAP_LAYER_COUNT 6
#define LAYER_STATE_8BIT

// モデル未指定 → 自動レンジ学習モード
//#define JH16

// 学習レンジの EEPROM 保存用（VIA カスタム設定領域 10 バイトを予約）
#define VIA_EEPROM_CUSTOM_CONFIG_SIZE 10

// スティック中央のデッドゾーン
#define JOYSTICK_DEADZONE 30

// ハイブリッド速度モード: 傾き80%までは比例速度、超えると加速
#define JOYSTICK_ACCEL_THRESHOLD 900
#define JOYSTICK_DIRECT_SPEED 600

// ハイブリッド速度モード中は下記カーブ設定は使用されない
//#define JOYSTICK_CURVE_LOW_GAIN 10

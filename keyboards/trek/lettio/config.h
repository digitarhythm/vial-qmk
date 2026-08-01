// Copyright 2026 Hajime Oh-yake (@Hajime Oh-yake)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// 行ピン4本 × 列ピン6列のデュプレックスマトリクス
//   論理行 0〜3: COL2ROW（行を駆動して列を読む）
//   論理行 4〜7: ROW2COL（列を駆動して行を読む）
#define MATRIX_ROWS 8
#define MATRIX_COLS 6

#define JOYSTICK_X_PIN GP28
#define JOYSTICK_Y_PIN GP29

#define DEBOUNCE 50

// Esc（matrix[0][0] = K00）を押しながら USB 接続でブートローダーへ（QMK 標準の配置）
//   ジョイスティック押し込み [7,5] は GP13 の結線が未確認のため使わない。
//   GP13 が起動時に LOW と読まれると毎回 EEPROM を消してブートローダへ飛んでしまう。
#define BOOTMAGIC_ROW 0
#define BOOTMAGIC_COLUMN 0

#define TAPPING_TERM 200
//#define PERMISSIVE_HOLD
#define HOLD_ON_OTHER_KEY_PRESS
//#define RETRO_TAPPING
#define QUICK_TAP_TERM 100

#define DYNAMIC_KEYMAP_LAYER_COUNT 6
#define LAYER_STATE_8BIT

// 学習レンジの EEPROM 保存用（VIA カスタム設定領域 10 バイトを予約）
//   保存内容: magic(2) + x_min(2) + x_max(2) + y_min(2) + y_max(2) = 10 バイト
//   保存先アドレスは qmk_analog_stick.c が VIA_EEPROM_CUSTOM_CONFIG_ADDR から自動計算する。
//
// 実測した EEPROM マップ（TOTAL_EEPROM_BYTE_COUNT = 4096）
//      0 -   36  コア EEPROM (EECONFIG_SIZE = 37)
//     37 -   39  VIA magic (3)
//     40 -   40  VIA layout options (1)
//     41 -   50  ★ジョイスティック校正値（この予約領域 10 バイト）
//     51 -  626  ダイナミックキーマップ (6層 x 8行 x 6列 x 2 = 576)
//    627 -  698  エンコーダ (3基 x 6層 x 2方向 x 2 = 72)
//    699 -  738  QMK settings (40)
//    739 - 1058  Vial タップダンス (320)
//   1059 - 1378  Vial コンボ (320)
//   1379 - 1698  Vial キーオーバーライド (320)
//   1699 - 1890  Vial Alt Repeat Key (192)
//   1891 - 4095  ダイナミックマクロ (2205)
//
// 注意: 51 以降の全領域の開始アドレスは MATRIX_ROWS / MATRIX_COLS /
//       DYNAMIC_KEYMAP_LAYER_COUNT から算出される。これらを変更すると
//       エンコーダ以降の保存内容が別アドレスに移動するため、
//       書き込み済みの EEPROM は必ずリセットすること。
#define VIA_EEPROM_CUSTOM_CONFIG_SIZE 10

// アナログスティックでの縦スクロール方向を上下反転
//#define JOYSTICK_SCROLL_INVERT_V 1

// ジョイスティックの最大速度
#define JOYSTICK_MAX_SPEED 5000

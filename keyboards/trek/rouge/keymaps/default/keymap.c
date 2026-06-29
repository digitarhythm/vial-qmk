
// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#ifdef OS_DETECTION_ENABLE
#include "os_detection.h"
#endif

#define _BASE    0
#define _BASE2   1
#define _LOWER   2
#define _RAISE   3
#define _ADJUST  4
#define _ADJUST2 5

enum {
  _MAC,
  _WIN
} os_layer_num;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,  KC_BTN1,        LGUI(KC_0),     KC_MUTE,       0x0909,
        MO(2),   KC_BTN1,        KC_BTN2,        KC_WH_U,       LGUI(KC_H),
        MO(5),   LGUI(KC_LBRC),  LGUI(KC_RBRC),  KC_WH_D,       KC_F3,
        KC_ENT,  SGUI(KC_LBRC),  TG(1),          SGUI(KC_RBRC), LGUI(KC_TAB)
    ),
    [1] = LAYOUT(
        KC_TRNS, KC_TRNS,        LCTL(KC_0),     KC_TRNS,       LGUI(KC_UP),
        MO(3),   KC_TRNS,        KC_TRNS,        KC_TRNS,       LGUI(KC_DOWN),
        MO(5),   LALT(KC_LEFT),  LALT(KC_RGHT),  KC_TRNS,       LGUI(KC_TAB),
        KC_TRNS, LCTL(KC_PGUP),  KC_TRNS,        RCTL(KC_PGDN), LCTL(KC_TAB)
    ),
    [2] = LAYOUT(
        KC_TRNS, KC_TRNS,        KC_TRNS,        KC_TRNS,       KC_TRNS,
        KC_TRNS, KC_LEFT,        KC_RGHT,        KC_PGUP,       MO(4),
        KC_TRNS, LSFT(KC_COMM),  LSFT(KC_DOT),   KC_PGDN,       SGUI(KC_R),
        KC_TRNS, KC_TRNS,        KC_TRNS,        KC_F,          LGUI(KC_W)
    ),
    [3] = LAYOUT(
        KC_TRNS, KC_TRNS,        KC_TRNS,        KC_TRNS,       KC_TRNS,
        KC_TRNS, KC_LEFT,        KC_RGHT,        KC_PGUP,       MO(4),
        KC_TRNS, LSFT(KC_COMM),  LSFT(KC_DOT),   KC_PGDN,       0x0315,
        KC_TRNS, KC_TRNS,        KC_TRNS,        KC_F,          LCTL(KC_W)
    ),
    [4] = LAYOUT(
        KC_TRNS, KC_TRNS,        KC_TRNS,        KC_TRNS,       KC_TRNS,
        KC_TRNS, KC_TRNS,        KC_TRNS,        KC_TRNS,       KC_TRNS,
        KC_TRNS, KC_TRNS,        KC_TRNS,        KC_TRNS,       KC_TRNS,
        KC_TRNS, KC_TRNS,        QK_BOOT,        KC_TRNS,       KC_TRNS
    ),
    [5] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_END,  KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_WH_U, KC_WH_D), ENCODER_CCW_CW(LGUI(KC_EQL), LGUI(KC_MINS)), ENCODER_CCW_CW(KC_VOLU, KC_VOLD) },
    [1] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(LCTL(KC_EQL), LCTL(KC_MINS)), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [2] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [3] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [4] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [5] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
};
#endif

#include "qmk_analog_stick.h"

void keyboard_post_init_user(void) {
    analog_stick_init();

#ifdef OS_DETECTION_ENABLE
    //wait_ms(100);
    switch (detected_host_os()) {
        case OS_WINDOWS:
        case OS_LINUX:
            layer_move(_WIN);
            break;
        case OS_MACOS:
        case OS_IOS:
        default:
            layer_move(_MAC);
            break;
    }
#endif
}

// スクロール蓄積を8ms（125Hz）ごとに更新する
// カーソル移動はこの制限を受けない
#define SCROLL_INTERVAL_MS 8
// 正規化傾き量（-1000〜+1000）をスクロール量に変換する除数
// 大きくすると遅く、小さくすると速くなる
#define SCROLL_SPEED_DIV 6000
// スクロール速度の上限（1〜1000）: 全倒しでもこの値以上の速度にならない
// 小さくするほどスクロールの最高速が下がる
#define SCROLL_MAX_SPEED 600

static int32_t  scroll_accum_h = 0;
static int32_t  scroll_accum_v = 0;
static uint16_t scroll_timer   = 0;

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (IS_LAYER_ON(_ADJUST2)) {
        // スクロールモード: 加速なしの正規化傾き量を使用
        // 蓄積は8msごと、スムージングは毎サイクル更新
        int16_t stick_x, stick_y;
        analog_stick_get_scroll_values(&stick_x, &stick_y);

        if (stick_x >  SCROLL_MAX_SPEED) stick_x =  SCROLL_MAX_SPEED;
        if (stick_x < -SCROLL_MAX_SPEED) stick_x = -SCROLL_MAX_SPEED;
        if (stick_y >  SCROLL_MAX_SPEED) stick_y =  SCROLL_MAX_SPEED;
        if (stick_y < -SCROLL_MAX_SPEED) stick_y = -SCROLL_MAX_SPEED;

        if (timer_elapsed(scroll_timer) >= SCROLL_INTERVAL_MS) {
            scroll_timer = timer_read();
            scroll_accum_h += stick_x;
            scroll_accum_v += stick_y;
        }

        mouse_report.x = 0;
        mouse_report.y = 0;
        mouse_report.h = (int8_t)(scroll_accum_h / SCROLL_SPEED_DIV);
        mouse_report.v = (int8_t)(scroll_accum_v / SCROLL_SPEED_DIV);
        scroll_accum_h %= SCROLL_SPEED_DIV;
        scroll_accum_v %= SCROLL_SPEED_DIV;
    } else {
        // カーソルモード: 加速カーブあり（レート制限なし）
        mouse_report = analog_stick_update(mouse_report);
        scroll_accum_h = 0;
        scroll_accum_v = 0;
        scroll_timer   = timer_read();
    }

    return mouse_report;
}


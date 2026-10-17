// Copyright 2026 Hajime Oh-yake (@Hajime Oh-yake)
// SPDX-License-Identifier: GPL-2.0-or-later
//
// Slim QMK Settings for the ATmega32u4.
//
// Vial's full QMK Settings (quantum/qmk_settings.c) costs about 5.4 KB of flash because it
// drags in Auto Shift, Chordal Hold and every per-key tapping hook. That does not fit next to
// RGB Matrix + HostOS on this MCU, so this file is a drop-in replacement that keeps the same
// Vial protocol (query / get / set / reset) but exposes only these tap-hold settings:
//
//   qsid  7  "Tapping term"              default: TAPPING_TERM (200 ms)
//   qsid 20  "Tapping toggle"            default: TAPPING_TOGGLE (5)     (QS_SLIM_TAPPING_TOGGLE)
//   qsid 22  "Permissive hold"           default: OFF                    (PERMISSIVE_HOLD_PER_KEY)
//   qsid 23  "Hold on other key press"   default: ON
//
// Everything is hard-wired (no settings table, no function pointers): a PROGMEM table version
// measured about 290 bytes more. Retro tapping is deliberately not offered; its action.c code
// alone costs about 230 bytes. Measured cost of this file plus the per-key hooks: about 880 bytes.
//
// Wiring (keymap rules.mk):
//   QMK_SETTINGS = no                                   <- keeps build_vial.mk's version out
//   OPT_DEFS += -DQMK_SETTINGS -DHOLD_ON_OTHER_KEY_PRESS_PER_KEY -DPERMISSIVE_HOLD_PER_KEY
//               -DQS_SLIM_TAPPING_TOGGLE
//   SRC += qmk_settings_slim.c
//
// Nothing in Vial's core sources is modified. The other QS fields are kept at their compile-time
// defaults so that the modules reading them (grave escape, one-shot keys, mouse keys, tap delays)
// behave exactly as without QMK Settings.

#include "qmk_settings.h"

#include <stddef.h>
#include <string.h>

#include "dynamic_keymap.h"
#include "mousekey.h"

#ifndef COMBO_TERM
#    define COMBO_TERM 50
#endif
#ifndef TAPPING_TOGGLE
#    define TAPPING_TOGGLE 5
#endif

qmk_settings_t QS;

// Vial QMK Settings ids (see the protos[] table in quantum/qmk_settings.c)
#define QSID_TAPPING_TERM            7
#define QSID_TAPPING_TOGGLE          20
#define QSID_PERMISSIVE_HOLD         22
#define QSID_HOLD_ON_OTHER_KEY_PRESS 23

static void eeprom_settings_load(void) {
    for (uint8_t i = 0; i < sizeof(qmk_settings_t); ++i)
        ((uint8_t*)&QS)[i] = dynamic_keymap_get_qmk_settings(i);
}

// Write `size` bytes of QS starting at `offset` to EEPROM. eeprom_update_byte() underneath
// already skips unchanged bytes, so there is no compare loop here.
static void store(uint8_t offset, uint8_t size) {
    while (size--)
        dynamic_keymap_set_qmk_settings(offset + size, ((uint8_t*)&QS)[offset + size]);
}

void qmk_settings_init(void) {
    eeprom_settings_load();
}

// Called from dynamic_keymap_reset() (EEPROM reset) and the Vial "reset settings" command.
void qmk_settings_reset(void) {
    memset(&QS, 0, sizeof(QS));
    QS.osk_tap_toggle = ONESHOT_TAP_TOGGLE;
    QS.osk_timeout = ONESHOT_TIMEOUT;
#if defined(MOUSEKEY_ENABLE) && !defined(MK_3_SPEED)
    QS.mousekey_delay = MOUSEKEY_DELAY;
    QS.mousekey_interval = MOUSEKEY_INTERVAL;
    QS.mousekey_move_delta = MOUSEKEY_MOVE_DELTA;
    QS.mousekey_max_speed = MOUSEKEY_MAX_SPEED;
    QS.mousekey_time_to_max = MOUSEKEY_TIME_TO_MAX;
    QS.mousekey_wheel_delay = MOUSEKEY_WHEEL_DELAY;
    QS.mousekey_wheel_interval = MOUSEKEY_WHEEL_INTERVAL;
    QS.mousekey_wheel_max_speed = MOUSEKEY_WHEEL_MAX_SPEED;
    QS.mousekey_wheel_time_to_max = MOUSEKEY_WHEEL_TIME_TO_MAX;
#endif
    QS.combo_term = COMBO_TERM;
    QS.tapping_term = TAPPING_TERM;
    QS.quick_tap_term = TAPPING_TERM;
    QS.tap_code_delay = TAP_CODE_DELAY;
    QS.tap_hold_caps_delay = TAP_HOLD_CAPS_DELAY;
    QS.tapping_toggle = TAPPING_TOGGLE;
    // Default: Hold on other key press = ON, Permissive hold = OFF
    QS.tapping_v2 = (1 << QS_tapping_hold_on_other_key_press_bit);
    store(0, sizeof(qmk_settings_t));
}

// GUI: "which qsids above qsid_gt do you support?" 0xFFFF terminates the list.
void qmk_settings_query(uint16_t qsid_gt, void *buffer, size_t sz) {
    static const uint8_t ids[] = {
        QSID_TAPPING_TERM,
#ifdef QS_SLIM_TAPPING_TOGGLE
        QSID_TAPPING_TOGGLE,
#endif
#ifdef PERMISSIVE_HOLD_PER_KEY
        QSID_PERMISSIVE_HOLD,
#endif
        QSID_HOLD_ON_OTHER_KEY_PRESS,
    };
    size_t offset = 0;
    memset(buffer, 0xFF, sz);
    for (uint8_t i = 0; i < sizeof(ids) && offset + sizeof(uint16_t) <= sz; ++i) {
        uint16_t qsid = ids[i];
        if (qsid > qsid_gt) {
            memcpy((char*)buffer + offset, &qsid, sizeof(qsid));
            offset += sizeof(qsid);
        }
    }
}

// qsid 22 / 23 live in the same byte (tapping_v2); 0xFF means "not a bit setting"
static uint8_t bit_of(uint16_t qsid) {
#ifdef PERMISSIVE_HOLD_PER_KEY
    if (qsid == QSID_PERMISSIVE_HOLD) return QS_tapping_permissive_hold_bit;
#endif
    if (qsid == QSID_HOLD_ON_OTHER_KEY_PRESS) return QS_tapping_hold_on_other_key_press_bit;
    return 0xFF;
}

int qmk_settings_get(uint16_t qsid, void *setting, size_t maxsz) {
    uint8_t bit = bit_of(qsid);
    if (bit != 0xFF && maxsz >= 1) {
        *(uint8_t*)setting = (QS.tapping_v2 >> bit) & 1;
        return 0;
    }
    if (qsid == QSID_TAPPING_TERM && maxsz >= 2) {
        memcpy(setting, &QS.tapping_term, 2);
        return 0;
    }
#ifdef QS_SLIM_TAPPING_TOGGLE
    if (qsid == QSID_TAPPING_TOGGLE && maxsz >= 1) {
        *(uint8_t*)setting = QS.tapping_toggle;
        return 0;
    }
#endif
    return -1;
}

int qmk_settings_set(uint16_t qsid, const void *setting, size_t maxsz) {
    uint8_t bit = bit_of(qsid);
    if (bit != 0xFF && maxsz >= 1) {
        if (*(const uint8_t*)setting & 1)
            QS.tapping_v2 |= (1 << bit);
        else
            QS.tapping_v2 &= ~(1 << bit);
        store(offsetof(qmk_settings_t, tapping_v2), 1);
        return 0;
    }
    if (qsid == QSID_TAPPING_TERM && maxsz >= 2) {
        memcpy(&QS.tapping_term, setting, 2);
        store(offsetof(qmk_settings_t, tapping_term), 2);
        return 0;
    }
#ifdef QS_SLIM_TAPPING_TOGGLE
    if (qsid == QSID_TAPPING_TOGGLE && maxsz >= 1) {
        QS.tapping_toggle = *(const uint8_t*)setting;
        store(offsetof(qmk_settings_t, tapping_toggle), 1);
        return 0;
    }
#endif
    return -1;
}

// vial.c asks for the tapping term through this when QMK_SETTINGS is defined.
uint16_t qs_get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    return QS.tapping_term;
}

// action_tapping.c per-key hooks
#ifdef PERMISSIVE_HOLD_PER_KEY
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    return QS_tapping_permissive_hold;
}
#endif

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    return QS_tapping_hold_on_other_key_press;
}

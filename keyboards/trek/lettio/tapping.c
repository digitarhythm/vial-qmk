// Copyright 2026 Hajime Oh-yake (@Hajime Oh-yake)
// SPDX-License-Identifier: GPL-2.0-or-later
//
// タッピング（モッドタップ／レイヤータップ）の挙動調整。

#include "quantum.h"

#ifdef CHORDAL_HOLD

/* CHORDAL_HOLD は builddefs/build_vial.mk が QMK Settings 有効時に無条件で定義する。
 * 既定の手の割り当ては keyboard.json のキー座標から自動生成されるが、
 * Lettio では 48 キー中 46 キーが 'L'（左手）と判定されてしまう。
 *
 * その状態だと get_chordal_hold_default()（quantum/action_tapping.c:756）が
 * 「同じ手のキー同士」と判断して常に false を返し、
 * quantum/action_tapping.c:424 でモッドタップの Hold が却下される。
 * この判定は HOLD_ON_OTHER_KEY_PRESS より先に効くため、
 * Vial の QMK Settings で「Hold on other key press」を ON にしても効果が無い。
 *
 * '*'（手が不明）を返すと get_chordal_hold_default() は即 true を返すので、
 * コーダルホールドによる却下が無くなり、HOLD_ON_OTHER_KEY_PRESS が本来どおり働く。
 * 結果として Cmd+Tab などが待ち時間なしで反応する。 */
char chordal_hold_handedness(keypos_t key) {
    (void)key;
    return '*';
}

#endif

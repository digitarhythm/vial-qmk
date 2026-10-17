# TReK Symmetria

A 51-key, 3-encoder keyboard by digitarhythm (ATmega32u4 / caterina, WS2812 × 48 full per-key backlight, RGB Matrix).
Sibling of [TReK GT40Plus PARALLAX](../parallax/): same PCB layout, matrix, encoders and keymap; only the LEDs differ
(PARALLAX has no LEDs under the left/right modifier keys). The firmware is the parallax build with symmetria's LED map.

* Keyboard Maintainer: [digitarhythm](https://github.com/digitarhythm)
* Hardware Supported: TReK Symmetria PCB (Pro Micro compatible)
* Hardware Availability: https://digitalforhumanlife.blogspot.com/

Make example for this keyboard (after setting up your build environment):

    make trek/symmetria:default

Flashing example for this keyboard:

    make trek/symmetria:default:flash

## Firmware

Keymap `default` is a **Vial** firmware with **HostOS** enabled
(`include quantum/host_os/host_os.mk`, 16 entries, `HOS(0)`–`HOS(15)`).
It replaces the former 6-layer VIA keymap (OS detection + manual OS layers): the keys that differ
between macOS and Windows/Linux are HostOS keys and switch automatically with the detected OS.

| HOS | Key | macOS | Windows | Linux / unknown |
|---|---|---|---|---|
| 0 | Layer 0 left thumb | `LGUI_T(KC_BSPC)` | `LCTL_T(KC_BSPC)` | `LCTL_T(KC_BSPC)` |
| 1 | Layer 0 right thumb | `RGUI_T(KC_ENT)` | `RCTL_T(KC_ENT)` | `RCTL_T(KC_ENT)` |
| 2 | Layer 0 right thumb | `RCTL_T(KC_LNG1)` | `RGUI_T(KC_LNG1)` | `RGUI_T(KC_LNG1)` |
| 3 | Layer 1, `G` | – | `LGUI(KC_G)` | – |
| 4 | Layer 1, `V` | – | `LGUI(KC_V)` | – |
| 5 | Layer 1, `N` | `LGUI(KC_LBRC)` | `KC_WBAK` | `KC_WBAK` |
| 6 | Layer 1, `M` | `LGUI(KC_RBRC)` | `KC_WFWD` | `KC_WFWD` |
| 7 | Layer 0 left outer thumb | – | – | – (empty; assign per OS in Vial) |
| 8–15 | (spare) | | | |

Layers: 0 base, 1 raise (`LT(1, KC_SPC)`), 2 adjust (`MO(2)`). The ATmega32u4 has 1 KB of EEPROM;
with 3 layers there is room for 32 tap dance slots (`VIAL_TAP_DANCE_ENTRIES 32`): the last 16 are
HostOS keys and 16 stay ordinary tap dances, the same split as the RP2040 boards. Combos: 4 slots.
Macro storage: 211 bytes.

Vial unlock combo: hold `ESC` + `TAB`.

### Flash budget

The ATmega32u4 has 28,672 bytes of flash and the old VIA firmware already used 99% of it, so the
Vial build drops the following (keymap `rules.mk`):

| Disabled | Why |
|---|---|
| Vial's full QMK Settings tab (Auto Shift, Chordal Hold, per-key tapping hooks) | about 5.4 KB. Replaced by `qmk_settings_slim.c` (about 880 bytes): the tab shows only **Tapping term**, **Tapping toggle**, **Permissive hold** (default OFF) and **Hold on other key press** (default ON) |
| Key Overrides, Caps Word, Layer Lock, Repeat Key | about 3 KB together; Combos (4 entries), tap dance and HostOS stay enabled |
| RGB Matrix effects: everything except the 4 listed below | the full set of 45 costs about 7.2 KB (about 120 bytes each) |

Remaining RGB Matrix effects (keymap `config.h`):

- static: GRADIENT_UP_DOWN (plus the always-present SOLID_COLOR)
- animated: BREATHING
- key-reactive: SOLID_SPLASH, SPLASH

The key-reactive effects are dark while idle and light only the keys being pressed (fading out),
so when cycling with `RGB_MOD` they look "off" until you type.

Result: see `docs/vial-hostos-spec.md` (the 6 extra LEDs cost a few bytes more than parallax).

* [trek_symmetria_default.hex](trek_symmetria_default.hex) — keymap `default`

Flashing resets the EEPROM, so reload your `.vil` afterwards. The HostOS tab needs a
HostOS-aware Vial GUI; see `quantum/host_os/docs/host-os-guide.md`.

## Bootloader

Double-tap the reset switch (caterina), or use `QK_BOOT` from the keymap.

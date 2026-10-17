#!/usr/bin/env python3
"""Acceptance tests for the SYMMETRIA Vial/HostOS port (same build as trek/parallax, LEDs differ) (docs/vial-hostos-spec.md, section 8).

Usage (from the vial-qmk root):
    python3 keyboards/trek/symmetria/tests/test_vial_hostos.py            # static tests only
    SYMMETRIA_BUILD=1 python3 keyboards/trek/symmetria/tests/test_vial_hostos.py   # + T7/T8 build tests
"""
import json
import os
import re
import subprocess
import unittest
from pathlib import Path

KB_DIR = Path(__file__).resolve().parents[1]
QMK_ROOT = KB_DIR.parents[2]
KM_DIR = KB_DIR / "keymaps" / "default"

FLASH_LIMIT = 28672  # atmega32u4 with caterina (4KB bootloader)

# The 51 matrix positions of the original VIA info.json (now keyboard.json)
EXPECTED_KEYS = (
    {(r, c) for r in (0, 1, 2, 4, 5, 6) for c in range(7)}
    | {(3, c) for c in (0, 2, 3, 4, 6)}
    | {(7, c) for c in (2, 3, 4, 6)}
)

# Spec section 5.1: slot -> {field: keycode}; a missing field must be absent (empty)
EXPECTED_HOS = {
    0: {"kc_macos": "LGUI_T(KC_BSPC)", "kc_windows": "LCTL_T(KC_BSPC)", "kc_linux": "LCTL_T(KC_BSPC)", "kc_default": "LCTL_T(KC_BSPC)"},
    1: {"kc_macos": "RGUI_T(KC_ENT)", "kc_windows": "RCTL_T(KC_ENT)", "kc_linux": "RCTL_T(KC_ENT)", "kc_default": "RCTL_T(KC_ENT)"},
    2: {"kc_macos": "RCTL_T(KC_LNG1)", "kc_windows": "RGUI_T(KC_LNG1)", "kc_linux": "RGUI_T(KC_LNG1)", "kc_default": "RGUI_T(KC_LNG1)"},
    3: {"kc_windows": "LGUI(KC_G)"},
    4: {"kc_windows": "LGUI(KC_V)"},
    5: {"kc_macos": "LGUI(KC_LBRC)", "kc_windows": "KC_WBAK", "kc_linux": "KC_WBAK", "kc_default": "KC_WBAK"},
    6: {"kc_macos": "LGUI(KC_RBRC)", "kc_windows": "KC_WFWD", "kc_linux": "KC_WFWD", "kc_default": "KC_WFWD"},
}


def read(path):
    return path.read_text(encoding="utf-8")


def strip_c_comments(src):
    src = re.sub(r"/\*.*?\*/", "", src, flags=re.S)
    return re.sub(r"//[^\n]*", "", src)


def kle_labels(keymap):
    """Yield the first-line label of every key in a KLE keymap."""
    for row in keymap:
        for item in row:
            if isinstance(item, str):
                yield item


def balanced(src, start):
    """Return the text between the '(' at src[start] and its matching ')'."""
    depth = 0
    for i in range(start, len(src)):
        if src[i] == "(":
            depth += 1
        elif src[i] == ")":
            depth -= 1
            if depth == 0:
                return src[start + 1:i]
    raise ValueError("unbalanced parentheses")


def hex_data_bytes(path):
    """Number of data bytes in an Intel HEX file (= flash usage)."""
    total = 0
    for line in read(path).splitlines():
        if line.startswith(":") and line[7:9] == "00":
            total += int(line[1:3], 16)
    return total


class StaticTests(unittest.TestCase):
    def test_t1_keyboard_json_hardware(self):
        # The keyboard definition is keyboard.json; a leftover info.json would be merged by QMK.
        self.assertFalse((KB_DIR / "info.json").exists(), "info.json must be renamed to keyboard.json")
        kb = json.loads(read(KB_DIR / "keyboard.json"))
        self.assertEqual(kb["processor"], "atmega32u4")
        self.assertEqual(kb["bootloader"], "caterina")
        self.assertEqual(kb["usb"]["vid"].lower(), "0x1209")
        self.assertEqual(kb["usb"]["pid"].lower(), "0x516b")
        self.assertEqual(kb["matrix_pins"]["rows"], ["D1", "D0", "D4", "C6"])
        self.assertEqual(kb["matrix_pins"]["cols"], ["F4", "F5", "F6", "F7", "B1", "B3", "B2"])
        self.assertEqual(kb["ws2812"]["pin"], "D3")
        enc = [(e["pin_a"], e["pin_b"]) for e in kb["encoder"]["rotary"]]
        self.assertEqual(enc, [("D7", "E6"), ("B4", "B5"), ("D2", "B6")])

    def test_t2_keyboard_json_layout(self):
        kb = json.loads(read(KB_DIR / "keyboard.json"))
        layouts = list(kb["layouts"].values())
        self.assertEqual(len(layouts), 1)
        keys = [tuple(k["matrix"]) for k in layouts[0]["layout"]]
        self.assertEqual(len(keys), len(set(keys)), "duplicate matrix positions")
        self.assertEqual(set(keys), EXPECTED_KEYS)

    def test_t3_vial_json(self):
        vj = json.loads(read(KM_DIR / "vial.json"))
        self.assertEqual(vj["hostOS"], {"count": 16})
        self.assertEqual(vj["matrix"], {"rows": 8, "cols": 7})
        keys, encoders = set(), set()
        for label in kle_labels(vj["layouts"]["keymap"]):
            parts = label.split("\n")
            a, b = (int(x) for x in parts[0].split(","))
            if len(parts) > 9 and parts[9] == "e":
                encoders.add((a, b))
            else:
                keys.add((a, b))
        self.assertEqual(keys, EXPECTED_KEYS)
        self.assertEqual(encoders, {(e, d) for e in range(3) for d in range(2)})

    def test_t4_keymap_rules(self):
        rules = read(KM_DIR / "rules.mk")
        self.assertRegex(rules, r"(?m)^VIAL_ENABLE\s*=\s*yes")
        self.assertRegex(rules, r"(?m)^VIA_ENABLE\s*=\s*yes")
        self.assertRegex(rules, r"(?m)^include quantum/host_os/host_os\.mk")

    def test_t5_keymap_hostos(self):
        src = strip_c_comments(read(KM_DIR / "keymap.c"))
        self.assertIn('#include "host_os.h"', src)
        for n in range(7):
            self.assertRegex(src, rf"\bHOS\({n}\)", f"HOS({n}) is not placed in the keymap")
        self.assertIn("host_os_actions[HOST_OS_COUNT]", src)
        # Spec section 4: 3 layers; the former fixed-macOS override layer (TG(1)) is gone
        self.assertNotRegex(src, r"\bTG\(\d+\)")
        self.assertNotIn("_LOWER", src)
        layers = re.findall(r"^\s*\[(_\w+)\]\s*=\s*LAYOUT\(", src, flags=re.M)
        self.assertEqual(layers, ["_BASE", "_RAISE", "_ADJUST"])
        self.assertRegex(src, r"\bLT\(1,\s*KC_SPC\)")
        self.assertRegex(src, r"\bMO\(2\)")
        for n, fields in EXPECTED_HOS.items():
            m = re.search(rf"\[{n}\]\s*=\s*HOST_OS\(", src)
            self.assertIsNotNone(m, f"no default for HOS({n})")
            body = re.sub(r"\s+", "", balanced(src, m.end() - 1))
            got = {}
            for part in re.finditer(r"\.(kc_\w+)=", body):
                rest = body[part.end():]
                depth, end = 0, len(rest)
                for i, ch in enumerate(rest):
                    depth += ch == "("
                    depth -= ch == ")"
                    if ch == "," and depth == 0:
                        end = i
                        break
                got[part.group(1)] = rest[:end]
            self.assertEqual(got, fields, f"HOS({n}) defaults differ from the spec")

    def test_t6_vial_config(self):
        cfg = strip_c_comments(read(KM_DIR / "config.h"))
        self.assertRegex(cfg, r"#define VIAL_KEYBOARD_UID \{0x37, 0xD3, 0x35, 0xC7, 0x90, 0xF0, 0xC9, 0xD1\}")
        # the UID must differ from parallax so Vial keeps the two keyboards' layouts apart
        self.assertNotIn("0x8A, 0x09, 0x6D, 0xC7", cfg)
        self.assertRegex(cfg, r"#define VIAL_UNLOCK_COMBO_ROWS \{\s*0,\s*1\s*\}")
        self.assertRegex(cfg, r"#define VIAL_UNLOCK_COMBO_COLS \{\s*0,\s*0\s*\}")
        self.assertRegex(cfg, r"#define RGB_MATRIX_LED_COUNT 48\b")
        # Spec section 4/6: 32 tap dance slots (16 HostOS + 16 ordinary) need the 3-layer EEPROM layout
        self.assertRegex(cfg, r"#define VIAL_TAP_DANCE_ENTRIES 32\b")
        kbcfg = strip_c_comments(read(KB_DIR / "config.h"))
        self.assertRegex(kbcfg, r"#define DYNAMIC_KEYMAP_LAYER_COUNT 3\b")
        # Spec section 7.1: the RGB Matrix effects that fit (SOLID_COLOR is always built in)
        effects = re.findall(r"#define ENABLE_RGB_MATRIX_(\w+)", cfg)
        self.assertEqual(sorted(effects), ["BREATHING", "GRADIENT_UP_DOWN", "SOLID_SPLASH", "SPLASH"])

    def test_t10_led_map(self):
        """Spec section 2: 48 per-key LEDs; every LED index 0..47 appears exactly once in the key->LED map."""
        src = strip_c_comments(read(KM_DIR / "keymap.c"))
        m = re.search(r"g_led_config\s*=\s*\{\{(.*?\})\s*\}\s*,\s*\{", src, flags=re.S)
        self.assertIsNotNone(m, "g_led_config missing")
        rows = re.findall(r"\{([^{}]*)\}", m.group(1))
        self.assertEqual(len(rows), 8)
        leds = []
        for row in rows:
            cells = [c.strip() for c in row.split(",")]
            self.assertEqual(len(cells), 7)
            leds += [int(c) for c in cells if c != "NO_LED"]
        self.assertEqual(sorted(leds), list(range(48)))
        unlit = {(r, c) for r, row in enumerate(rows) for c, cell in enumerate(row.split(",")) if cell.strip() == "NO_LED"}
        self.assertEqual(unlit & EXPECTED_KEYS, {(3, 0), (3, 6), (7, 6)}, "only the outer thumb keys have no LED")

    def test_t9_slim_qmk_settings(self):
        """Spec section 9: a keymap-local QMK Settings exposing only the tap-hold settings
        7 Tapping term, 20 Tapping toggle, 22 Permissive hold, 23 Hold on other key press (default ON).
        Auto Shift / Chordal Hold / Retro tapping (the expensive parts) stay out."""
        rules = read(KM_DIR / "rules.mk")
        # Vial's full QMK Settings (Auto Shift etc., about 5.4 KB) must stay off ...
        self.assertRegex(rules, r"(?m)^QMK_SETTINGS\s*=\s*no")
        # ... and the slim replacement is wired in from the keymap directory
        m = re.search(r"(?m)^OPT_DEFS\s*\+=(.*)$", rules)
        self.assertIsNotNone(m, "OPT_DEFS line missing")
        for d in ("-DQMK_SETTINGS", "-DHOLD_ON_OTHER_KEY_PRESS_PER_KEY", "-DPERMISSIVE_HOLD_PER_KEY", "-DQS_SLIM_TAPPING_TOGGLE"):
            self.assertIn(d, m.group(1), f"{d} missing from OPT_DEFS")
        self.assertNotIn("RETRO_TAPPING", m.group(1), "retro tapping costs about 230 bytes and is not offered")
        self.assertRegex(rules, r"(?m)^SRC\s*\+=.*\bqmk_settings_slim\.c\b")
        self.assertNotRegex(rules, r"AUTO_SHIFT_ENABLE\s*=\s*yes")

        src = strip_c_comments(read(KM_DIR / "qmk_settings_slim.c"))
        qsids = re.findall(r"#define QSID_\w+\s+(\d+)", src)
        self.assertEqual(qsids, ["7", "20", "22", "23"], "exposed settings differ from spec section 9")
        self.assertNotIn("protos", src, "no PROGMEM settings table: hard-wired code measured about 290 bytes smaller")
        self.assertNotIn("PROGMEM", src)
        # default after an EEPROM reset: only Hold on other key press is set
        m = re.search(r"QS\.tapping_v2\s*=\s*([^;]+);", src)
        self.assertIsNotNone(m, "qmk_settings_reset() must initialise tapping_v2")
        self.assertIn("QS_tapping_hold_on_other_key_press_bit", m.group(1))
        self.assertNotIn("permissive", m.group(1))
        self.assertRegex(src, r"QS\.tapping_term\s*=\s*TAPPING_TERM")
        self.assertRegex(src, r"QS\.tapping_toggle\s*=\s*TAPPING_TOGGLE")
        # the hooks Vial core and action_tapping.c link against
        for fn in ("qmk_settings_init", "qmk_settings_reset", "qmk_settings_query", "qmk_settings_get",
                   "qmk_settings_set", "qs_get_tapping_term", "get_hold_on_other_key_press", "get_permissive_hold"):
            self.assertRegex(src, rf"\b{fn}\s*\(", f"{fn}() missing")


@unittest.skipUnless(os.environ.get("SYMMETRIA_BUILD") == "1", "set SYMMETRIA_BUILD=1 to run build tests")
class BuildTests(unittest.TestCase):
    HEX = QMK_ROOT / "trek_symmetria_default.hex"

    @classmethod
    def setUpClass(cls):
        cls.result = subprocess.run(
            ["qmk", "compile", "-kb", "trek/symmetria", "-km", "default"],
            cwd=QMK_ROOT, capture_output=True, text=True,
        )

    def test_t7_build_succeeds(self):
        self.assertEqual(self.result.returncode, 0, self.result.stdout[-3000:] + self.result.stderr[-3000:])

    def test_t8_flash_size(self):
        self.assertEqual(self.result.returncode, 0, "build failed")
        size = hex_data_bytes(self.HEX)
        print(f"\nflash: {size} / {FLASH_LIMIT} bytes ({FLASH_LIMIT - size} free)")
        self.assertLessEqual(size, FLASH_LIMIT)


if __name__ == "__main__":
    unittest.main(verbosity=2)

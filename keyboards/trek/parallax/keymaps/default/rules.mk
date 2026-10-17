VIA_ENABLE = yes
VIAL_ENABLE = yes
RGBLIGHT_ENABLE = no
RGB_MATRIX_ENABLE = yes
LTO_ENABLE = yes
SPACE_CADET_ENABLE = no

# HostOS: the last N tap dance slots act as HostOS keys; N comes from "hostOS" in vial.json
# (see quantum/host_os/docs/host-os-guide.md)
include quantum/host_os/host_os.mk

# ATmega32u4 flash budget: these Vial extras do not fit next to RGB Matrix + HostOS
# (the five together cost about 3 KB). Combos stay on (about 2.1 KB, 4 entries).
# QMK_SETTINGS = no keeps Vial's full version (about 5.4 KB) out; qmk_settings_slim.c below
# provides a four-setting replacement: Tapping term, Tapping toggle, Permissive hold (default OFF)
# and Hold on other key press (default ON). About 990 bytes; retro tapping would add 230 more.
QMK_SETTINGS = no
OPT_DEFS += -DQMK_SETTINGS -DHOLD_ON_OTHER_KEY_PRESS_PER_KEY -DPERMISSIVE_HOLD_PER_KEY -DQS_SLIM_TAPPING_TOGGLE
SRC += qmk_settings_slim.c
KEY_OVERRIDE_ENABLE = no
CAPS_WORD_ENABLE = no
LAYER_LOCK_ENABLE = no
REPEAT_KEY_ENABLE = no

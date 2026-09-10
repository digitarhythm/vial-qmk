VIA_ENABLE = yes
VIAL_ENABLE = yes
RGBLIGHT_ENABLE = no
RGB_MATRIX_ENABLE = yes
GRAVE_ESC_ENABLE = yes
SPACE_CADET_ENABLE = no

# HostOS: the last N tap dance slots act as HostOS keys; N comes from "hostOS" in vial.json
# (see quantum/host_os/docs/host-os-guide.md)
include quantum/host_os/host_os.mk

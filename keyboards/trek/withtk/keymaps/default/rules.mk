VIA_ENABLE = yes
VIAL_ENABLE = yes
ENCODER_MAP_ENABLE = yes
RGBLIGHT_ENABLE = no
RGB_MATRIX_ENABLE = yes

# HostOS: the last N tap dance slots act as HostOS keys; N comes from "hostOS" in vial.json
# (see quantum/host_os/docs/host-os-guide.md)
include quantum/host_os/host_os.mk

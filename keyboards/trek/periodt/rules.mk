ENCODER_MAP_ENABLE = yes
MAGIC_ENABLE = no
BOOTMAGIC_ENABLE = yes
OS_DETECTION_ENABLE = yes
KEY_OVERRIDE_ENABLE = yes

AUDIO_ENABLE = no

CUSTOM_MATRIX = lite
DEBOUNCE_TYPE = sym_eager_pk

SRC += matrix.c

# OS Dance (dedicated EEPROM region; quantum/os_dance/docs/os-dance-guide.md)
OS_DANCE_ENABLE = yes

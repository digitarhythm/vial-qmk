# Joystick Test

*A short description of the keyboard/project*

* Keyboard Maintainer: [digitarhythm](https://github.com/digitarhythm)
* Hardware Supported: *The PCBs, controllers supported*
* Hardware Availability: *Links to where you can find this hardware*

Make example for this keyboard (after setting up your build environment):

    make trek/joystick_test:default

Flashing example for this keyboard:

    make trek/joystick_test:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Firmware

Prebuilt Vial firmware with **HostOS** enabled (`include quantum/host_os/host_os.mk`, 16 entries, `HOS(0)`–`HOS(15)`):

* [trek_joystick_test_default.uf2](trek_joystick_test_default.uf2) — keymap `default`

To flash: enter the bootloader (see below), then copy the `.uf2` onto the `RPI-RP2` drive.
Connect the keyboard **directly** to the computer's USB port — copying through a hub often fails with error -36 on macOS.
Flashing resets the EEPROM, so reload your `.vil` afterwards. The HostOS tab needs an HostOS-aware Vial GUI;
see `quantum/host_os/docs/host-os-guide.md`.

## Bootloader

Press the "RESET" button while holding down the "BOOT" button on the RP2040-Zero.


# thinkpad-sysfs-stuff

## Install

```
make install
```

Note: installs to /usr/local/bin by default, and chown's to root and setuid's
the binaries to be able to use sysfs with unprivilaged users

### ledctl

```
usage: ledctl <brightness path>
```

### brightnessctl

Supports intel\_backlight (default: /sys/class/backlight/intel_backlight/)

```
usage: brightnessctl <[0-100]|(+|-)[0-100]>
```

## Tested working

### ThinkPad P53

LEDs:

```
input0::capslock -> ../../devices/platform/i8042/serio0/input/input0/input0::capslock
input0::numlock -> ../../devices/platform/i8042/serio0/input/input0/input0::numlock
input0::scrolllock -> ../../devices/platform/i8042/serio0/input/input0/input0::scrolllock
phy0-led -> ../../devices/pci0000:00/0000:00:1c.5/0000:52:00.0/leds/phy0-led
platform::micmute -> ../../devices/platform/thinkpad_acpi/leds/platform::micmute
platform::mute -> ../../devices/platform/thinkpad_acpi/leds/platform::mute
tpacpi::kbd_backlight -> ../../devices/platform/thinkpad_acpi/leds/tpacpi::kbd_backlight
tpacpi::lid_logo_dot -> ../../devices/platform/thinkpad_acpi/leds/tpacpi::lid_logo_dot
tpacpi::power -> ../../devices/platform/thinkpad_acpi/leds/tpacpi::power
tpacpi::standby -> ../../devices/platform/thinkpad_acpi/leds/tpacpi::standby
tpacpi::thinkvantage -> ../../devices/platform/thinkpad_acpi/leds/tpacpi::thinkvantage
```

Backlight:

```
/sys/class/backlight/intel_backlight/brightness
```


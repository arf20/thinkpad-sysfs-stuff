# thinkpad-sysfs-stuff

## Install

```
make install
```

Note: installs to /usr/local/bin by default, and chown's to root and setuid's
the binaries to be able to use sysfs with unprivilaged users

### ledctl

Sets keyboard LEDs

```
usage: %s <led name> [(default)toggle|on|off]
```

led name as in /sys/class/leds

### brightnessctl

Sets LCD backlight intensity

Supports intel\_backlight (default: /sys/class/backlight/intel_backlight/)

```
usage: brightnessctl <[0-100]|(+|-)[0-100]>
```

### fanctl

Sets fan speed

Via /proc/acpi/ibm/fan interface

```
usage: fanctl [0-7|auto|full-speed]
```

### ledkeyer

Keys LED with morse code

```
usage: %s [-s <wpm>] [-l] <led name> <message>
```

### thinkhotkeys

Script for hotkey actions and calling \*ctl programs

 - Volume
 - Mute/Mic Mute
 - Brightness

```
usage: thinkhotkeys <syncleds|volinc|voldec|volmutetog|micmutetog|brightinc|brightdec|faninc|fandec>
```

Included an example config for sxhkd (sxhkdrc)

## Tested working

### ThinkPad P53

#### LEDs:

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

Caps/NumLock LEDs work by default, as keyboard backlight (with Fn+Space)

scrolllock, phy0-led, power, standby and thinkvantage don't have real LEDs

#### Backlight:

```
/sys/class/backlight/intel_backlight/brightness
```

#### Fans:

```
/proc/acpi/ibm/fan
```


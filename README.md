# backlight_control
Control the backlight brightness.

I had some problems with `xbacklight` in combination with the proprietary nvidia driver, so I wrote a replacement.

## Build
```sh
make
```

## Install
```sh
sudo make install
```

## Uninstall
```sh
sudo make uninstall
```

## Usage
```sh
$ backlight_control
Usage: backlight_control [+|-]<value>

Examples:
        backlight_control +10
        backlight_control -10
        backlight_control 50

```

`backlight_control +n` increases brightness by n%

`backlight_control -n` decreases brightness by n%

`backlight_control n` sets the brightness to n%

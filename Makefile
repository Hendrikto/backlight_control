CC = gcc
CFLAGS += -Wall -Wextra -O3 -march=native

prefix = /usr/local
backlight_dir = /sys/class/backlight/intel_backlight/
max_brightness = $(shell cat $(backlight_dir)max_brightness)

DEFINES += -D BACKLIGHT_DIR=\"$(backlight_dir)\"
DEFINES += -D MAX_BRIGHTNESS=$(max_brightness)

all: backlight_control

%: %.c
	$(CC) $(CFLAGS) $(DEFINES) $< -o $@

clean:
	rm -f backlight_control

install: backlight_control
	install -D -m 4755 -o root -g root $< $(DESTDIR)$(prefix)/bin/$<

uninstall:
	rm -f $(DESTDIR)$(prefix)/bin/backlight_control

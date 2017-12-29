CC = gcc
CFLAGS += -Wall -Wextra -O3 -march=native

prefix = /usr/local
backlight_dir = /sys/class/backlight/intel_backlight/
max_brightness = $(shell cat $(backlight_dir)max_brightness)
backlight_rule = ALL ALL=NOPASSWD: $(prefix)/bin/backlight_control

DEFINES += -D BACKLIGHT_DIR=\"$(backlight_dir)\"
DEFINES += -D MAX_BRIGHTNESS=$(max_brightness)

all: backlight_control

%: %.c
	$(CC) $(CFLAGS) $(DEFINES) $< -o $@

clean:
	rm -f backlight_control

install: backlight_control
	mv $< $(DESTDIR)$(prefix)/bin
	tee $(DESTDIR)/etc/sudoers.d/backlight <<< "$(backlight_rule)"

uninstall:
	rm -f $(DESTDIR)$(prefix)/bin/backlight_control
	rm -f $(DESTDIR)/etc/sudoers.d/backlight

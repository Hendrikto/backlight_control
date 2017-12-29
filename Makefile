CC = gcc
CFLAGS += -Wall -Wextra -O3 -march=native

prefix = /usr/local
backlight_dir = /sys/class/backlight/intel_backlight/
max_brightness = $(shell cat $(backlight_dir)max_brightness)
backlight_rule = $(USER) ALL=NOPASSWD: $(prefix)/bin/backlight_control

DEFINES += -D BACKLIGHT_DIR=\"$(backlight_dir)\"
DEFINES += -D MAX_BRIGHTNESS=$(max_brightness)

all: backlight_control

%: %.c
	$(CC) $(CFLAGS) $(DEFINES) $< -o $@

clean:
	rm -f backlight_control

install: backlight_control
	sudo mv $< $(DESTDIR)$(prefix)/bin
	echo $(backlight_rule) | sudo tee $(DESTDIR)/etc/sudoers.d/backlight

uninstall:
	sudo rm -f $(DESTDIR)$(prefix)/bin/backlight_control
	sudo rm -f $(DESTDIR)/etc/sudoers.d/backlight

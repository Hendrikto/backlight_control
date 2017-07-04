backlight_dir = "/sys/class/backlight/intel_backlight/"
max_brightness = $(shell cat $(backlight_dir)max_brightness)
backlight_rule = $(USER) ALL=NOPASSWD: /usr/local/bin/backlight_control

all: backlight_control

backlight_control: backlight_control.c
	gcc -Wall -Wextra -O3 backlight_control.c -o backlight_control\
		-D BACKLIGHT_DIR=$(backlight_dir)\
		-D MAX_BRIGHTNESS=$(max_brightness)

deploy: backlight_control
	echo $(backlight_rule) | sudo tee /etc/sudoers.d/backlight
	sudo mv backlight_control /usr/local/bin/

clean:
	rm -f backlight_control
	sudo rm /etc/sudoers.d/backlight

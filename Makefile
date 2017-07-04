backlight_dir = "/sys/class/backlight/intel_backlight/"
max_brightness = $(shell cat $(backlight_dir)max_brightness)

all: backlight_control

backlight_control: backlight_control.c
	gcc -Wall -Wextra -O3 backlight_control.c -o backlight_control\
		-D BACKLIGHT_DIR=$(backlight_dir)\
		-D MAX_BRIGHTNESS=$(max_brightness)

clean:
	rm ./backlight_control

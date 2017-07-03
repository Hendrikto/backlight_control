all: backlight_control

backlight_control: backlight_control.c
	gcc -Wall -Wextra -O3 backlight_control.c -o backlight_control

clean:
	rm ./backlight_control

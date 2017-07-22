#include <sys/param.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * A program to control the backlight brightness.
 *
 * @author: Hendrik Werner
 */

#define MIN_BRIGHTNESS 1

void print_usage(char *name) {
	printf(
		"Usage: %1$s [+|-]<value>\n"
		"\n"
		"Examples:\n"
		"\t%1$s +10\n"
		"\t%1$s -10\n"
		"\t%1$s 50\n",
		name
	);
}

int main(int argc, char **argv) {
	if (argc != 2) {
		print_usage(argv[0]);
		return EXIT_FAILURE;
	}
	int value = strtol(argv[1], NULL, 10);
	FILE *brightness = fopen(BACKLIGHT_DIR "brightness", "r+");
	int brightness_value = 0;
	fscanf(brightness, "%d", &brightness_value);
	switch (argv[1][0]) {
		case '+':
		case '-':
			brightness_value += MAX_BRIGHTNESS * value / 100;
			break;
		default:
			brightness_value = MAX_BRIGHTNESS * value / 100;
	}
	brightness_value = MIN(brightness_value, MAX_BRIGHTNESS);
	brightness_value = MAX(brightness_value, MIN_BRIGHTNESS);
	fprintf(brightness, "%d", brightness_value);
	fclose(brightness);
	return EXIT_SUCCESS;
}

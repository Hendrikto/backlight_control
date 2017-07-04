#include <sys/param.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * A program to control the backlight brightness.
 *
 * @author: Hendrik Werner
 */

#define MIN_BRIGHTNESS 1

void print_usage(char *name) {
	printf("Usage: %s <mode> <value>\n", name);
	printf("\t mode: change | set\n");
}

int main(int argc, char **argv) {
	if (argc != 3) {
		print_usage(argv[0]);
		return EXIT_FAILURE;
	}
	int value = strtol(argv[2], NULL, 10);
	FILE *brightness = fopen("/sys/class/backlight/intel_backlight/brightness", "r+");
	int brightness_value = 0;
	fscanf(brightness, "%d", &brightness_value);
	if (!strcmp(argv[1], "change")) {
		brightness_value += MAX_BRIGHTNESS * value / 100;
	} else if (!strcmp(argv[1], "set")) {
		brightness_value = MAX_BRIGHTNESS * value / 100;
	} else {
		print_usage(argv[0]);
		fclose(brightness);
		return EXIT_FAILURE;
	}
	brightness_value = MIN(brightness_value, MAX_BRIGHTNESS);
	brightness_value = MAX(brightness_value, MIN_BRIGHTNESS);
	fprintf(brightness, "%d", brightness_value);
	fclose(brightness);
	return EXIT_SUCCESS;
}

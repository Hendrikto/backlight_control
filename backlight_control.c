#include <stdio.h>
#include <stdlib.h>

/**
 * A program to control the backlight brightness.
 *
 * @author: Hendrik Werner
 */

#define MIN_BRIGHTNESS 1

#define MAX(a, b) ((a > b) ? a : b)
#define MIN(a, b) ((a < b) ? a : b)

void usage(char *name) {
	printf(
		"Usage: %1$s [+|-]<value>\n\n"
		"Examples:\n"
		"\t%1$s +10\n"
		"\t%1$s -10\n"
		"\t%1$s 50\n",
		name
	);
}

int main(int argc, char **argv) {
	if (argc != 2) {
		usage(argv[0]);

		return EXIT_FAILURE;
	}

	char *endptr;

	long int value = strtol(argv[1], &endptr, 10);

	if (endptr == argv[1]) {
		fputs("brightness value must be an integer\n", stderr);

		return EXIT_FAILURE;
	}

	if (!((value < 0 ? value *= -1 : value) >= 1 && value <= 100)) {
		fputs("brightness value must be between 1 and 100 (inclusively)\n", stderr);

		return EXIT_FAILURE;
	}

	FILE *fp;

	if (!(fp = fopen(BRIGHTNESS_FILE, "r+"))) {
		fprintf(stderr, "failed to open %s\n", BRIGHTNESS_FILE);

		return (EXIT_FAILURE);
	}

	float brightness_value;

	fscanf(fp, "%e", &brightness_value);

	switch (argv[1][0]) {
		case '+':
			brightness_value += MAX_BRIGHTNESS * ((float)value / 100.0);

			break;
		case '-':
			brightness_value -= MAX_BRIGHTNESS * ((float)value / 100.0);

			break;
		default:
			brightness_value = MAX_BRIGHTNESS * ((float)value / 100.0);
	}

	brightness_value = MIN(brightness_value, MAX_BRIGHTNESS);
	brightness_value = MAX(brightness_value, MIN_BRIGHTNESS);

	fprintf(fp, "%.0f", brightness_value);
	fclose(fp);

	return EXIT_SUCCESS;
}

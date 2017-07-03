#include <stdio.h>
#include <stdlib.h>

/**
 * A program to control the backlight brightness.
 *
 * @author: Hendrik Werner
 */

void print_usage(char *name) {
	printf("Usage: %s <mode> <value>\n", name);
	printf("\t mode: inc | dec\n");
}

int main(int argc, char **argv) {
	if (argc != 3) {
		print_usage(argv[0]);
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

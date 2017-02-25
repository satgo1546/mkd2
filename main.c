/* main.c */

/* library */
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

/* definition */
#include "error.c"
#include "read_config.c"
#include "invoke.c"

/* main */
int main(int argc, char* argv[]) {
	read_config();
	for (int i = 1; i < argc; i++) {
		invoke(argv[i]);
	}
	return EXIT_SUCCESS;
}

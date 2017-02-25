/* main.c */

/* library */
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

/* platform */
#ifdef _MSC_VER
	#define bool int
	#define true 1
	#define false 0
#else
	#include <stdbool.h>
#endif
#ifdef _WIN32
	#include "win32.c"
#else
	#include <unistd.h>
	#include "posix.c"
#endif

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

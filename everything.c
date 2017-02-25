/* everything.c */

/* library */
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#ifdef _MSC_VER
	#define bool int
	#define true 1
	#define false 0
#else
	#include <stdbool.h>
#endif

/* utilities */
#include "fncheck.c"

/* platform */
#ifdef _WIN32
	#include "win32.c"
#else
	#include "posix.c"
#endif

/* definition */
#include "error.c"
#include "read_config.c"
#include "invoke.c"

/* main */
#include "main.c"

/* error.c */

/* Usage:
	error("sqrt()", "calculating square root of %f", x);
	error(NULL, "unknown error made by me");
*/
void error(const char* function, const char* format, ...) {
	va_list ap;
	va_start(ap, format);
	set_color(15, 1);
	fputs(" Error ", stdout);
	reset_color();
	fputs("\nMessage: ", stdout);
	vprintf(format, ap);
	putchar('\n');
	if (function && *function) perror(function);
	va_end(ap);
	exit(EXIT_FAILURE);
}

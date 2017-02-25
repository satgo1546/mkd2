/* error.c */

/* Usage:
	error("sqrt()", "calculating square root of %f", x);
	error(NULL, "unknown error made by me");
*/
void error(const char* function, const char* format, ...) {
	va_list ap;
	va_start(ap, format);
	fprintf(stderr, "= Error =\nMessage: ");
	vfprintf(stderr, format, ap);
	fputc('\n', stderr);
	if (function && *function) perror(function);
	va_end(ap);
	exit(EXIT_FAILURE);
}

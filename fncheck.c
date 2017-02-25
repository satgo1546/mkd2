/* fncheck.c */

/* Usage:
	assert(fncheck(".") == false);
	assert(fncheck("..") == false);
	assert(fncheck("anything_else") == true);
*/
bool fncheck(const char* name) {
	// We'd like it to explode rather than stuck.
	if (!name) return true;
	if (name[0] == '.') {
		if (name[1] == '.' && name[2] == 0 || name[1] == 0) {
			return false;
		}
	}
	return true;
}

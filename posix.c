/* posix.c */
#include <unistd.h>
#include <libgen.h>
#include <dirent.h>
#include <fnmatch.h>

typedef struct {
	DIR* dir;
	char glob_base[FILENAME_MAX];
} type_dir;

void platform_init() {
}

type_dir* dir_open(const char* glob) {
	char* glob_dir = strdup(glob);
	char* glob_base_ = strdup(glob);
	char* glob_base = basename(glob_base_);
	type_dir* dir = malloc(sizeof(type_dir));
	dir->dir = opendir(dirname(glob_dir));
	strncpy(dir->glob_base, glob_base, FILENAME_MAX);
	free(glob_dir);
	free(glob_base_);
	return dir;
}

const char* dir_entry(type_dir* dir) {
	struct dirent* dp = readdir(dir->dir);
	if (!dp) return NULL;
	{
		const char* name = dp->d_name;
		if (
			!fncheck(name) || fnmatch(
				dir->glob_base, name, FNM_NOESCAPE | FNM_PATHNAME
			) == FNM_NOMATCH
		) {
			return dir_entry(dir);
		}
		return name;
	}
}

void dir_close(type_dir* dir) {
	closedir(dir->dir);
	free(dir);
}

void set_color(int fg, int bg) {
	char sequence[13] = "\e[0;";
	char* p = sequence + 4;
	if (fg > 0 && fg & 8) {
		*p++ = '1';
		*p++ = ';';
	}
	if (fg > 0) {
		*p++ = '3';
		*p++ = '0' + (fg & 7);
		*p++ = ';';
	}
	if (bg > 0) {
		*p++ = '4';
		*p++ = '0' + (bg & 7);
		*p++ = ';';
	}
	*p-- = 0;
	*p = 'm';
	fputs(sequence, stdout);
}

void reset_color() {
	printf("\e[0m");
}

/* posix.c */
#include <unistd.h>
#include <libgen.h>
#include <dirent.h>
#include <fnmatch.h>

typedef struct {
	DIR* dir;
	char glob_base[FILENAME_MAX];
} type_dir;

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

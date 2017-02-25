/* win32.c */
#include <windows.h>

typedef struct {
	WIN32_FIND_DATA ffd;
	bool first;
	HANDLE handle;
} type_dir;

type_dir* dir_open(const char* glob) {
	type_dir* dir = malloc(sizeof(type_dir));
	dir->first = true;
	dir->handle = FindFirstFileA(glob, &dir->ffd);
	return dir;
}

const char* dir_entry(type_dir* dir) {
	if (dir->first) {
		if (dir->handle == INVALID_HANDLE_VALUE) {
			return NULL;
		} else {
			dir->first = false;
		}
	} else if (!FindNextFile(dir->handle, &dir->ffd)) {
		return NULL;
	}
	dir->first = false;
	// ignore . and ..
	const char* name = dir->ffd.cFileName;
	if (name[0] == '.') {
		if (name[1] == '.' && name[2] == 0 || name[1] == 0) {
			return dir_entry(dir);
		}
	}
	return name;
}

void dir_close(type_dir* dir) {
	FindClose(dir->handle);
	free(dir);
}

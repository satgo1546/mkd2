/* win32.c */
#include <windows.h>

typedef struct {
	WIN32_FIND_DATA ffd;
	bool first;
	HANDLE handle;
} type_dir;

HANDLE handle_stdout;
WORD old_text_attributes;

void platform_init() {
	handle_stdout = GetStdHandle(STD_OUTPUT_HANDLE);
	{
		CONSOLE_SCREEN_BUFFER_INFO info;
		GetConsoleScreenBufferInfo(handle_stdout, &info);
		old_text_attributes = info.wAttributes;
	}
}

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
	{
		const char* name = dir->ffd.cFileName;
		if (!fncheck(name)) return dir_entry(dir);
		return name;
	}
}

void dir_close(type_dir* dir) {
	FindClose(dir->handle);
	free(dir);
}

int windows_console_color(int color) {
	return color = color & 10 | (color & 1) << 2 | (color & 4) >> 2;
}

void set_color(int fg, int bg) {
	if (fg < 0) {
		fg = old_text_attributes & 0xf;
	} else {
		fg = windows_console_color(fg);
	}
	if (bg < 0) {
		bg = old_text_attributes & 0xf0;
	} else {
		bg = windows_console_color(bg);
	}
	SetConsoleTextAttribute(handle_stdout, bg << 4 | fg);
}

void reset_color() {
	SetConsoleTextAttribute(handle_stdout, old_text_attributes);
}

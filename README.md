mkd2
====

**[WIP]**

Yet another build automation utility.

System requirements
-------------------

Win32 or POSIX.

Installation
------------

1. Compile libanib.
2. Copy anib.h here.
3. Compile everything.c. Any of the following works, where “▤” should be replaced with the path of libanib.

	```shell
	gcc everything.c -o mkd2 -L▤ -lanib
	clang everything.c -o mkd2 -L▤ -lanib
	cl everything.c /Femkd2.exe /link ▤\libanib.lib
	```

4. Move mkd2(.exe) to somewhere in your $PATH (%PATH%).

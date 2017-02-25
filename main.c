/* main.c */
int main(int argc, char* argv[]) {
	int i;
	type_dir* dir = dir_open("./*");
	const char* n;
	while ((n = dir_entry(dir))) puts(n);
	read_config();
	for (i = 1; i < argc; i++) {
		invoke(argv[i]);
	}
	return EXIT_SUCCESS;
}

/* read_config.c */
void read_config() {
	FILE* f = fopen("a.mkd2", "r");
	if (!f) error("fopen()", "error in reading a.mkd2");
	fclose(f);
}

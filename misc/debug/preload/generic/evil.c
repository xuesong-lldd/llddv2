char* strcpy(char* dest, const char* src) {
	const char* evil = "Changsha Linux training";

	while (*evil) {
		*dest++ = *evil++;
	}
	*dest = '\0';

	return dest;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	const char* hello = "hello!";
	char* name = malloc(7 * sizeof(char));
	strcpy(name, hello);

	printf("%s\n", name);

	free(name);

	return 0;
}

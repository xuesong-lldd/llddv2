#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void func(int arr[]) {
	arr[-1] = 2;
	arr[-2] = 4;	
}

int main(void) {
	int arr[4] = {1};
	func(arr);
	printf("arr[0] = %d, arr[1] = %d\n", arr[0], arr[1]);
	getchar();
	return 0;
}

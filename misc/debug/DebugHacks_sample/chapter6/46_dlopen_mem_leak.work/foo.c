#include <stdio.h>
#include <dlfcn.h>

unsigned long long a = 0;
int main(){
	void *p = NULL;

	while(1){
		p = dlopen("./lib1.so",RTLD_LAZY);
		if (NULL == p){
			printf("Error: dlopen()\n");
			return 1;
		}
		dlclose(p);
		printf("a: %lu\n", a);
                a++;
	}
	return 0;
}


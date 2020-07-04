#include <stdio.h>
#include <dlfcn.h>

int main(){
	void *p = NULL;

	while(1){
		p = dlopen("./lib1.so",RTLD_LAZY);
		if (NULL == p){
			printf("Error: dlopen()\n");
			return 1;
		}
		dlclose(p);
		usleep(100);
	}
	return 0;
}


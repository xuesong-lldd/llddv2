int a, b, c;
void foo()
{ 
	a = b + 1;
	//asm volatile("":::"memory");
	//asm volatile("mfence":::"memory");
 	b = 0;
}


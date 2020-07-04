//g++ gcov-demo.cpp -fprofile-arcs -ftest-coverage -o gcov-demo

#define MAX 10000
void f()
{
	long long sum = 0;
	for (long long i=0;i<MAX;i++)
		sum += i;
}

long long g()
{
	long long sum = 0;
	for (long long i=0;i<MAX;i++)
		sum += i;
	f();

	return sum;
}

void h()
{
	long long sum = 0;
	for (long long i=0;i<MAX;i++)
		sum += i;
}

int main()
{
	long long sum = 0;
	for (long long i=0;i<MAX;i++)
		sum += i;
	f();
	g();
	if (sum < 5000)
		h();
}

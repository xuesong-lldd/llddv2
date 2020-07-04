#include <cstdio>

class foo {
    int a;
    int b;
public:
    void func(int x, int y);
};

void foo::func(int x, int y)
{
    a = x;
    b = y + 2;
}

int main(void)
{
    foo f1, f2;
    printf("f1: %p, f2: %p\n", &f1, &f2);
    f1.func(5, 1);
    f2.func(-4, 2);

    return 0;
}

#include "func_pointer.h"
#include <stdio.h>

int add(int a, int b)
{
    return a + b;
}

int mul(int a, int b)
{
    return a * b;
}

int sub(int a,int b)
{
    return b - a;
}
int (*pADD)(int, int);

typedef int (*FUNC_ADD)(int, int);

void test_func_pointer()
{
    printf("Hello!\n");

    pADD = add;
    int r = add(100, 200);
    int r1 = (*pADD)(100, 200);

    FUNC_ADD myOP = sub;
    int r2 = myOP(100, 200);

    printf("r = %d, r1 = %d, r2 = %d\n", r, r1, r2);

    return;
}
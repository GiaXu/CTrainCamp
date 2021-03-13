#include <stdio.h>

int fun14(int n, int k)
{
    int a = 0;
    int b = 1;

    while (n != 0)
    {
        a = a + n % k * b;
        n = n / k;
        b = b * 10;
    }

    return a;
}
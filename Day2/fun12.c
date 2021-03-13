#include <stdio.h>

float fun11_power(float m, int n);

unsigned fun12(unsigned w)
{
    if (w <= 10)
    {
        return w;
    }

    int n = 0;
    int i = 0;
    int s = w;

    while (w >= 1)
    {
        n++;
        i = w;
        w = w / 10;
    }

    w = s - (i * fun11_power(10, n - 1));

    return w;
}
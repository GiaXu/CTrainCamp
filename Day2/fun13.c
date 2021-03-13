#include <stdio.h>

float fun11_power(float m, int n);

long fun13(long s)
{
    int n = 0;
    long t = 0;
    long t1 = 0;
    while (s >= 10)
    {
        s = s / 10;
        t1 = s % 10;
        s = s / 10;
        t = t + t1 * fun11_power(10, n);
        n++;
    }
    return t;
}
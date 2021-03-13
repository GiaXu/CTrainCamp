#include <stdio.h>
#include <math.h>

float fun05(float num)
{
    int s = 1;
    float n = 1.0;
    float t = 1.0;
    float pi = 0;

    while (fabsf(t) >= num)
    {
        pi = pi + t;
        n = n + 2.0;
        s = -s;
        t = s / n;
    }

    pi = pi * 4;

    return pi;
}
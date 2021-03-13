#include <stdio.h>

float fun17(float eps) 
{
    float e = 1;
    int n = 1;
    int i = 1;

    for (n = 1; n < eps; ++n)
    {
        for (i = 1; i <= n; ++i)
        {
            i *= i;
        }

        e += 1 / i;
    }

    return e;
}
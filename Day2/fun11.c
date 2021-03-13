#include <stdio.h>

float fun11_power(float m, int n)
{
    if (0 == n)
    {
        return 1;
    }
    int i = 1;

    for (i = 1; i < n; ++i)
    {
        m *= m;
    }

    return m;
}

float fun11(float x, int m)
{
    if (m > 6)
    {
        return x;
    }
    else
    {
        x *= fun11_power(10, m);

        if (x - (int)(x) >= 0.5)
        {
            x++;
        }
        else
        {
            x = (int)(x);
        }
        x = (int)x / fun11_power(10, m);
        return x;
    }
}


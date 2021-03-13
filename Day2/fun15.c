#include <stdio.h>

void fun15(int k)
{
    if (k >= 9 || k % 2 == 0)
    {
        return;
    }

    double s = 1;
    double d = 0;

    while (k > 0)
    {
        d = k;
        s = 1;

        while (d > 1)
        {
            s = s * d;
            --d;
        }
        printf("%lf\t", s);
        k -= 2;
    }
}
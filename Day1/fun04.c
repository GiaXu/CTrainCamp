#include <stdio.h>

int fun04(int a, int b)
{
    if (a >= b)
    {
        int c = a % b;

        while (c != 0)
        {
            a = b;
            b = c;
            c = a % b;
        }
        return b;
    } //if
    else
    {
        int d = b % a;

        while (d != 0)
        {
            b = a;
            a = d;
            d = b % a;
        }
        return a;
    }
}

int fun04_2(int a, int b)
{
    int c = fun04(a, b);
    int d = (a * b) / c;

    return d;
}

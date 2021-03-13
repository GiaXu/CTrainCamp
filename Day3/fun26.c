#include <stdio.h>

void fun26(char *p)
{
    char max;
    int i = 0;
    int q;
    max = p[0];

    while (p[i])
    {
        if (max < p[i])
        {
            max = p[i];
            q = i;
        }
        ++i;
    }

    while (q)
    {
        p[q] = p[q - 1];
        --q;
    }
    p[0] = max;
}
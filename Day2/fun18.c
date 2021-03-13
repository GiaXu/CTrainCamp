#include <stdio.h>

int fun18(int m)
{
    int i, j;
    int k = 0;
    for (i = 3; i <= m; ++i)
    {
        for (j = 2; j < i; ++j)
        {
            if (i % j == 0)
            {
                break;
            }
            if (j == i - 1)
            {
                ++k;
            }
        }
    }
    return k;
}

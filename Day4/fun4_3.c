#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

void fun4_3(char *a)
{
    int i, j, n;
    char ch;
    n = strlen(a);
    for (i = 1; i < n; ++i)
    {
        ch = a[i];
        j = i - 1;
        while ((j >= 0) && (ch < a[j]))
        {
            a[j + 1] = a[j];
            --j;
        }
        a[j + 1] = ch;
    }
}
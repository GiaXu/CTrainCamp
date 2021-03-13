#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fun27(char *a, char *b, char *c)
{
    int i, j, n;
    int k = 0;
    int p;
    char t;
    j = strlen(b) - 1;
    for (i = 0; i < j; ++i)
    {
        t = b[i];
        b[i] = b[j];
        b[j] = t;
        --j;
    }
    j = 0;
    p = 0;
    n = strlen(a) + strlen(b);
    for (i = 0; i <= n; ++i)
    {
        if (0 == i % 2)
        {
            if ('\0' != a[j])
            {
                c[k] = a[j];
                ++k;
                ++j;
            }

            if ('\0' == a[j])
            {
                c[k] = b[p];
                ++k;
                ++p;
            }
        } //if

        if (1 == i % 2)
        {
            if ('\0' != b[p])
            {
                c[k] = b[p];
                ++k;
                ++p;
            }

            if ('\0' == b[p])
            {
                c[k] = a[j];
                ++j;
                ++k;
            }
        } //if
    }
}

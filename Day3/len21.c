#include <stdio.h>

int len21(char *s)
{
    int i = 0;
    int n = 0;
    while ('\0' != s[i])
    {
        ++n;
        ++i;
    }
    return n;
}
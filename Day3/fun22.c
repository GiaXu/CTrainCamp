#include <stdio.h>

int fun22(char *s, char k)
{
    int i = 0;
    int n = 0;

    while ('\0' != s[i])
    {
        if (s[i] == k)
        {
            ++n;
            ++i;
        }
        else
        {
            ++i;
        }
    }

    return n;
}
#include <stdio.h>

void fun24(char *s)
{
    char *p;
    while (*s)
    {
        if (*s == ' ')
        {
            p = s;
            while (*p)
            {
                *p = *(p + 1);
                ++p;
            }
        }
        else
        {
            ++s;
        }
    }
}
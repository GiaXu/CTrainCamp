#include <stdio.h>

int fun4_4(char *a, char *b)
{
    char *p;
    int n = 0;
    while (*a)
    {
        p = b;
        if (*a == *p)
        {
            while (*a == *p)
            {
                ++a;
                ++p;
                if ('\0' == *p)
                {
                    ++n;
                }
            }
        }
        else
        {
            ++a;
        }
    }
    return n;
}
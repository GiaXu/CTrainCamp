#include <stdio.h>

void fun25(char *a, char *b)
{
    int i;
    while (*a)
    {
        for (i = 0; i < 3; ++i)
        {
            *b = *a;
            if ('\0' == *a)
            {
                break;
            }
            ++a;
            ++b;
        }
        while ('\0' != *a)
        {
            *b = ' ';
            ++b;
            break;
        }
    }
}
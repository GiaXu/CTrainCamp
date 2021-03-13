#include <stdio.h>

int *fun4_6(char *st, int a[3])
{
    while (*st)
    {

        if ('a' == *st)
        {
            ++a[0];
        }
        if ('b' == *st)
        {
            ++a[1];
        }
        if ('c' == *st)
        {
            ++a[2];
        }
        ++st;
    }
    return a;
}
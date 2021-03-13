#include <stdio.h>

void fun6_2(int n)
{
    if(0 == n / 10)
    {
        putchar('0' + n % 10);
    }
    else 
    {
        fun6_2(n / 10);
        putchar('0' + n % 10);
    }
    
}
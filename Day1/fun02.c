#include <stdio.h>

int fun02(int num)
{
    if (num < 0)
    {
        printf("Wrong!\n");
        return -1;
    }
    if (num == 0)
    {
        return 0;
    }
    else
    {
        int c = 1;
        while (num > 0)
        {
            c = c * (num % 10);
            num = num / 10;
        }
        
        return c;
    }
}
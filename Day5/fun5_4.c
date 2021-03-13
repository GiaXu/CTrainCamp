#include <stdio.h>

int fun5_4(int lim,int aa[100])
{
    int i,MAX = 0,j;
    for(i = 0;i <= lim;++i)
    {
        for(j = 2;j < i;++j)
        {
            if(i % j == 0)
            {
                break;
            }
            if(i == j + 1)
            {
                aa[MAX] = i;
                MAX ++;
            }
        }
    }
    return MAX;
}

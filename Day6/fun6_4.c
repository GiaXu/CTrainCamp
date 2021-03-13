#include <stdio.h>

#define N 10

 
 typedef struct stu
    {
        int num;
        int score;
    }stu;


int fun6_4(struct stu* s,struct stu* h)
{
    stu min;
    min = s[0];
    int i,c = 0;
    for(i = 0;i < N;++i)
    {
        if(min.score > s[i].score)
        {
            min = s[i];
        }
    }
    for(i = 0;i < N;++i)
    {
        if(s[i].score == min.score)
        {
            *(h + c) = s[i];
            ++c;
        }
    }
    return c;
}
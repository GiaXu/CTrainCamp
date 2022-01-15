#include <stdio.h>

int main()
{
    printf("Please input your name:\n");
    char szName[16] = {0};
    scanf("%s", szName);
    printf("Hello, %s \n", szName);
    return 0;
}
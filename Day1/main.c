#include <stdio.h>

extern double fun01(double x, double y);

int fun02(int num);

void fun03(int *a, int *b);

int fun04(int a, int b);

int fun04_2(int a, int b);

float fun05(float num);


int main()
{  
    //Day1-1
    double x,y;

    printf("(Day1-1) Please input x,y:\n");
    scanf("%lf,%lf",&x,&y);

    double a ;
    a = fun01(x,y);
    
    printf("result is %lf\n",a);


     
    //Day1-2
    int num = 0;
    printf("(Day1-2)Please input a number:\n");
    scanf("%d",&num);
    int c = fun02(num);

    printf("result is %d\n",c);
   


    //Day1-3
    int d = 5;
    int f = 3;
    printf("(Day1-3)d = %d,f = %d\n",d,f);

    fun03(&d,&f);
    printf("\n");

    printf("now,d = %d,f = %d\n",d,f);



    //Day1-4
    int g = 0;
    int h = 0;

    printf("(Day1-4)Please input g,h:\n");
    scanf("%d,%d",&g,&h);

    int j = fun04(g,h);
    printf("j is %d\n",j);

    int k = fun04_2(g,h);
    printf("k is %d\n",k);
    


    //Day1-5
    printf("(Day1-5)Please input num0:\n");

    float num0;
    scanf("%f", &num0);

    float pi = fun05(num0);
    printf("pi is %f\n",pi);
    

    return 0;
}
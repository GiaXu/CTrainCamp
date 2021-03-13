#include <stdio.h>

float fun11(float x, int m);

float fun11_power(float m, int n);

unsigned fun12(unsigned w);

long fun13(long s);

int fun14(int n, int k);

void fun15(int k);

float fun17(float eps);

int fun18(int m);

int main()
{
    //Day2-1
    float x;
    int m = 0;

    printf("(Day2-1)Please input x:\n");
    scanf("%f", &x);
    printf("Please input m:\n");
    scanf("%d", &m);

    float re = fun11(x, m);

    printf("Now result is %f\n", re);



    //Day2-2
    unsigned w;

    printf("(Day2-2)Please input w:\n");
    scanf("%d", &w);

    unsigned a = fun12(w);

    printf("number is %d\n", a);




    //Day2-3
    long s;

    printf("(Day2-3)Please input s:\n");
    scanf("%ld", &s);

    long t = fun13(s);

    printf("t is %ld\n", t);




    //Day2-4
    int n = 0;
    int k = 0;

    printf("(Day2-4)Please input number:\n");
    scanf("%d", &n);

    printf("Please input k:\n");
    scanf("%d", &k);

    int b = fun14(n, k);
    printf("number is %d\n", b);




    //Day2-5
    int c = 0;
    printf("(Day2-5)Please input number:\n");
    scanf("%d", &c);

    fun15(c);




    //Day2-6
    int h = 0;
    int d = 0;

    printf("(Day2-6)Please input h:\n");
    scanf("%d", &h);

    printf("Please input n:\n");
    scanf("%d", &d);

    int i, j, e;
    int f = 0;
    for (i = 0; i < d; ++i)
    {
        f = f + h;
        h = h * 10;
    }

    e = f;
    while (e)
    {
        e = e / 10;
        f = f - e;
    }

    printf("result is %d\n", f);




    //Day2-7
    float eps;
    printf("(Day2-7)Please input eps:\n");
    scanf("%f", &eps);

    printf("result is %f\n", fun17(eps));




    //Day2-8
    int g;
    printf("(Day2-8)Please input g :\n");
    scanf("%d", &g);
    printf("number is %d\n", fun18(g));

    return 0;
}
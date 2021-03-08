#include "SUT.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "insert_sort.h"

//Day 1
double fun01(double x, double y)
{
    double a;
    //double a = sqrt(x) + sqrt(y);

    return a;
}

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

void fun03(int *a, int *b)
{
    int c = *a;
    *a = *b;
    *b = c;

    return;
}

int fun04(int a, int b)
{
    if (a >= b)
    {
        int c = a % b;

        while (c != 0)
        {
            a = b;
            b = c;
            c = a % b;
        }
        return b;
    } //if
    else
    {
        int d = b % a;

        while (d != 0)
        {
            b = a;
            a = d;
            d = b % a;
        }
        return a;
    }
}

int fun04_2(int a, int b)
{
    int c = fun04(a, b);
    int d = (a * b) / c;

    return d;
}

float fun05(float num)
{
    int s = 1;
    float n = 1.0;
    float t = 1.0;
    float pi = 0;

    while (fabsf(t) >= num)
    {
        pi = pi + t;
        n = n + 2.0;
        s = -s;
        t = s / n;
    }

    pi = pi * 4;

    return pi;
}

//Day 2
float fun11(float x, int m)
{
    if (m > 6)
    {
        return x;
    }
    else
    {
        x *= fun11_power(10, m);

        if (x - (int)(x) >= 0.5)
        {
            x++;
        }
        else
        {
            x = (int)(x);
        }
        x = (int)x / fun11_power(10, m);
        return x;
    }
}

float fun11_power(float m, int n)
{
    if (0 == n)
    {
        return 1;
    }
    int i = 1;

    for (i = 1; i < n; ++i)
    {
        m *= m;
    }

    return m;
}

unsigned fun12(unsigned w)
{
    if (w <= 10)
    {
        return w;
    }

    int n = 0;
    int i = 0;
    int s = w;

    while (w >= 1)
    {
        n++;
        i = w;
        w = w / 10;
    }

    w = s - (i * fun11_power(10, n - 1));

    return w;
}

long fun13(long s)
{
    int n = 0;
    long t = 0;
    long t1 = 0;
    while (s >= 10)
    {
        s = s / 10;
        t1 = s % 10;
        s = s / 10;
        t = t + t1 * fun11_power(10, n);
        n++;
    }
    return t;
}

int fun14(int n, int k)
{
    int a = 0;
    int b = 1;

    while (n != 0)
    {
        a = a + n % k * b;
        n = n / k;
        b = b * 10;
    }

    return a;
}

void fun15(int k)
{
    if (k >= 9 || k % 2 == 0)
    {
        return;
    }

    double s = 1;
    double d = 0;

    while (k > 0)
    {
        d = k;
        s = 1;

        while (d > 1)
        {
            s = s * d;
            --d;
        }
        printf("%lf\t", s);
        k -= 2;
    }
}

float fun17(float eps) //w
{
    float e = 1;
    int n = 1;
    int i = 1;

    for (n = 1; n < eps; ++n)
    {
        for (i = 1; i <= n; ++i)
        {
            i *= i;
        }

        e += 1 / i;
    }

    return e;
}

int fun18(int m)
{
    int i, j;
    int k = 0;
    for (i = 3; i <= m; ++i)
    {
        for (j = 2; j < i; ++j)
        {
            if (i % j == 0)
            {
                break;
            }
            if (j == i - 1)
            {
                ++k;
            }
        }
    }
    return k;
}

//Day 3
int len21(char *s)
{
    int i = 0;
    int n = 0;
    while ('\0' != s[i])
    {
        ++n;
        ++i;
    }
    return n;
}

int fun22(char *s, char k)
{
    int i = 0;
    int n = 0;

    while ('\0' != s[i])
    {
        if (s[i] == k)
        {
            ++n;
            ++i;
        }
        else
        {
            ++i;
        }
    }

    return n;
}

void fun24(char *s)
{
    char *p;
    while (*s)
    {
        if (*s == ' ')
        {
            p = s;
            while (*p)
            {
                *p = *(p + 1);
                ++p;
            }
        }
        else
        {
            ++s;
        }
    }
}

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

void fun26(char *p)
{
    char max;
    int i = 0;
    int q;
    max = p[0];

    while (p[i])
    {
        if (max < p[i])
        {
            max = p[i];
            q = i;
        }
        ++i;
    }

    while (q)
    {
        p[q] = p[q - 1];
        --q;
    }
    p[0] = max;
}

void fun27(char *a, char *b, char *c)
{
    int i, j, n;
    int k = 0;
    int p;
    char t;
    j = strlen(b) - 1;
    for (i = 0; i < j; ++i)
    {
        t = b[i];
        b[i] = b[j];
        b[j] = t;
        --j;
    }
    j = 0;
    p = 0;
    n = strlen(a) + strlen(b);
    for (i = 0; i <= n; ++i)
    {
        if (0 == i % 2)
        {
            if ('\0' != a[j])
            {
                c[k] = a[j];
                ++k;
                ++j;
            }

            if ('\0' == a[j])
            {
                c[k] = b[p];
                ++k;
                ++p;
            }
        } //if

        if (1 == i % 2)
        {
            if ('\0' != b[p])
            {
                c[k] = b[p];
                ++k;
                ++p;
            }

            if ('\0' == b[p])
            {
                c[k] = a[j];
                ++j;
                ++k;
            }
        } //if
    }
}

//Day 4
void fun4_3(char *a)
{
    int i, j, n;
    char ch;
    n = strlen(a);
    for (i = 1; i < n; ++i)
    {
        ch = a[i];
        j = i - 1;
        while ((j >= 0) && (ch < a[j]))
        {
            a[j + 1] = a[j];
            --j;
        }
        a[j + 1] = ch;
    }
}

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

int search4_5(int *input, size_t start, size_t count, int x)
{
    if (NULL == input || count <= 0)
    {
        return -1;
    }

    size_t mid = ((start + count) + start) / 2;

    if (input[mid] == x)
    {
        return mid;
    }
    else if (input[mid] > x)
    {
        return search4_5(input, start, (mid - start), x);
    }
    else
    {
        return search4_5(input, mid + 1, (start + count - mid - 1), x);
    }
}

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
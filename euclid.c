#include <stdio.h>

struct pair {
    int f;
    struct pair2 {
        int f;
        int s;
    } s;
};

struct pair extendedEuclid(int a, int b) 
{
    int x = 1, y = 0;
    int xL = 0, yL = 1;
    int q, r, m, n;
    while (a != 0) 
    {
        q = b / a;
        r = b % a;
        m = xL - q * x;
        n = yL - q * y;
        xL = x; 
        yL = y;
        x = m; 
        y = n;
        b = a; 
        a = r;
    }
    struct pair re;
    re.f = b;
    re.s.f = xL;
    re.s.s = yL;
    return re;
}

int modInverse(int a, int m) 
{
    return (extendedEuclid(a, m).s.f + m) % m;
}

int main()
{
    int a, m;
    printf("Enter a number: ");
    scanf("%d", &a);
    printf("Enter Modular Value: ");
    scanf("%d", &m);
    printf("%d\n", modInverse(a, m));
    return 0;
}

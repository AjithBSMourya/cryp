#include <stdio.h>
#include <math.h>

long calculate(long b, long e, long m) {
    long re = 1;
    while (e > 0) {
        if (e % 2 == 1) {
            re = (ret * b) % m;
        }
        b= (b * b) % m;
        e= e / 2;
    }
    return re;
}

int main() {
    long P, G, x, a, y, b, ka, kb;
    
    printf("Public keys G and P\n");
    
    printf("Enter a value for G:");
    scanf("%ld", &G);
    printf("Enter a value for P:");
    scanf("%ld", &P);
    
    printf("Enter value for key 1:");
    scanf("%ld", &a);
    printf("Enter value for key 2:");
    scanf("%ld", &b);
    
    x = calculate(G, a, P);
    y = calculate(G, b, P);
    
    ka = calculate(y, a, P);
    
    kb = calculate(x, b, P);
    printf("Secret key 1: %d\n", ka);
    printf("Secret key 2: %d", kb);
    
    return 0;
}

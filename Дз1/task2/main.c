#include <stdio.h>
#include <stdlib.h>

int binary(int x){
    int a = 1, b;
    a = a << 31;
    for (int i = 0; i < 32; i++){
        b = x & a;
        if(a != b)
            printf("0");
        else
            printf("1");
        x = x << 1;
    }
    return 0;
}

int change(unsigned int x, unsigned int n, char side){
    int a,b;
    a = 1;
    a = a << 31;
    if(side == 'R')
        for(int i = 0; i < n; i++){
            b = x % 2;
            x = x >> 1;
            if(b != 0)
                x += a;
        }
    else
        for(int i = 0; i < n; i++){
            b = x;
            b = b >> 31;
            x = x << 1;
            if(b != 0)
                x++;
        }
    return x;
}


int main()
{
    // task1
    int x;
    printf("Input x = ");
    scanf("%d", &x);
    printf("In binary = ");
    binary(x);
    printf("\n");
    // task2
    unsigned int y, n;
    char side = 0;
    printf("Input y = ");
    scanf("%u", &y);
    printf("Input n = ");
    scanf("%u", &n);
    printf("Input R or L = ");
    getchar();
    scanf("%c", &side);
    y = change(y,n,side);
    printf("After shift y = %u", y);
    return 0;
}

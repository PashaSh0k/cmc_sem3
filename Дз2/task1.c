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

int count1(int x){
    int a = 1, b, c = 0;
    a = a << 31;
    for (int i = 0; i < 32; i++){
        b = x & a;
        if(a == b)
            c++;
        x = x << 1;
    }
    return c;
}
int sort(int *a, int n){
    int ap, at, r;
    for(int i = 0; i < (n-1); i++){
        ap = count1(a[i]);
        for(int j = (i+1); j < n; j++){
            at = count1(a[j]);
            if((at < ap) || ((at == ap) && (a[j] > a[i]))){
                r = a[i];
                a[i] = a[j];
                a[j] = r;
                ap = at;
            }
        }
    }
    return 0;
}
int main()
{
    int n;
    printf("Input dimension = ");
    scanf("%d", &n);
    int a[n];
    printf("Input array elements\n");
    for(int i = 0; i < n; i++){
        printf("a[%d] = ", i);
        scanf("%d", &a[i]);
    }
    printf("\n");
    printf("-----OUTPUT-----\n");
    for(int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
    printf("-----OUTPUT IN BINARY-----\n");
    for(int i = 0; i < n; i++){
        printf("a[%d] = ", i);
        binary(a[i]);
        printf("\n");
    }
    sort(a, n);
    printf("-----OUTPUT SORTED-----\n");
    for(int i = 0; i < n; i++)
        printf("%d ", a[i]);
    return 0;
}

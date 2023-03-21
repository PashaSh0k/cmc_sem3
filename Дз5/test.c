#include <stdio.h>
#include <stdlib.h>

#define BINPRINT(x){ \
    if (sizeof(x) == 1) \
        ToBinary((long long)(char)x, 8*sizeof(x)); \
    else if (sizeof(x) == 2) \
        ToBinary((long long)(short)x, 8*sizeof(x)); \
    else if (sizeof(x) == 4) \
        ToBinary((long long)(int)x, 8*sizeof(x)); \
    else if (sizeof(x) == 8) \
        ToBinary((long long)(long)x, 8*sizeof(x)); \
    else \
        ToBinary((long long)x, 8*sizeof(x)); \
    printf("\n"); \
}

int ToBinary(long long x, int size){
    long long mask = 1;
    mask = mask << (size - 1);
    for (int i = 0; i < size; i++){
        printf("%u", (x&mask) == mask);
        x = x << 1;
    }
    return 0;
}

int main(){
    printf("Main test:\n");
    char y = -3;
    if (y){
        BINPRINT(y);
    }
    else printf("Zero!\n");
    BINPRINT((short)7);
    long x=15;
    if(x){
        BINPRINT(x);
    }
    else printf("Zero!\n");
    BINPRINT((long long)x);

    printf("Other tests:\n");
    char a = -2;
    printf("char -2:        ");
    BINPRINT(a);
    short b = -2;
    printf("short -2:       ");
    BINPRINT(b);
    int c = -2;
    printf("int -2:         ");
    BINPRINT(c);
    long d = -2;
    printf("long -2:        ");
    BINPRINT(d);
    long long e = -2;
    printf("long long -2:   ");
    BINPRINT(e);
    char aa = 3;
    printf("char 3:         ");
    BINPRINT(aa);
    short bb = 3;
    printf("short 3:        ");
    BINPRINT(bb);
    int cc = 3;
    printf("int 3:          ");
    BINPRINT(cc);
    long dd = 3;
    printf("long 3:         ");
    BINPRINT(dd);
    long long ee = 3;
    printf("long long 3:    ");
    BINPRINT(ee);
    long long eee = 1099511627776;
    printf("long long 2^40: ");
    BINPRINT(eee);
    long ddd = 8589934592;
    printf("long 2^33:      ");
    BINPRINT(ddd);
    return 0;
}
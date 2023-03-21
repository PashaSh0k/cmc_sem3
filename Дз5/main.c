#include <stdio.h>
#include <stdlib.h>

#define BINPRINT(x){ \
    if (sizeof(x) == 1) \
        binary((long long)x, 8*sizeof(x)); \
    else if (sizeof(x) == 2) \
        binary((long long)x, 8*sizeof(x)); \
    else if (sizeof(x) == 4) \
        binary((long long)x, 8*sizeof(x)); \
    else \
        binary((long long)x, 8*sizeof(x)); \
    printf("\n"); \
}
void binary(long long x, int size){
    long long a = 1, b;
    a = a << (size - 1);
    for (int i = 0; i < size; i++){
        b = x & a;
        if(a != b)
            printf("0");
        else
            printf("1");
        x = x << 1;
    }
}

int main(){
    printf("Main:\n");
    char c = -3;
    if(c){  
        BINPRINT(c);
    }
    else
        printf("Zero!\n");
    BINPRINT((short)7);
    long x=15;
    if(x){ 
        BINPRINT(x);
    }
    else
        printf("Zero!\n");
    BINPRINT((long long)x);

    printf("Some tests:\n");
    char a1 = -8;
    printf("char -8:        ");
    BINPRINT(a1);
    short b1 = -8;
    printf("short -8:       ");
    BINPRINT(b1);
    int c1 = -8;
    printf("int -8:         ");
    BINPRINT(c1);
    long d1 = -8;
    printf("long -8:        ");
    BINPRINT(d1);
    long long e1 = -8;
    printf("long long -8:   ");
    BINPRINT(e1);
    char a2 = 3;
    printf("char 3:         ");
    BINPRINT(a2);
    short b2 = 3;
    printf("short 3:        ");
    BINPRINT(b2);
    int c2 = 3;
    printf("int 3:          ");
    BINPRINT(c2);
    long d2 = 3;
    printf("long 3:         ");
    BINPRINT(d2);
    long long e2 = 3;
    printf("long long 3:    ");
    BINPRINT(e2);
    return 0;
}
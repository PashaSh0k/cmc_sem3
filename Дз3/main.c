#include <stdio.h>
#include <stdlib.h>
#define buff 4

char* fun(){
    char* a = (char*)malloc(buff * sizeof(char*));
    char c;
    int k = 0, n = buff;
    while(scanf("%c", &c) != -1){
        if (c != '\n'){
            *(a + k) = c;
            k++;
            if ((n + k) % buff == 0){
                n += buff;
                a = (char*)realloc(a, n * sizeof(char*));
            }
        }
        else{
            *(a + k) = '\0';
            break;
        }
    }
    return a;
}
int main(){
    char* str = fun();
    printf("%s", str);
    free(str);
    return 0;
}

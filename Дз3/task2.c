#include <stdio.h>
#include <stdlib.h>
#define buff 4

// test abcasdasdabcasdasdabcasdabc12abc21ab1231abb12321abcc12abcabc112abc
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
char* find(char* a, char* b){
    char* asave = a;
    char* bsave = b;
    int flag;
    while(*asave != '\0'){
        a = asave;
        b = bsave;
        flag = 0;
        while((*a == *b) || (*a == '\0') || (*b == '\0')){
            if ((*a == '\0') || (*b == '\0')){
                flag = 1;
                break;
            }
            a++;
            b++;
        }
        if (*b == '\0' && flag){ // цикл пройден по элементам подстроки
            return a;
        }
        if (*a == '\0' && flag){ // основная строка закончилась --> вывод пустого указателя (если при этом закончилась бы подстрока, то сработало бы предыдущее условие)
            return NULL;
        }
        asave++;
    }
    return NULL; // основная строка закончилась
}
int main()
{
    char* str = fun();
    char* substr = fun();
    char* c;
    c = find(str, substr);
    while (1 > 0){
        if (c == NULL){
            printf("NULL");
            break;
        }
        printf("%s\n", c);
        c = find(c, substr);
    }
    free(str);
    free(substr);
    free(c);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>

void inp(int n, int m, char** x){
    int i,j;
    printf("-----INPUT-----\n");
    char temp;
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++){
            scanf("%c", &temp);
            scanf("%c", &x[i][j]);
        }
}

void outp(int n, int m, char** x){
    int i,j;
    printf("-----OUTPUT-----\n");
    for (i = 0; i < n; i++){
        for (j = 0; j < m; j++)
            printf("%c ", x[i][j]);
        printf("\n");
    }
}

char** fun1(int n, int m, char** a, char x){
    char** newm = (char**)malloc(n*sizeof(char*));
    for(int i = 0; i < n; i++)
        newm[i] = (char*)malloc(m*sizeof(char));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            newm[i][j] = a[i][j];
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            if (a[i][j] == x){
                for(int k = 0; k < m; k++)
                    newm[i][k] = '#';
                for(int k = 0; k < n; k++)
                    newm[k][j] = '#';
            }
        }
    }
    return newm;
}
void fun2(int n, int m, char** a, char x){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            if (a[i][j] == x){
                for(int k = 0; k < j; k++)
                    if (a[i][k] != x)
                        a[i][k] = '#';
                for(int k = 0; k < i; k++)
                    if (a[k][j] != x)
                        a[k][j] = '#';
                for(int k = j + 1; k < m; k++)
                    if (a[i][k] != x)
                        a[i][k] = '#';
                for(int k = i + 1; k < n; k++)
                    if (a[k][j] != x)
                        a[k][j] = '#';
            }
        }
    }
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            if (a[i][j] == x)
                a[i][j] = '#';
        }
    }
}
int main(){
    int i, n, m;
    printf("Input dimension:\n  line: n = ");
    scanf("%d", &n);
    printf("column: m = ");
    scanf("%d", &m);
    char** a = (char**)malloc(n*sizeof(char*));
    for(i = 0; i < n; i++)
        a[i] = (char*)malloc(m*sizeof(char));
    inp(n,m,a);
    outp(n,m,a);
    printf("\n");
    printf("Enter x = ");
    char x;
    getchar();
    scanf("%c", &x);
    char** b = fun1(n,m,a,x);
    printf("___New matrix___ \n");
    outp(n,m,b);
    fun2(n,m,a,x);
    printf("----Old matrix---- \n");
    outp(n,m,a);
    for (i = 0; i < n; i++)
        free(a[i]);
    free(a);
    for (i = 0; i < n; i++)
        free(b[i]);
    free(b);
    return 0;
}

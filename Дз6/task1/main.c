#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
    FILE* file;
    char* name = argv[1];
    file = fopen(name, "r");
    int n = atoi(argv[2]);
    char** list = malloc(sizeof(char*));
    char c = fgetc(file);
    int i = 0;
    while(c != EOF){
        list[i] = malloc(sizeof(char));
        int count = 0;
        while(c != '\n'){
            list[i][count] = c;
            count++;
            list[i] = realloc(list[i], sizeof(char)*(count+1));
            c = fgetc(file);
        }
        list[i][count] = '\0';
        if(count > n){
            free(list[i]);
        }
        else{
            i++;
        }
        c = fgetc(file);
        list = realloc(list, sizeof(char*)*(i+1));
    }
    //clear and write
    fclose(file);
    file = fopen(name, "w");
    int j;
    for(j = 0; j < i; j++){
        fputs(list[j], file);
        fputc('\n', file);
    }
    //free
    fclose(file);
    for(j = 0; j < i; j++){
        free(list[j]);
    }
    free(list);
    return 0;
}
#include <stdio.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void sortstr(int* length, int* position, int count){
    int i, j;
    int tmp;
    for(i = 0; i < count-1; i++)
        for(j = i+1; j < count; j++)
            if(length[j] < length[i]){
                tmp = length[j];
                length[j] = length[i];
                length[i] = tmp;
                tmp = position[j];
                position[j] = position[i];
                position[i] = tmp;
            }
}

int main(int argc, char** argv){
    char c, a;
    int* str_length = NULL;
    int* str_position = NULL;
    int str_count = 0;
    int saved, f, number;

    FILE* file = fopen(argv[1], "r");
    if(file){
        str_length = malloc(sizeof(int));
        str_position = malloc(sizeof(int));
        c = fgetc(file);
        while(c != EOF){
            str_count++;
            str_length = realloc(str_length, sizeof(int)*str_count);
            str_position = realloc(str_position, sizeof(int)*str_count);
            saved = str_count;
            str_length[str_count-1] = 0;
            str_position[str_count-1] = 0;
            while(saved != 1){
                str_position[str_count-1] += str_length[saved-2] + 1;
                saved--;
            }
            while((c != EOF) && (c != '\n')){
                str_length[str_count-1]++;
                c = fgetc(file);
            }
            if(c != EOF)
                c = fgetc(file);
        }
        fclose(file);
        f = open(argv[1], O_RDONLY);
        printf("Enter string number: ");
        a = getchar();
        while(a != '0' && a != EOF){
            number = 0;
            while(a != '\n' && a != EOF){
                number = number*10 + a - '0';
                a = getchar();
            }
            if(number <= str_count){
                char* tmp;
                tmp = malloc(sizeof(char));
                lseek(f, str_position[number-1], SEEK_SET);
                if(str_length[number-1] == 0)
                    printf("\n");
                else{
                    tmp = realloc(tmp, sizeof(char)*(str_length[number-1]+1));
                    read(f, tmp, str_length[number-1]);
                    tmp[str_length[number-1]] = '\0';
                    printf("%s", tmp);
                    printf("\n");
                }
                free(tmp);
            }
            else
                printf("\nwrong number, enter again: ");
            a = getchar();     
        }
        if(a == '0'){
            file = fopen(argv[2], "w");
            sortstr(str_length, str_position, str_count);
            for(int i = 0; i < str_count; i++){
                lseek(f, str_position[i], SEEK_SET);
                char* tmp;
                tmp = malloc(sizeof(char));
                tmp[0] = ' ';
                if(str_length[i] == 0)
                    fputc('\n', file);
                else{
                    tmp = realloc(tmp, sizeof(char)*(str_length[i]+1));
                    read(f, tmp, str_length[i]);
                    tmp[str_length[i]] = '\0';
                    fputs(tmp, file);
                    fputc('\n', file);
                }
                free(tmp);
            }
            fclose(file);
            close(f);
        }
        free(str_length);
        free(str_position);
        return 0;
    }
    else{
        printf("file not found\n");
        return 0;
    }
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void check(int* s, int* num, int* linenum, int argc, char** argv){
    if(argc > 2){
        for(int i = 1; i < argc - 1; i++)
            if((argv[i][0] == '-') && (argv[i][1] == 's'))
                *s = 1;
            else if(argv[i][0] == '-')  
                *num = atoi(argv[i] + 1);  
            else if(argv[i][0] == '+')
                *linenum = atoi(argv[i] + 1);
    }
}

int my_more(int s, int num, int linenum, FILE* file){
    char c;
    if((num != 0) && !(feof(file))){
        if(linenum > 1){
            //skip linenum lines
            for(int i = 1; i < linenum; i++){
                fscanf(file, "%c", &c);
                while(!(feof(file)) && (c != '\n'))
                    fscanf(file, "%c", &c);
                if(feof(file))
                    return 1;
            }
        }
        if(s){
            int flag = 0; // skip empty
            for(int i = 0; i < num; i++){
                int j = 0;
                c = ' ';
                while(!(feof(file)) && (c != '\n')){
                    j++;
                    if(j > 1)
                        flag = 0;
                    fscanf(file, "%c", &c);
                    if(feof(file))
                        return 1;
                    if((j == 1) && (c == '\n')){
                        if(flag == 0){
                            printf("%c", c);
                            flag = 1;
                        }
                    }
                    else
                        printf("%c", c);
                }
            }
        }
        else{
            for(int i = 0; i < num; i++){
                c = ' ';
                while((c != '\n') && !(feof(file))){
                    fscanf(file, "%c", &c);
                    if(feof(file))
                        return 1;
                    printf("%c", c);
                }
            }
        }
    }
    return 0;
}

int main(int argc, char** argv)
{
    FILE* file = fopen(argv[argc-1], "r");
    int s = 0;
    int num = 10;
    int linenum = 1;
    check(&s, &num, &linenum, argc, argv);
    char c = ' ';
    c = getchar();
    while(c != 'q'){
        printf("==%c", c);
        if(my_more(s, num, linenum, file) == 1){
            printf("EOF\n");
            break;
        }
        c = getchar();
    }
    fclose(file);
    return 0;
}
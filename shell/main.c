#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/file.h>
#include <stdlib.h>

#define MAXWORDS 50
#define size 4

int conveyor(int from, int to, char* list[]){
    pid_t pid;
    int flag = 0;
    int count = 1;
    int pd_last[2];
    while(!flag){
        int pointer = from;
        while(pointer < to){
            if(strcmp(list[pointer], "|") == 0){
                break;
            }
            pointer++;
        }
        char* vector[pointer - from + 1];
        vector[pointer - from] = NULL;
        int i = 0;
        while(from != pointer){
            vector[i] = list[from];
            i++;
            from++;
        }
        if(from == to){
            flag = 1;
        }
        else{
            from++;
        }
        int pd_cur[2];
        if(!flag)
            pipe(pd_cur);
        if((pid = fork()) == 0){
            if(count > 1){
                dup2(pd_last[0], 0);
            }
            if(!flag){
                close(pd_cur[0]);
                dup2(pd_cur[1], 1);
            }
            execvp(vector[0], vector);
        }
        if(!flag){
            close(pd_cur[1]);
        }
        if(count > 1){
            close(pd_last[0]);
        }
        pd_last[0] = pd_cur[0];
        pd_last[1] = pd_cur[1];
        count++;
    }
    int status;
    int prev_status = 0;
    pid_t pid0;
    while((pid0 = wait(&status)) != -1){
        if(pid0 == pid)
            prev_status = WEXITSTATUS(status);
    }
    return prev_status;
}
int redirection(int pointer, char* list[]){
    if(strcmp(list[pointer], "<") == 0){
        pointer++;
        int fd = open(list[pointer], O_RDONLY);
        dup2(fd, 0);
        close(fd);
        return 1;
    }
    else if(strcmp(list[pointer], ">") == 0){
        pointer++;
        int fd = open(list[pointer], O_WRONLY | O_CREAT | O_TRUNC, 0666);
        dup2(fd, 1);
        close(fd);
        return 1;
    }
    else if(strcmp(list[pointer], ">>") == 0){
        pointer++;
        int fd = open(list[pointer], O_WRONLY | O_CREAT | O_APPEND, 0666);
        dup2(fd, 1);
        close(fd);
        return 1;
    }
    else
        return 0;
}
int command(int from, int to, char* list[], int bracket[]){
        int check; int pointer0;
        if(strcmp(list[from], "(") == 0){
            int check = bracket[from];
            exit(check);
        }
        int pointer = from;
        if(redirection(pointer, list)){
            pointer += 2;
            if(redirection(pointer, list)){
                pointer += 2;
            }
            check = conveyor(pointer, to, list);
            if(check == 0)
                exit(1);
            else
                exit(0);
        }
        else {
            int pointer = from;
            pointer0 = to;
            while(pointer < to){
                if(strcmp(list[pointer], ">>") == 0 || (strcmp(list[pointer], ">") == 0) || (strcmp(list[pointer], "<") == 0)){
                    pointer0 = pointer;
                    if(redirection(pointer, list)){
                        pointer += 2;
                        if(redirection(pointer, list)){
                            pointer += 2;
                        }
                    }
                    break;
                }
                pointer++;
            }
            check = conveyor(from, pointer0, list);
            if(check == 0)
                return 1;
            else
                return 0;
        }
}

int command_conditional(int from, int to, char* list[], int bracket[]){
    int pointer = from, success = 0, failure = 0, flag = 0;
    while(pointer < to){
        if(strcmp(list[pointer], "&&") == 0){
            success = 1;
            break;
        }
        else if(strcmp(list[pointer], "||") == 0){
            failure = 1;
            break;
        }
        pointer++;
    }
    if(pointer == to){
        flag = 1;
    }
    int check = command(from, pointer, list, bracket);
    if(!flag){
        if((check && success) || (!check && failure)){
            check = command_conditional(pointer + 1, to, list, bracket);
        }
    }
    return check;
}
int command_shell(int from, int to, char* list[]){
    int bracket[MAXWORDS], flag = 0, i = from;
    int pointer = from, open_close = 0;
    int flagbracket = 0;
    if(to == 0){
        return 0;
    }
    while(!flag){ //expression in ()?
        while(!flag){
            if(strcmp(list[pointer], "&") == 0 || strcmp(list[pointer], ";") == 0){
                flag = 1;
                break;
            }
            if(strcmp(list[pointer], "(") == 0){
                pointer++;
                break;
            }
            pointer++;
            if(pointer == to){
                flag = 1;
                break;
            }
        }
        if(flag)    //not found '(';
            break;
        open_close = 1;
        i = pointer;
        while(!((strcmp(list[i], ")") == 0) && open_close == 1)){
            if(strcmp(list[i], "(") == 0)
                open_close++;
            if(strcmp(list[i], ")") == 0)
                open_close--;
            i++;
        }
        int status, waitstatus;
        if(fork() == 0){ // запускаем на выполнение выражение в скобках
            if((strcmp(list[i+1], "&") == 0)){
                if(fork() == 0){
                    int fd[2];
                    fd[0] = open("/dev/null", O_RDONLY);
                    fd[1] = open("/dev/null", O_WRONLY);
                    dup2(fd[0], 0);
                    dup2(fd[1], 1);
                    signal(SIGINT, SIG_IGN); //ignore ^C
                    command_conditional(pointer, i, list, bracket);
                    exit(0);
                }
                else{
                    exit(0);
                }
            wait(NULL);
            }
            else{
                status = command_shell(pointer, i, list);
                exit(status);
            }
            exit(0);
        }
        if((strcmp(list[i+1], "&") == 0) && (i + 2 <= to)){
            flagbracket = 1;
            command_shell(i + 2, to, list);
            return 1;
        }
        wait(&waitstatus);
        bracket[pointer - 1] = WEXITSTATUS(waitstatus);
        pointer = i;
    }
    if(!flagbracket){
    flag = 0;
    pointer = from;
    int semicolon = 0, fon = 0;
    //printf("%s\n", list[pointer]);
    while(pointer < to){
        if(strcmp(list[pointer], ";") == 0){
            semicolon = 1;
            break;
        }
        else if((strcmp(list[pointer], "&") == 0) && (strcmp(list[pointer-1], ")") != 0)){
            fon = 1;
            break;
        }
        pointer++;
    }
    if(pointer + fon + semicolon == to){
        flag = 1;
    }
    int check = 0;
    if(fon){
        if(fork() == 0){
            if(fork() == 0){
                int fd[2];
                fd[0] = open("/dev/null", O_RDONLY);
                fd[1] = open("/dev/null", O_WRONLY);
                dup2(fd[0], 0);
                dup2(fd[1], 1);
                signal(SIGINT, SIG_IGN); //ignore ^C
                int check = command_conditional(from, pointer, list, bracket);
                exit(check);
            }
            else{
                exit(0);
            }
        }
        else{
            wait(NULL);
        }
    }
    else{
        check = command_conditional(from, pointer, list, bracket);
    }
    if(!flag)
        command_shell(pointer + 1, to, list);
    }
    return 0;
}
void lineTOmas(char line[], int* count_list, char* list[]){
    int i = 0, count = 0, from, to;
    int flag = (strlen(line) == 0);
    while(!flag){
        // skip ' '
        while(line[i] == ' '){
            i++;
            if(i == strlen(line)){ // only ' '
                flag = 1;
                break;
            }
        }
        if(flag){
            break;
        }
        from = i;
        while(line[i] != ' '){ // read word
            i++;
            if(i == strlen(line)){
                flag = 1;
                break;
            }
        }
        to = i;
        list[count] = (char*)malloc((to - from + 1)*sizeof(char)); 
        for(int j = from; j < to; j++)
            list[count][j - from] = line[j]; // list[count] = word №count
        list[count][to - from] = '\0';
        count++;
    }
    *count_list = count;
}
char* ReadLine(void){
    int buff = size;
    char* buffer = (char*)malloc(buff*sizeof(char));
    char symbol;
    int pointer = 0;
    while(1){
        symbol = fgetc(stdin);
        if(symbol == EOF || symbol == '\n'){
            buffer[pointer] = '\0';
            return buffer; 
        }
        else{
            buffer[pointer] = symbol;
        }
        pointer++;
        if(pointer >= buff){
            buff += size;
            buffer = realloc(buffer, buff);
        }
    }
}
/*
char* SpaceRemove(char* str){
    int i, k = 0;
    if(str[0] == ' '){
        while(str[k] == ' '){
            k++;
        }
    }
    str = (str + k);
    k = 0;
    for(i = 1; str[i]; i++){
        str[i] = str[i+k];
        if((str[i] == ' ' && str[i-1] != ' ') || (str[i] == '|') || (str[i] == '>') || (str[i] == '<') || (str[i] == '>') ||
            (str[i] == '&') || (str[i] == '|') || (str[i] == ';') || (str[i] == '&') || (str[i] == '(') || (str[i] == ')'))
            continue;
        if(str[i] == ' ' || str[i] == '\t'){
            k++;
            i--;
        }
    }
    if(str[strlen(str) - 1] == ' '){
        str[strlen(str) - 1] = '\0';
    }
    return str;
}

char* MakeSpaces(char* str){
    int k;
    int buff = 2048;
    char* s = (char*) malloc(buff*sizeof(char));
    strcpy(s, str);
    char buf;
    for(int i = 0; s[i+1]; i++){
        if((s[i]) != ' ' && ((s[i+1] == '|') || (s[i+1] == '>') || (s[i+1] == '<') || (s[i+1] == '>') ||
            (s[i+1] == '&') || (s[i+1] == '|') || (s[i+1] == ';') || (s[i+1] == '&') || (s[i+1] == '(') || (s[i+1] == ')'))){
                k = i + 1;
                buf = s[k];
                str[k] = ' ';
                k++;
                while(buf != '\0'){
                    s[k] = buf;
                    buf = s[k+1];
                    k++;
                }
            }
    }
    for(int i = 0; s[i+1]; i++){
        if((s[i+1]) != ' ' && ((s[i] == '|') || (s[i] == '>') || (s[i] == '<') || (s[i] == '>') ||
            (s[i] == '&') || (s[i] == '|') || (s[i] == ';') || (s[i] == '&') || (s[i] == '(') || (s[i] == ')'))){
                k = i + 1;
                buf = s[k];
                str[k] = ' ';
                k++;
                while(buf != '\0'){
                    s[k] = buf;
                    buf = s[k+1];
                    k++;
                }
            }
    }
    return s;
}
*/
int main(){
    while(1){
        //char line[MAXLINE + 1];
        //fgets(line, MAXLINE, stdin); // read line
        //line[strlen(line) -1] = '\0'; // so '\n' -last symbol
        char* line = ReadLine();
        //printf("%s\n", line);
        //line = SpaceRemove(line);
        //printf("%s\n", line);
        //line = MakeSpaces(line);
        //printf("%s\n", line);
        int count_list;
        char* list[MAXWORDS];
        lineTOmas(line, &count_list, list); // line to array
        //printf("%d\n", count_list);
        //for(int i = 0; i < count_list; i++)
        //    printf("%s\n", list[i]);
        command_shell(0, count_list, list);
        free(line);
        for(int i = 0; i < count_list; i++)
            free(list[i]);
    }
    return 0;
}
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdarg.h>
#define number 30

typedef struct node{
    char* c;
    int k;
    int len;
    struct node* next;
} node;

node* createnode(char* file, int s){
    node* list = NULL;
    node* head = NULL;
    FILE* f = fopen(file, "r");
    if(f == NULL)
        return head;
    node* tmp = (node*)malloc(sizeof(node));
    tmp->c = malloc(sizeof(char)*number+1);
    while(fgets(tmp->c, number, f)){
        tmp->k = 1;
        tmp->len = strlen(tmp->c) - 1;
        tmp->next = NULL;
        list = head;
        if(head != NULL){
            while(list->next != NULL){
                if(list->len <= s && tmp->len <= s){
                    list->k++;
                    tmp->k++;
                }
                else if(list->len > s && tmp->len >s){
                    if(strcmp(list->c+s, tmp->c+s) == 0){
                        list->k++;
                        tmp->k++;
                    }
                }
                list = list->next;
            }
            if(list->len <= s && tmp->len <= s){
                    list->k++;
                    tmp->k++;
                }
                else if(list->len > s && tmp->len >s){
                    if(strcmp(list->c+s, tmp->c+s) == 0){
                        list->k++;
                        tmp->k++;
                    }
                }
            list->next = tmp;
        }
        else{
            head = tmp;
        }
        tmp = (node*)malloc(sizeof(node));
        tmp->c = malloc(sizeof(char)*number);
    }
    free(tmp->c);
    free(tmp);
    fclose(f);
    return head;
}
void my_uniq(int count, char* file, ...){
    int s = 0;
    char c = 0, d = 0, u = 0;
    va_list argm;
    va_start(argm, file);
    char* tmp;
    for(int i = 0; i < count; i++){
        tmp = va_arg(argm, char*);
        if(tmp[1] == 'c')
            c = 1;
        else if(tmp[1] == 'd')
            d = 1;
        else if(tmp[1] == 'u')
            u = 1;
        else if(tmp[1] == 's')
            s = atoi(tmp+2);
    }
    va_end(argm);
    if(d == 1 && u == 1)
        return;
    node* list = createnode(file, s);
    if(list == NULL)
        return;
    node* saved = NULL;
    node* head = list;
    if(d){//only ununiq
        if(list->k > 1){
            if(c)
                printf("%d: %s", list->k, list->c);
            else
                printf("%s", list->c);
        }
        saved = list;
        list = list->next;
        while(list != NULL){
            if(list->k > 1){
                if(saved->len > s && list->len > s){
                    if(strcmp(saved->c+s, list->c+s) != 0){
                        if(c)
                            printf("%d: %s", list->k, list->c);
                        else
                            printf("%s", list->c);
                    }
                }
                else if ((saved->len > s && list->len <= s) || (saved->len <= s && list->len > s)){
                    if(c)
                        printf("%d: %s", list->k, list->c);
                    else
                        printf("%s", list->c);
                }
            }
            saved = list;
            list = list->next;
        }
    }
    else if(u){//only uniq
        while(list != NULL){
            if(list->k == 1){
                if(c)
                    printf("%d: %s", list->k, list->c);
                else
                    printf("%s", list->c);
            }
            list = list->next;
        }
    }
    else{
        if(c)
            printf("%d: %s", list->k, list->c);
        else
            printf("%s", list->c);
        saved = list;
        list = list->next;
        while(list != NULL){
            if(saved->len > s && list->len > s){
                if(strcmp(saved->c+s, list->c+s) != 0){
                    if(c)
                        printf("%d: %s", list->k, list->c);
                    else
                        printf("%s", list->c);
                }
            }
            else if ((saved->len > s && list->len <= s) || (saved->len <= s && list->len > s)){
                if(c)
                    printf("%d: %s", list->k, list->c);
                else
                    printf("%s", list->c);
            }
        saved = list;
        list = list->next;
        }
    }
    node* del;
    list = head;
    while(list != NULL){
        free(list->c);
		del = list;
        list = list->next;
		free(del);
	}
} 
int main(int argc, char** argv){
    // example input: ./task test -c -d -u -s2
    if(argc < 2)
        return 0; 
    if(argc == 2){
        my_uniq(0, argv[1]);
        return 0;
    }
    if(argc == 3){
        my_uniq(1, argv[1], argv[2]);
        return 0;
    }
    if(argc == 4){
        my_uniq(2, argv[1], argv[2], argv[3]);
        return 0;
    }
    if(argc == 5){
        my_uniq(3, argv[1], argv[2], argv[3], argv[4]);
        return 0;
    }
    if(argc == 6){
        my_uniq(4, argv[1], argv[2], argv[3], argv[4], argv[5]);
        return 0;
    }
    return 0;
}
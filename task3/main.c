#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node{
    char* word;
    struct node* next;
}node;

node* createnode(){
    node* head = NULL;
    char* str = (char*)malloc(sizeof(char));
    node* list = head;
    scanf("%s ", str);
    while (strcmp(str, "end") != 0) {
        node* tmp = (node*)malloc(sizeof(node));
        tmp->word = str;
        tmp->next = NULL;
        list = head;
        if (head != NULL) {
            while (list->next != NULL){
                list = list->next;
            }
            list->next = tmp;
            }
        else {
            head = tmp;
        }
        str = (char*)malloc(sizeof(char));
        scanf("%s", str);
    }
    return head;
}

void outnode (node* list){
    while (list != NULL){
        printf("%s ", list->word);
        list = list->next;
    }
}

void renode(node* list, char c){
    int k;
    while(list != NULL){
        k = strlen(list->word);
        if((list->word)[k-1] == c){
            node* tmp = (node*)malloc(sizeof(node));
            char* temp =(char*)malloc(sizeof(char[4]));
            temp[0] = '2';
            temp[1] = '2';
            temp[2] = '2';
            temp[3] = '\0';
            tmp->word = temp;
            tmp->next = list->next;
            list->next = tmp;
            list = list->next;
        }
        list = list->next;
    }
}
node* deleteifc(node* list, char c){
    node* pred = list; //указатель на предыдущий элемент списка
    node* tek = list; //указатель на текущий элемент списка
    while(tek != NULL){
        if(strchr(tek->word, c) != 0){
            //find in first word
            if(tek == list){
                pred = tek->next;
                list = tek->next;
                free(tek->word);
                free(tek);
                tek = pred;
            }
            else{
                pred->next = tek->next;
                free(tek->word);
                free(tek);
                tek = pred->next;
            }
        }
        //not find
        else{
            pred = tek;
            tek = tek->next;
        }
    }
    return list;
}

void deletenode(node* a){
    if(a != NULL){
        deletenode(a->next);
        free(a->word);
        free(a);
    }
}

int main()
{
    // enter 'end' for stop input
    node* list = createnode();
    outnode(list);
    printf("\n");
    printf("input symbol: ");
    char c;
    getchar();
    scanf("%c", &c);
    renode(list, c);
    outnode(list);
    printf("\n");
    printf("input symbol: ");
    getchar();
    scanf("%c", &c);
    list = deleteifc(list,c);
    outnode(list);
    deletenode(list);
    return 0;
}

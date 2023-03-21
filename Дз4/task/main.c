#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node{
    char* c;
    struct node* next;
} node;

typedef struct word{
    char c;
    struct word* next;
} word;
int flag = 1;
word* createword(){
    word* head = NULL;
    word* list = NULL;
    char c;
    scanf("%c", &c);
    while(c == ' ')
        scanf("%c", &c);
    if(c == -1 || c == '\n'){
        flag = 0;
        return head;
    }
    while(c != ' ' && c != -1 && c != '\n'){
        word* temp = (word*)malloc(sizeof(word));
        temp->c = c;
        temp->next = NULL;
        list = head;
        if(head != NULL){
            while(list->next != NULL)
                list = list->next;
            list->next = temp;
        }
        else{
            head = temp;
        }
        scanf("%c", &c);
        if(c == '\n' || c == -1)
            flag = 0;
    }
    return head;
}

char* addword(word* newword){
    word* save = newword;
    word* del;
    int length = 0;
    while(save != NULL){
        length++;
        save = save->next;
    }
    char* result = NULL;
    if(length == 0)
        return result;
    else{
        result = (char*)malloc(length+1);
        int k = 0;
        while(newword != NULL){
            result[k] = newword->c;
		    del = newword;
            newword = newword->next;
		    free(del);
            k++;
        }
        result[k] = '\0';
        return result;
    }
}
node* createnode(){
    node* list = NULL;
    node* head = list;
    char* temp = addword(createword());
    while (temp != NULL){
        node* tmp = (node*)malloc(sizeof(node));
        tmp->c = temp;
        tmp->next = NULL;
        list = head;
        if(head != NULL){
            while(list->next != NULL)
                list = list->next;
            list->next = tmp;
        }
        else{
            head = tmp;
        }
        if(flag == 0)
            break;
        temp = addword(createword());
    }
    return head;
}
void outlist(node* list){
    while(list != NULL){
        printf("%s ", list->c);
        list = list->next;
    }
}

void invert(node* list){
    if(list == NULL)
        return;
    invert(list->next);
    printf("%s ", list->c);
}

node* iWord(node* list, int i){
	for(int j = 0; j < i; j++)
		list = list->next;
	return list;
}

void sortlist(node* list){
    int size = 0;
    node* saved = list;
    if(list == NULL)
        return;
    while(list != NULL){
        size++;
        list = list->next;
    }
    list = saved;
    char* change;
    for(int i = 0; i < (size-1); i++)
        for(int j = (i+1); j < size; j++)
            if(strcmp(iWord(list, i)->c, iWord(list, j)->c) > 0){
                change = iWord(list, i)->c;
                iWord(list, i)->c = iWord(list, j)->c;
                iWord(list, j)->c = change;
            }
}

int main()
{
    printf("Enter list: ");
    node* list = createnode();
    outlist(list);
    printf("\n");
    //¹1
    printf("Invert: \n");
    invert(list);
    printf("\n");
    //N2
    printf("Sorted: \n");
    sortlist(list);
    outlist(list);
    //delete
    node* del;
    while(list != NULL){
		free(list->c);
		del = list;
        list = list->next;
		free(del);
	}
    return 0;
}
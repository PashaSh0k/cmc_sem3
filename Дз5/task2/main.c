#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct tree{
    char* c;
    struct tree* left;
    struct tree* right;
}tree;

typedef struct word{
    char c;
    struct word* next;
}word;
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
tree* createtree(){
    tree* tree1 = NULL;
    tree* head = tree1;
    tree* saved = NULL;
    char* temp = addword(createword());
    while (temp != NULL){
        tree* tmp = (tree*)malloc(sizeof(tree));
        tmp->c = temp;
        tmp->left = NULL;
        tmp->right = NULL;
        saved = NULL;
        tree1 = head;
        while(tree1 != NULL)
            if(strcmp(tmp->c, tree1->c) > 0){
                saved = tree1;
                tree1 = tree1->right;
            }
            else if(strcmp(tmp->c, tree1->c) < 0){
                saved = tree1;
                tree1 = tree1->left;
            }
            else
                break; 
        if(head == NULL){
            head = tmp;
        }         
        else if(saved != NULL){
            if(strcmp(tmp->c, saved->c) > 0)
                saved->right = tmp;
            else if(strcmp(tmp->c, saved->c) < 0)
                saved->left = tmp;
        }
        else{
            free(tmp->c);
            free(tmp);
        }
        if(flag == 0)
            break;
        temp = addword(createword());
    }
    return head;
}
void outtree(tree* head){
    if(head == NULL)
        return;
    outtree(head->left);
    printf("%s ", head->c);
    outtree(head->right);
}
void deletetree(tree* head){
    if(head == NULL)
        return;
    deletetree(head->left);
    deletetree(head->right);
    free(head->c);
    free(head);
}
int main()
{
    printf("Enter list: ");
    tree* binarytree = createtree();
    printf("OUTPUT TREE\n");
    outtree(binarytree);
    printf("\n");
    //delete
    deletetree(binarytree);
    return 0;
}
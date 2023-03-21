#include <stdio.h>
#include <stdlib.h>

typedef struct tree{
    int value;
    struct tree* left;
    struct tree* right;
}tree;

tree* createtree(int value){
    tree* temp = (tree*)malloc(sizeof(tree));
    temp->left = NULL;
    temp->right = NULL;
    temp->value = value;
    return temp;
}
void addelem(tree* head, int value){
    tree* saved = NULL;
    while(head != NULL){
        if(value < head->value){
            saved = head;
            head = head->left;
        }
        else if(value > head->value){
            saved = head;
            head = head->right;
        }
        else
            return;
    }
    tree* temp = malloc(sizeof(tree));
    temp->value = value;
    temp->left = temp->right = NULL;
    if(temp->value < saved->value)
        saved->left = temp;
    else
        saved->right = temp;
}

void outtree(tree* head){
    if(head == NULL)
        return;
    outtree(head->left);
    outtree(head->right);
    printf("%d ", head->value);
}
int findnumber(int value, tree* head){
    int k = 0;
    while(head != NULL){
        k++;
        if(value == head->value)
            return k;
        else if(value < head->value)
            head = head->left;
        else
            head = head->right;
    }
    k = -1;
    return k;
}
void deletetree(tree* head){
    if(head == NULL)
        return;
    deletetree(head->left);
    deletetree(head->right);
    free(head);
}
int main()
{
    printf("Enter nubmers: ");
    int value;
    tree* head = NULL;
    if(scanf("%d", &value)){
        head = createtree(value);
    }
    while(scanf("%d", &value)){
        addelem(head, value);
    }
    printf("Output: ");
    if(head != NULL)
        outtree(head);
    else
        printf("Empty tree");
    printf("\n");
    printf("Enter number = ");
    getchar();
    int number;
    scanf("%d", &number);
    int k = findnumber(number, head);
    if(k == -1)
        printf("Not found");
    else
        printf("%d", k);
    deletetree(head);
    return 0;
}

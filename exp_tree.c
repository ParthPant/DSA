#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

struct Node{
    char data;
    struct Node* right;
    struct Node* left;
};

struct ListNode {
  struct Node *data;
  struct ListNode *next;
};

void enqueue(struct ListNode **head, struct Node *data) {
  struct ListNode *newNode = (struct ListNode *)malloc(sizeof(struct ListNode));
  newNode->data = data;
  newNode->next = NULL;

  if (*head == NULL) {
    *head = newNode;
  } else {
    struct ListNode *ptr = *head;
    while (ptr->next != NULL) {
      ptr = ptr->next;
    }
    ptr->next = newNode;
  }
}

void push(struct ListNode **head, struct Node *data){
  struct ListNode *newNode = (struct ListNode *)malloc(sizeof(struct ListNode));
  newNode->data = data;
  newNode->next = *head;

  *head = newNode;
}

struct Node *dequeue(struct ListNode **head) {
  struct ListNode *tmp = *head;
  struct Node *res = tmp->data;
  *head = (*head)->next;
  free(tmp);
  return res;
}

#define pop dequeue

struct Node* newNode(char data, struct Node* right, struct Node* left){
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));

    node->data = data;
    node->right = right;
    node->left = left;

    return node;
}

int isEmpty(struct ListNode *head) {
  if (head == NULL)
    return 1;
  else
    return 0;
}

void inorder(struct Node* tree){
    if(tree == NULL){
        return;
    }

    inorder(tree->left);
    printf("%c ", tree->data);
    inorder(tree->right);
}

void preorder(struct Node* tree){
    if(tree == NULL){
        return;
    }

    printf("%c ", tree->data);
    preorder(tree->left);
    preorder(tree->right);
}

void postorder(struct Node* tree){
    if(tree == NULL){
        return;
    }

    postorder(tree->left);
    postorder(tree->right);
    printf("%c ", tree->data);
}

void levelorder(struct Node* tree){
    if(tree == NULL){
        return;
    }else{
      struct ListNode *queue = NULL;
      enqueue(&queue, tree);

      while (isEmpty(queue) != 1) {
        struct Node *current = dequeue(&queue);
        if (current != NULL)
          printf("%c ", current->data);
        if (current->left != NULL)
          enqueue(&queue, current->left);
        if (current->right != NULL)
          enqueue(&queue, current->right);    
        }
    }
}

int isOperator(char c){
    if(c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
        return 1;
    return 0;
}

struct Node *postfix_tree(char *str){
    struct ListNode* stack;
    for(int i=0; str[i] != '\0'; i++){
        if(isOperator(str[i]) == 1){
            struct Node *right = pop(&stack);
            struct Node *left = pop(&stack);

            struct Node *rootNode = newNode(str[i], right, left);
            push(&stack, rootNode);
        }else{
            struct Node *newLeaf = newNode(str[i], NULL, NULL);
            push(&stack, newLeaf);
        }
    }
    return pop(&stack);
}

float calculate(float a, char O, float b){
    switch(O){
        case '+': return a+b;
        case '*': return a*b;
        case '-': return a-b;
        case '/': return a/b;
        case '^': return pow(a,b);
        default: printf("Invalid Symbol Encountered\n");
                 return 0;
    }
}

float evaluate(struct Node *tree){
    if(isOperator(tree->data) != 1){
        return (int)tree->data - '0';
    }else{
        float left = evaluate(tree->left);
        float right = evaluate(tree->right);
        
        return calculate(left, tree->data, right);
    }
}

int main(){
    char expr[50];
    printf("Enter a postfix expression\n");
    scanf("%s", expr);

    struct Node *tree = postfix_tree(expr);

    printf("Level Order:\n");
    levelorder(tree);
    printf("\n");

    printf("InOrder:\n");
    inorder(tree);
    printf("\n");

    printf("PostOrder:\n");
    postorder(tree);
    printf("\n");

    printf("PreOrder:\n");
    preorder(tree);
    printf("\n");

    printf("Answer: %f", evaluate(tree));
}

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

struct Node{
    int data;

    struct Node* right;
    struct Node* left;
};

struct ListNode {
  struct Node *data;
  struct ListNode *next;
};

void push(struct ListNode **head, struct Node *data){
  struct ListNode *newNode = (struct ListNode *)malloc(sizeof(struct ListNode));
  newNode->data = data;
  newNode->next = *head;
  *head = newNode;
}

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

struct Node *dequeue(struct ListNode **head) {
  struct ListNode *tmp = *head;
  struct Node *res = tmp->data;
  *head = (*head)->next;
  free(tmp);
  return res;
}

#define pop dequeue

struct Node* newNode(int data){
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));

    node->data = data;
    node->right = NULL;
    node->left = NULL;

    return node;
}

int isEmpty(struct ListNode *head) {
  if (head == NULL)
    return 1;
  else
    return 0;
}

void insert(struct Node** tree, int data){
    if(*tree == NULL){
        *tree = newNode(data);
    }else{
      struct ListNode *queue = NULL;
      enqueue(&queue, *tree);

      while (isEmpty(queue) != 1) {
        struct Node *current = dequeue(&queue);
        /*printf("dequeued--- %d\n",current->data);*/

        if (current->left != NULL) {
          enqueue(&queue, current->left);
          /*printf("enqueued--- %d\n", current->left->data);*/
        } else {
          current->left = newNode(data);
          /*printf("\n");*/
          return;
        }

        if (current->right != NULL) {
          enqueue(&queue, current->right);
          /*printf("enqueued--- %d\n", current->right->data);*/
        } else {
          current->right = newNode(data);
          /*printf("\n");*/
          return;
        }
        }
    }
}

void inorder(struct Node* tree){
    if(tree == NULL){
        return;
    }

    inorder(tree->left);
    printf("%d ", tree->data);
    inorder(tree->right);
}

void preorder(struct Node* tree){
    if(tree == NULL){
        return;
    }

    printf("%d ", tree->data);
    preorder(tree->left);
    preorder(tree->right);
}

void postorder(struct Node* tree){
    if(tree == NULL){
        return;
    }

    postorder(tree->left);
    postorder(tree->right);
    printf("%d ", tree->data);
}

void levelorder(struct Node* tree){
    if(tree == NULL){
        return;
    }else{
      struct ListNode *queue = NULL;
      enqueue(&queue, tree);

      while (isEmpty(queue) != 1) {
        struct Node *current = dequeue(&queue);
        printf("%d ", current->data);
        if (current->left != NULL)
          enqueue(&queue, current->left);
        if (current->right != NULL)
          enqueue(&queue, current->right);    
        }
    }
}

int main(){
    struct Node* tree;

    insert(&tree, 1);
    insert(&tree, 2);
    insert(&tree, 3);
    insert(&tree, 4);
    insert(&tree, 5);
    insert(&tree, 6);
    insert(&tree, 7);
    insert(&tree, 8);

    inorder(tree);
    printf("\n");
    preorder(tree);
    printf("\n");
    postorder(tree);
}

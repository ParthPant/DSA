#include <stdio.h>
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
        if(data < (*tree)->data){
            insert(&(*tree)->left, data);
        }else{
            insert(&(*tree)->right, data);
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

void search(struct Node* tree, int data){
    if(tree == NULL){
        printf("Not Found\n");
    }
    else{
        if(data > tree->data)
            search(tree->right, data);
        else if(data < tree->data)
            search(tree->left, data);
        else{
            printf("Found %d", tree->data);
        }
    }
}

struct Node* getInorderSuccessor(struct Node **tree){
    struct Node* res = *tree;
    res = res->right;
    while(res->left != NULL && res != NULL){
        res = res->left;
    }
    return res;
}

void delete(struct Node** tree, int data){
    if(tree == NULL)
        printf("Not Found\n");
    else{
        struct Node** curr = tree;
        while((*curr)->data != data && *curr != NULL){
            if(data > (*curr)->data)
                curr = &(*curr)->right;
            else if(data < (*curr)->data)
                curr = &(*curr)->left;
        }

        if(curr == NULL){
            printf("Not Found\n");
        }else if((*curr)->left == NULL){
            struct Node* tmp = *curr;
            *curr = (*curr)->right;
            free(tmp);
        }else if((*curr)->right == NULL){
            struct Node* tmp = *curr;
            *curr = (*curr)->left;
            free(tmp);
        }else{
            struct Node* tmp = getInorderSuccessor(curr); 
            (*curr)->data = tmp->data;
            delete(&((*curr)->right), tmp->data);
        }
    }
}

int main(){
  struct Node *bst;

  insert(&bst, 50);
  insert(&bst, 30);
  insert(&bst, 20);
  insert(&bst, 40);
  insert(&bst, 70);
  insert(&bst, 60);
  insert(&bst, 80);

  inorder(bst);
  printf("\n");
  levelorder(bst);

  printf("\n-----------------\n");

  delete(&bst, 70);

  inorder(bst);
  printf("\n");
  levelorder(bst);
}

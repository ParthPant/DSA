#include <stdio.h>
#include <stdlib.h>

struct node{
  int data;
  struct node *next;
};

struct node *new() { return (struct node *)malloc(sizeof(struct node)); }

void enqueue(struct node **front, struct node **rear, int data){
  if(*front == NULL){
    (*front) = new();
    (*front)->next = NULL;
    (*front)->data = data;
    *rear = *front;
  }else{
    (*rear)->next = new();
    *rear = (*rear)->next;
    (*rear)->data = data;
  }
}

void dequeue(struct node **front, struct node **rear){
  if(*front == NULL){
    return;
  }else{
    struct node *tmp = *front;
    (*front) = (*front)->next;
    free(tmp);
  }
}

void print(struct node *front){
  printf("*****\n");
  while(front != NULL){
    printf("%d\n", front->data);
    front = front->next;
  }
}

int getSize(struct node *first){
  int size =0;
  struct node *ptr = first;
  if(ptr == NULL){return 0;}  
  while(ptr != NULL){
    ptr = ptr->next; 
    size++;
  }
  return size;
}

int isEmpty(struct node *first){
  int size = getSize(first);
  if(size == 0)
    return 1;
  else
    return 0;
}

int getfront(struct node *front){
  return front->data;
}

void push(struct node **front1, struct node **rear1, struct node **front2, struct node **rear2, int data){
  enqueue(front2, rear2, data);
  while(isEmpty(*front1) != 1){
    enqueue(front2, rear2, getfront(*front1)); 
    dequeue(front1, rear1);
  }  
  struct node *tmp = *front1;
  *front1 = *front2;
  *front2 = tmp;
  
  tmp = *rear1;
  *rear1 = *rear2;
  *rear2 = tmp;
}

void pop(struct node **front1, struct node **rear1, struct node **front2, struct node **rear2){
  dequeue(front1, rear1);  
}

int main(){
  struct node *front1 = NULL, *front2 = NULL, *rear1 = NULL, *rear2 = NULL;
  printf("1:Push\n2:Pop\n3:Print\n");
  int input, choice;
  while(1){
    scanf("%d", &choice);
    switch(choice){
      case 1:
        printf("Enter the value:\n");
        scanf("%d", &input);
        push(&front1, &rear1, &front2, &rear2, input);  
        break;
      case 2:
        pop(&front1, &rear1, &front2, &rear2);
        break;
      case 3:
        print(front1);
    } 
  }
}
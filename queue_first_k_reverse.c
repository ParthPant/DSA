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

void print(struct node *front){
  printf("*****\n");
  while(front != NULL){
    printf("%d\n", front->data);
    front = front->next;
  }
}

void push(struct node** first, int data){
  if((*first)==NULL){
    *first = (struct node*)malloc(sizeof(struct node)); 
    (*first)->data = data;
    (*first)->next = NULL;
  }else{
    struct node *ptr = (struct node *)malloc(sizeof(struct node));
    ptr->data = data;
    ptr->next = *first;
    *first = ptr;
  }
}

void pop(struct node** first){
  if((*first)==NULL){
    printf("Underflow\n");
  }else{
    struct node * tmp = *first;
    (*first) = (*first)->next;
    free(tmp);
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

void reverse(struct node **front, struct node **rear, struct node **head, int k){
  int size = getSize(*front);
  while(isEmpty(*front)!=1){
    push(head, getfront(*front)); 
    pop(front);
  }

  while(isEmpty(*head) != 1){
    enqueue(front, rear, getfront(*head)); 
    pop(head);
  }
  
  for(int i=0; i<size-k+1; i++){
    push(head, getfront(*front)); 
    pop(front);
  }

  while(isEmpty(*head) != 1){
    enqueue(front, rear, getfront(*head)); 
    pop(head);
  }
}

int main(){
  struct node *front=NULL, *rear=NULL, *head=NULL;
  int n;
  printf("Enter the number of elements\n");
  scanf("%d", &n);
  for(int i=0; i<n; i++){
    int data;
    scanf("%d", &data);
    enqueue(&front, &rear, data); 
  }
  printf("Enter the value of K\n");
  int k;
  scanf("%d", &k);
  printf("Entered List:\n");
  print(front);
  printf("Modified List:\n");
  reverse(&front, &rear, &head, k);
  print(front);
}

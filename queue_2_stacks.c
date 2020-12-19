#include <stdio.h>
#include <stdlib.h>

struct node{
  int data;
  struct node *next;
};

struct node *new(){
  return (struct node *)malloc(sizeof(struct node));
}

void push(struct node **head, int data){
  if((*head) == NULL){
    (*head) = new(); 
    (*head)->data = data;
    (*head)->next = NULL;
  }else{
    struct node *ptr = new();
    ptr->data = data;
    ptr->next = *head;
    *head = ptr; 
  }
}

int pop(struct node **head){
   if(*head == NULL){
      return 0;     
   }
   struct node *p = *head;
   *head = (*head)->next;
   free(p);
   return 1;
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

void enqueue(int data, struct node **stack1, struct node **stack2){
  while(isEmpty(*stack1) != 1){
    push(stack2, getfront(*stack1)); 
    pop(stack1);
  }    
  push(stack2, data);
  while(isEmpty(*stack2) != 1){
    push(stack1, getfront(*stack2)); 
    pop(stack2);
  }    
}

void dequeue(struct node **stack1){
  if(pop(stack1))
    return;
  else{
    printf("Queue is empty"); 
  }
}

void print(struct node *front){
  printf("*****\n");
  while(front != NULL){
    printf("%d\n", front->data);
    front = front->next;
  }
}

int main(){
  struct node *stack1=NULL, *stack2=NULL;
  int choice, input;
  printf("1:Enqueue\n2:Dequeue\n3:Print\n");
  while(1){
    scanf("%d", &choice);
    switch (choice){
      case 1:
       printf("Enter value\n");
       scanf("%d", &input);
       enqueue(input, &stack1, &stack2); 
       break;
      case 2:
       dequeue(&stack1);
       break;
      case 3:
       print(stack1);
       break;
    } 
  }
}

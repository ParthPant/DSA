#include <stdio.h>
#include <stdlib.h>

struct node{
  int data;
  struct node *next;
};

struct node* insert_end(int data, struct node *first){
  if(first == NULL){
    first = (struct node*)malloc(sizeof(struct node));
    first->data = data;
    first->next = NULL;
    return first;
  }else {
    while(first->next != NULL){
      first = first->next; 
    }
    first->next = (struct node*)malloc(sizeof(struct node));
    first = first->next;
    first->data = data;
    first->next = NULL;
    return first;
  }
}

struct node* insert_beg(int data, struct node *first){
  if(first == NULL){ 
    first = (struct node*)malloc(sizeof(struct node));
    first->data = data;
    first->next = NULL;
    return first;
  }else{
    struct node *ptr = (struct node*)malloc(sizeof(struct node));
    ptr->next = first;
    ptr->data = data;
    first = ptr;
    ptr = NULL;
    return first;
  }
}

void print_list(struct node *first){
  printf("*********Linked List*******\n");
  struct node *ptr = first;
  int i = 0;
  while(ptr != NULL){
    printf("%d:%d\n", i, ptr->data);
    i++;
    ptr = ptr->next; 
  }
}

struct node* reverse(struct node* first){
  if (first->next->next == NULL){  
    first->next->next = first;
    first->next=NULL;
    return first;
  }
  struct node* p = reverse(first->next);
  p->next = first;
  first->next = NULL;
  return first;
}

int main(){
  struct node *first = NULL,*last = NULL;
  int input, loc;
  printf("1: insert in begining\n"); 
  printf("2: insert in end\n"); 
  printf("3: Reverse List\n"); 
  printf("4: Print list\n"); 
  printf("------------------\n");
  while(1){
    int option;
    scanf("%d",&option);
    switch(option){
      case 1:
        scanf("%d",&input);
        first = insert_beg(input,first);  
        break;
      case 2:
        scanf("%d",&input);
        last = insert_end(input,first);  
        break;
      case 3:
        reverse(first);
        first = last;
        break;
      case 4:
        print_list(first);
        break;
    }
  }
  return 0;
}

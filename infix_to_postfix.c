#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

struct node{
  char data;
  struct node *next;
};

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

char getfront(struct node *front){
  return front->data;
}

void push(struct node** first, char data){
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

int is_operator(char c){
  if(c == '+' || c == '-' || c == '/' || c == '*' || c == '^'){
    return 1; 
  }else{
    return 0; 
  }
}

int precedence(char c){
  if(c == '^')
    return 3;
  else if(c == '*' || c == '/')
    return 2;
  else if(c == '+' || c == '-')  
    return 1;
  else
    return 0;
}

void infix2postfix(char infix[]){
  char postfix[100];
  int i=0,j=0;
  char item;
  char x;

  struct node *stack = NULL;
  push(&stack, '(');
  strcat(infix, ")");

  item = infix[i];

  while(item != '\0'){
    if(item == '(') {
      push(&stack, item); 
    }else if(isalnum(item)){
      postfix[j] = item;
      j++; 
    }else if(is_operator(item) == 1){
      x = getfront(stack);
      while(is_operator(x) == 1 && precedence(x) >= precedence(item)){
        postfix[j] = x;
        j++;
        pop(&stack);
        x = getfront(stack);
      }     
      push(&stack, item);
    }else if(item == ')'){
      x = getfront(stack);
      while(x != '('){
        postfix[j] = x;
        j++;
        pop(&stack); 
        x = getfront(stack);
      }
		pop(&stack);
    }else{
      printf("Invalid infix expresson\n");
      getchar();
      exit(1); 
    }
    i++;
    item = infix[i];
  }
 while(isEmpty(stack)==0){
	postfix[j] = getfront(stack);
	 j++;
	 pop(&stack);
 }
  postfix[j] = '\0';
  printf("Postfix: %s\n", postfix);
}

int main(){
  char infix[100];
  printf("Enter infix expression\n");
  scanf("%s", infix);
  infix2postfix(infix);
}



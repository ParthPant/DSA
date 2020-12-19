#include <stdio.h>
#include <stdlib.h>
#include<ctype.h>
#include<string.h>

struct node{
  float data;
  struct node *next;
};

float getfront(struct node *front){
  return front->data;
}

void push(struct node** first, float data){
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

float apply(char operator, float a, float b){
  switch(operator){
    case '+':
     return a+b;
    case '-':
     return a-b;
    case '/':
     return a/b;
    case '*':
     return a*b; 
    default:
     printf("Invalid operator");
     exit(1);
  } 
}

float evaluate(char postfix[]){
  float res;
  struct node *stack;
  int i=0, j=0;
  char item = postfix[i];
  while(item != '\0'){
    if(isdigit(item)){ 
      push(&stack, (int)item-'0');
    }else if(is_operator(item) == 1){
      float a = getfront(stack);
      pop(&stack);
      float b = getfront(stack);
      pop(&stack);
      float c = apply(item, b, a); 
      push(&stack, c);
    }else{
      printf("Invalid Postfix expresson");
    }
    item  = postfix[++i]; 
  }
  res = getfront(stack);
  return res;
}

int main(){
  printf("Enter a postfix expression:\n");
  char str[100];
  scanf("%s", str);
  float res = evaluate(str);
  printf("Result is :%f\n", res);
}
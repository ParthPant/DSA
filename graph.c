#include <stdio.h>
#include <stdlib.h>

#define MAX_VERT 10

struct Graph{
    struct Node *heads[MAX_VERT]; 
};

struct Node{
    int weight;
    int dest;
    struct Node *next;
};

struct Edge{
    int src;
    int dest;
    int weight;
};

struct QueueNode{
    int data;
    struct QueueNode* next;
};

void addEdge(struct Graph** graph, struct Edge const edge){
    int src = edge.src;
    int dest = edge.dest;
    int weight = edge.weight;

    struct Node *new1 = (struct Node*)malloc(sizeof(struct Node));
    struct Node *new2 = (struct Node*)malloc(sizeof(struct Node));

    new1->weight = weight;
    new1->dest = dest;
    new1->next = (*graph)->heads[src];
    (*graph)->heads[src] = new1;

    new2->weight = weight;
    new2->next = (*graph)->heads[dest];
    new2->dest = src;
    (*graph)->heads[dest] = new2;
}

void search_and_delete(struct Node **head, int data){
    if((*head) == NULL){
        printf("Emply List\n");
        return;
    }else{
        struct Node *ptr =  *head, *tmp;
        if(ptr->dest == data){
            tmp = ptr;
            ptr = ptr->next;
            free(tmp);
        }
        while(ptr->next){
            if(ptr->next->dest == data){
                tmp = ptr->next;
                ptr->next =ptr->next->next;
                free(tmp);
                break;
            }
            ptr = ptr->next;
        }
    }
}

void removeEdge(struct Graph** graph, struct Edge const edge){
    int src = edge.src;
    int dest = edge.dest;
    
    search_and_delete(&(*graph)->heads[src], dest);
    search_and_delete(&(*graph)->heads[dest], src);
}

struct Graph* createGraph(struct Edge edges[], int num_edges){ 
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    for(int i=0; i<num_edges; i++)
        graph->heads[i] = NULL;

    for(int i=0; i<num_edges; i++){
        addEdge(&graph, edges[i]);
    }
    return graph;
}

void display(struct Graph* graph){
    for(int i=0; i<MAX_VERT; i++){
        struct Node* head = graph->heads[i];
        while(head){
            printf("(%d-->%d)  ", i, head->dest);
            head = head->next;
        }
        printf("\n");
    }
}

void enqueue(struct QueueNode** head, int data){
    if(*head == NULL){
        *head = (struct QueueNode*)malloc(sizeof(struct QueueNode));
        (*head)->data = data;
        (*head)->next = NULL;
    }else{
        struct QueueNode* ptr = *head;
        while(ptr->next)
            ptr=ptr->next;
        ptr->next = (struct QueueNode*)malloc(sizeof(struct QueueNode));
        ptr = ptr->next;
        ptr->next = NULL;
        ptr->data = data;
    }
}

void push(struct QueueNode** head, int data){
    if(*head == NULL){
        *head = (struct QueueNode*)malloc(sizeof(struct QueueNode));
        (*head)->data = data;
        (*head)->next = NULL;
    }else{
        struct QueueNode *ptr = (struct QueueNode*)malloc(sizeof(struct QueueNode));
        ptr->next = *head;
        ptr->data = data;
        *head = ptr;
    }
}

int pop(struct QueueNode **head) {
    if (*head == NULL) {
        printf("Empty List\n");
        return -1;
    } else {
        int res = (*head)->data;
        struct QueueNode *tmp = (*head);
        *head = (*head)->next;
        free(tmp);
        return res;
    }
}

void printList(struct QueueNode *head){
    if(head == NULL)
        printf("Empty List");
    else{
        while(head){
            printf("%d,\t", head->data);
            head = head->next;
        }
        printf("\n");
    }
}

int isEmpty(struct QueueNode* head){
    return 1 ? head == NULL : 0;
}

void bfs(struct Graph* graph, int start, int end){
    struct QueueNode *queue = NULL;
    enqueue(&queue, start);
    
    int visited[MAX_VERT] = {0};
    int found = 0;
    visited[start] = 1;
    
    /*printf("start---%d\n", start);*/
    /*printf("enqueued---%d\n", start);*/

    while(isEmpty(queue) != 1){
      /*printList(queue);   */
      int currVert = pop(&queue);
      printf("dequeued---%d\n", currVert);

      struct Node *adj = graph->heads[currVert];
      while(adj){
        if (visited[adj->dest] == 0) {
          /*if(adj->dest == end){*/
          /*printf("found\n");*/
          /*break;*/
          /*found = 1;*/
          /*}*/
          enqueue(&queue, adj->dest);
          /*printf("enqueued---%d\n", adj->dest);*/
          visited[adj->dest] = 1;
        }
        adj = adj->next;
        /*if (found == 1)*/
          /*break;*/
        }

    }

}

void dfs(struct Graph* graph, int start, int end){
    struct QueueNode *stack = NULL;
    push(&stack, start);
    
    int visited[MAX_VERT] = {0};
    int found = 0;
    visited[start] = 1;
    
    /*printf("start---%d\n", start);*/
    /*printf("pushed---%d\n", start);*/

    while(isEmpty(stack) != 1){
      /*printList(stack);   */
      int currVert = pop(&stack);
      printf("popped---%d\n", currVert);

      struct Node *adj = graph->heads[currVert];
      while(adj){
        if (visited[adj->dest] == 0) {
          /*if(adj->dest == end){*/
          /*printf("found\n");*/
          /*break;*/
          /*found = 1;*/
          /*}*/

          push(&stack, adj->dest);
          /*printf("pushed---%d\n", adj->dest);*/
          visited[adj->dest] = 1;
        }
        adj = adj->next;
        /*if (found == 1)*/
          /*break;*/
        }

    }

}

int main(){
    struct Edge edges[] = {{0,1}, {1,5}, {6,7}, {4,6}, {0,5}, {0,7}, {5,4}};
    int n = sizeof(edges)/sizeof(edges[0]);
    struct Graph *graph = createGraph(edges, n);
    display(graph);
}

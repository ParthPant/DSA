#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TABLE_SIZE 10

struct Data{
    int data;
    char key[20];
    struct Data* next;
};

unsigned int hash(char *key){
    int len = strlen(key);
    unsigned int hash = 0;
    for(int i=0; i<len; i++){
        hash += key[i];
        hash *= key[i];
    }
    return hash%TABLE_SIZE;
}

void insert(char *key, int data, struct Data *table[]){
    int index = hash(key);
    if(table[index] != NULL){
        struct Data *ptr = table[index];
        while(ptr->next){
            ptr = ptr->next;
        }
        ptr->next = (struct Data*)malloc(sizeof(struct Data));
        ptr = ptr->next;
        ptr->data = data;
        strcpy(ptr->key, key);
        ptr->next = NULL;
        return;
    }else{
        table[index] = (struct Data*)malloc(sizeof(struct Data));
        strcpy(table[index]->key, key);
        table[index]->data = data;
        table[index]->next = NULL;
        return;
    }
}

int search(char *key, struct Data *table[]){
    int index = hash(key);
    if(table[index] != NULL){
        if(strcmp(table[index]->key, key) == 0)
            return table[index]->data;
        else{
            struct Data *ptr = table[index]->next;
            while(ptr){
                if(strcmp(ptr->key, key)==0)
                    return ptr->data;
                ptr = ptr->next;
            }
        }
    }
    printf("Key not Found\n");
    return -1;
}

void display(struct Data *table[], int size){
    for(int i=0; i<size; i++){
        if(table[i] == NULL)
            printf("%d\t---\t---\n", i);
        else{
            if(table[i]->next == NULL)
                printf("%d\t%s\t%d\n", i, table[i]->key, table[i]->data);
            else{
                printf("%d\t%s\t%d\n", i, table[i]->key, table[i]->data);
                struct Data *ptr = table[i]->next;
                while(ptr){
                    printf("\t|\t%s\t%d\n", ptr->key, ptr->data);
                    ptr = ptr->next;
                }
            }
        }
    }
}

void delete(char *key, struct Data *table[]){
    int found = 0;
    int index =  hash(key);
    if(table[index] == NULL){
        found = 0;
    }else if(strcmp(table[index]->key, key)==0){
        found = 1;
        struct Data *tmp = table[index];
        table[index] = table[index]->next;
        free(tmp);
    }else if(table[index] != NULL){
        struct Data *ptr = table[index];
        while(ptr->next){
            if(strcmp(ptr->next->key, key)==0){
                found = 1;
                struct Data *tmp = ptr->next;
                ptr->next = ptr->next->next;
                free(ptr->next);
                break;
            }
            ptr = ptr->next;
        }
    }

    if(found == 0){
        printf("Key not Found\n");
    }
}

int main(){
    struct Data *hashTable[10] = {NULL};
    printf("1: Insert\n"); 
    printf("2: Delete\n"); 
    printf("3: Display\n"); 
    printf("4: Search\n"); 
    printf("------------------\n");
    int option, data;
    char key[100];
    while(1){
        scanf("%d",&option);
        switch(option){
            case 1:
                printf("Enter key and data\n");
                scanf("%s", key);
                scanf("%d",&data);
                insert(key, data, hashTable);
                break;
            case 2:
                printf("Enter Key to delete\n");
                scanf("%s", key);
                delete(key, hashTable);
                break;
            case 3:
                display(hashTable, TABLE_SIZE); 
                break;
            case 4:
                printf("Enter Key to search\n");
                scanf("%s", key);
                printf("%d\n",search(key, hashTable));
                break;
            }
        printf("-------------------------\n");
    }
}

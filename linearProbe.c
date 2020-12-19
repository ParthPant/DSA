/*
 * Question: Write a C program to insert keys into an array with linear probing technique of collision detection
 * Roll Number: 194007
 * Name: Parth Pant
 * Data: 30th Nov 2020
 * Subject: CS-201;
 */

#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 11 

struct Data{
	int data;
	int key;
};

unsigned int hash(int key){
	return key%TABLE_SIZE;
}

unsigned int hash2(int key){
    return 1+key%(TABLE_SIZE-2);
}

void insert(int key, int data, struct Data *table[]){
	int index = hash(key);
	int start = index;
	if(table[index] != NULL){
    	if(table[index]->key == key){
        	printf("CANNOT INSERT: Key already exists in the hash table\n");
        	return;
    	}
        /*int i=1;*/
        /*index = hash(key+i*i);	*/
        /*index = hash(index+1);	*/
        index = (index+hash2(key))%TABLE_SIZE; //double hash
    	while(table[index] != NULL && index != start){
        	if(table[index]->key == key){
            	printf("CANNOT INSERT: Key already exists in the hash table\n");
            	return;
        	}
            /*i++;*/
            /*index = hash(key+i*i);*/
            /*index = hash(index+1);	*/
            index = (index+hash2(key))%TABLE_SIZE;//double hash
    	}
    	if(index == start){
        	printf("Hash Table can not hold more data\n");
        	return;
    	}
    	table[index] = (struct Data*)malloc(sizeof(struct Data));
    	table[index]->key = key;
    	table[index]->data = data;
    	return;
	}else{
    	table[index] = (struct Data*)malloc(sizeof(struct Data));
    	table[index]->key = key;
    	table[index]->data = data;
    	return;
	}
}

void search(struct Data* table[], int key){
	int index = hash(key);
	int start = index;
	if(table[index] != NULL){
    	if(table[index]->key == key){
        	printf("Found at index %d, key %d, data stored = %d\n", index, key, table[index]->data);
        	return;
    	}
        /*int i =1;*/
        /*index = hash(index+i*i);*/
        /*index = hash(index+1);	*/
        index = (index+hash2(key))%TABLE_SIZE;//double hash
    	while(table[index]->key != key && index != start){
            /*i++;*/
            /*index = hash(index+i*i);*/
            /*index = hash(index+1);	*/
            index = (index+hash2(key))%TABLE_SIZE;//double hash
    	}
    	if(table[index]->key == key){
        	printf("Found at index %d, key %d, data stored = %d\n", index, key, table[index]->data);
    	}
    	if(index == start){
        	printf("Key does not exist\n");
        	return;
    	}
    	return;
	}else{
    	printf("Key does not exist\n");
    	return;
	}
}

void display(struct Data *table[]){
	printf("INDEX\tKEY\t-->\tDATA\n");
	for(int i=0; i<20; i++){
    	if(table[i] != NULL){
        	printf("%d\t%d\t-->\t%d\n", i, table[i]->key, table[i]->data);
    	}else{
        	printf("%d\t\tNO DATA\n", i);
    	}
	}
}

void delete(struct Data *table[], int key){
	int index = hash(key);
	int start = index;
	if(table[index] != NULL){
    	if(table[index]->key == key){
        	free(table[index]);
        	table[index] = NULL;
        	return;
    	}
        /*int i=1;*/
        /*index = hash(index+i*i);*/
        /*index = hash(index+1);	*/
        index = (index+hash2(key))%TABLE_SIZE;//double hash
    	while(table[index]->key != key && index != start){
            /*i++;*/
            /*index = hash(index+i*i);*/
            /*index = hash(index+1);	*/
            index = (index+hash2(key))%TABLE_SIZE;//double hash
    	}
    	if(table[index]->key == key){
        	free(table[index]);
        	table[index] = NULL;
    	}
    	if(index ==start){
        	printf("Key does not exist\n");
        	return;
    	}
    	return;
	}else{
    	printf("Key does not exist\n");
    	return;
	}
}

int main(){
	struct Data *hashTable[20] = {NULL};
	printf("1: Insert\n");
	printf("2: Display\n");
	printf("3: Search\n");
	printf("4: Delete\n");
	printf("------------------\n");
	int option, data;
	int key;
	while(1){
    	scanf("%d",&option);
    	switch(option){
        	case 1:
            	printf("Enter key and data\n");
            	scanf("%d", &key);
            	scanf("%d", &data);
            	insert(key, data, hashTable);
            	break;
        	case 2:
            	display(hashTable);
            	break;
        	case 3:
            	printf("Enter a key to search for\n");
            	scanf("%d", &key);
            	search(hashTable, key);
            	break;
        	case 4:
            	printf("Enter a Key to delete\n");
            	scanf("%d", &key);
            	delete(hashTable, key);
            	break;
        	default:
            	printf("Enter a valid option\n");
            	break;
        	}
    	printf("-------------------------\n");
	}
}

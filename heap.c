#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_util_max(int arr[], int i, int size) {
  int largest = i;

  int leftChild = 2 * i + 1;
  int rightChild = 2 * i + 2;

  if (leftChild < size && arr[leftChild] > arr[largest]) {
    largest = leftChild;
  }

  if (rightChild < size && arr[rightChild] > arr[largest]) {
    largest = rightChild;
  }

  if (largest != i) {
    swap(&arr[largest], &arr[i]);
    heapify_util_max(arr, largest, size);
  }
}

void max_heap(int arr[], int* size){
    for(int i = (*size/2)-1; i>=0; i--){
      heapify_util_max(arr, i, *size);
    }
}

int removeRoot_max(int arr[], int* size){
    int res = arr[0];
    swap(&arr[0], &arr[*size - 1]);
    //arr[*size - 1] = -1000000;
    (*size)--;
    max_heap(arr, size);
    return res;
}

void insert_max(int arr[], int* size, int data){
    (*size)++;
    arr[*size-1] = data;
    max_heap(arr, size);
}

void removeNode_max(int arr[], int* size, int loc){
    swap(&arr[loc], &arr[*size-1]);
    arr[*size - 1] = -1000000;
    (*size)--;
    max_heap(arr, size);
}

/*------------------------*/

void heapify_util_min(int arr[], int i, int size) {
  int smallest = i;

  int leftChild = 2 * i + 1;
  int rightChild = 2 * i + 2;

  if (leftChild < size && arr[leftChild] < arr[smallest]) {
    smallest = leftChild;
  }

  if (rightChild < size && arr[rightChild] < arr[smallest]) {
    smallest = rightChild;
  }

  if (smallest != i) {
    swap(&arr[smallest], &arr[i]);
    heapify_util_max(arr, smallest, size);
  }
}

void min_heap(int arr[], int* size){
    for(int i = (*size/2)-1; i>=0; i--){
      heapify_util_min(arr, i, *size);
    }
}

int removeRoot_min(int arr[], int* size){
    int res = arr[0];
    swap(&arr[0], &arr[*size - 1]);
    //arr[*size - 1] = -1000000;
    (*size)--;
    min_heap(arr, size);
    return res;
}

void display(int arr[], int size){
    for(int i=0; i<size; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void insert_min(int arr[], int* size, int data){
    (*size)++;
    arr[*size-1] = data;
    min_heap(arr, size);
}

void removeNode_min(int arr[], int* size, int loc){
    swap(&arr[loc], &arr[*size-1]);
    arr[*size - 1] = -1000000;
    (*size)--;
    min_heap(arr, size);
}

void heapSort_max(int arr[], int* size){
	max_heap(arr, size);
	int initial_size = *size;
	while(*size > 0){
		removeRoot_max(arr, size);	
	}
	*size = initial_size;
}

void heapSort_min(int arr[], int* size){
	min_heap(arr, size);
	int initial_size = *size;
	while(*size > 0){
		removeRoot_min(arr, size);	
	}
	*size = initial_size;
}

int main(){
    int arr[] = {0,1,2,4,9,5,32,7,8,49};
    int size = 10;
    display(arr, size);
    heapSort_min(arr, &size);
    display(arr, size);
	heapSort_max(arr, &size);
    display(arr, size);
}


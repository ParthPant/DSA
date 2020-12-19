#include <stdio.h>
#include <string.h>

#define RANGE 255

void swap(int *a, int *b){
    int temp =  *a;
	*a = *b;
	*b = temp;
}

void bubblesort(int arr[], int n){
    for(int i=0; i<n-1; i++){
		for(int j=0; j<n-i-1; j++){
		    if(arr[j] > arr[j+1]){
				swap(&arr[j+1], &arr[j]);
			}
		}
	}
}

void insertionsort(int arr[], int n){
    int insert_pos;
	int value;
	
	for(int i=0; i<n; i++){
	    value = arr[i];
	    insert_pos = i;
    	while(insert_pos > 0 && arr[insert_pos-1] > value){
			arr[insert_pos] = arr[insert_pos -1];
			insert_pos -= 1;
    	}
		arr[insert_pos] = value;
    }
}

void selectionsort(int arr[], int n){
    for(int i=0; i<n-1; i++){
		int pos = i;
		for(int j=i+1; j<n; j++){
		    if(arr[j] < arr[pos]){
				pos = j;
			}
		}
		if(pos != i){
		    swap(&arr[i], &arr[pos]);
		}
	}
}

int partition(int arr[], int start, int end){
    int pivot = arr[end];
    int leftwall  = start-1;

    for (int i=start; i<=end-1; i++){
        if(arr[i] < pivot){
            leftwall++;
            swap(&arr[i], &arr[leftwall]);
        }
    }

    swap(&arr[end], &arr[leftwall+1]);

    return leftwall+1;
}

void quicksort(int arr[], int start, int end){
    if(start < end){
        int index = partition(arr, start, end);
        quicksort(arr, start, index-1);
        quicksort(arr, index+1, end);
    }
}

void merge(int arr[], int l, int m, int r) {
  int n1 = m - l + 1;
  int n2 = r - m;

  int L[n1], R[n2];

  for (int i = 0; i < n1; i++)
    L[i] = arr[l + i];
  for (int j = 0; j < n2; j++)
    R[j] = arr[m + 1 + j];

  int i, j, k;
  i = 0;
  j = 0;
  k = l;

  while (i < n1 && j < n2) {
    if (L[i] <= R[j]) {
      arr[k] = L[i];
      i++;
    } else {
      arr[k] = R[j];
      j++;
    }
    k++;
  }

  while (i < n1) {
    arr[k] = L[i];
    i++;
    k++;
  }

  while (j < n2) {
    arr[k] = R[j];
    j++;
    k++;
  }
}

void mergesort(int arr[], int l, int r) {
  if (l < r) {

    int m = l + (r - l) / 2;

    mergesort(arr, l, m);
    mergesort(arr, m + 1, r);

    merge(arr, l, m, r);
  }
}

void countsort(int arr[], int n, int exp){
    int count[10];
    memset(count, 0, sizeof(count));
    int output[n];

    for(int i=0; i<n; i++)
        ++count[(arr[i]/exp)%10];

    for(int i=1; i<10; i++)
        count[i] += count[i-1];
    
    for(int i=n-1; i>=0; i--){
        output[count[(arr[i]/exp)%10]-1] = arr[i];
        --count[(arr[i]/exp)%10];
    }

    for(int i=0; i<n; ++i)
        arr[i] = output[i];
}

int getMax(int arr[], int n){
    int max = arr[0];
    for(int i=0; i<n; i++){
        if(arr[i] > max){
            max = arr[i];
        }
    }
    return max;
}

void radixsort(int arr[], int n){
    int max = getMax(arr, n);
    
    for (int exp = 1; max/exp>0; exp *= 10){
        countsort(arr, n, exp);
    }
}

void shellsort(int arr[], int n){
    for(int gap=n/2; gap>0; gap/=2){
        for(int i=gap; i<n; i++){
            int temp = arr[i];
            int j;
            for(j=i; j>=gap && arr[j-gap]>temp; j-=gap){
                arr[j] = arr[j-gap];
            }
            arr[j] = temp;
        }
    }
}

int main(){
    int arr[10];
	printf("Enter the size of array\n");
	int n;
	scanf("%d", &n);
	printf("Enter the elements of the array\n");
	for(int i=0; i<n; i++){
		scanf("%d", &arr[i]);
	}
	/*bubblesort(arr, n);*/
    mergesort(arr, 0, n-1);
    /*quicksort(arr, 0, n-1);*/
	printf("Sorted array\n");
	for(int i=0; i<n; i++){
		printf("%d\n",arr[i]);
	}
}

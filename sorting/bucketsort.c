#include <stdio.h>
#include <stdlib.h>

#define BUCKETNUM 3

struct bucket{
    int count;
    float *value;
};

void swap(float *a, float *b){
    float temp =  *a;
	*a = *b;
	*b = temp;
}

float getMax(float arr[], int n){
    float max = arr[0];
    for(int i=0; i<n; i++){
        if(max<arr[i])
            max = arr[i];
    }
    return max;
}


float getMin(float arr[], int n){
    float min = arr[0];
    for(int i=0; i<n; i++){
        if(min>arr[i])
            min = arr[i];
    }
    return min;
}

float getBucket(float value, float max, float min){
    float a = (max-min)/BUCKETNUM;
    int b=-1;
    float i;
    for(i=min; i<max; i=i+a){
        if(value<i)
            break; 
        b++;
    }
    return b;
}

void selectionsort(float arr[], int n){
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

void bucketSort(float arr[], int n){
    struct bucket buckets[BUCKETNUM];
    for(int i=0; i<BUCKETNUM; i++){
        buckets[i].count = 0;
        buckets[i].value = (float*)malloc(sizeof(float)*n);
    }

    float max = getMax(arr, n);
    float min = getMin(arr, n);
    for(int i=0; i<n; i++){
        int b = getBucket(arr[i], max, min);
        printf("%f in bucket %d\n", arr[i], b);
        buckets[b].value[buckets[b].count++] = arr[i];
    }

    for(int k=0, i=0; i<3; i++){
        selectionsort(buckets[i].value, buckets[i].count);        
        for(int j=0; j<buckets[i].count; j++){
            arr[k+j] = buckets[i].value[j];
        }
        k += buckets[i].count;
        free(buckets[i].value);
    }
};


int main(){
    float arr[10];
	printf("Enter the size of array\n");
	int n;
	scanf("%d", &n);
	printf("Enter the elements of the array\n");
	for(int i=0; i<n; i++){
		scanf("%f", &arr[i]);
	}
	bucketSort(arr, n);
	printf("Sorted array\n");
	for(int i=0; i<n; i++){
		printf("%f\n",arr[i]);
	}
}

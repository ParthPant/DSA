#include <stdio.h>

void linsearch(int arr[], int n, int d){
    int found = 0;
    for(int i=0; i<n; i++){
        if(arr[i] == d){
            printf("Found element at pos %d\n", i);
            found = 1;
            break;
        }
    }
    if(found != 1){
        printf("Element not found\n");
    }
}

void binarysearch(int arr[], int n, int d){
    int left = 0;
    int right = n-1;

    while(left < right){
        int mid = (left+right)/2;
        if(arr[mid] == d){
            printf("Element found at %d\n", mid);
            return;
        }else if(arr[mid] > d){
            right = mid-1;
        }else if(arr[mid] < d){
            left = mid+1;
        }
    }

    printf("Element not found\n");
}

int main(){
    int arr[10], n;
    printf("Enter the size of the array\n");
    scanf("%d", &n);

    printf("Enter the elements of the array\n");
    for(int i=0; i<n; i++){
        scanf("%d", &arr[i]);
    }

    int d;
    printf("Enter the element to search\n");
    scanf("%d", &d);
    binarysearch(arr, n, d);
}

#include<stdio.h>
#include<stdlib.h>

void MergeTwoArea(int arr[],int left, int mid,int right){
    int fIdx = left;
    int rIdx = mid +1;
    int i;

    int* sortArr = (int*)malloc(sizeof(int)*(right+1));
    int sIdx = left;

    while(fIdx <= mid && rIdx <=right){
        if(arr[fIdx] <= arr[rIdx])
            sortArr[sIdx] = arr[fIdx++]; //두 영역데이터를 비교하며 arr에 옮김
        else  
            sortArr[sIdx] = arr[rIdx++];
    }
    if(fIdx > mid){ //배열의 앞부분이 모두 arr에 옮겨졌다면
        for(i = rIdx; i<=right;i++,sIdx++){
            sortArr[sIdx] = arr[i]; //뒷부분을 arr에 그대로 옮김
        }
    }else{ //뒷부분이 모두 arr에 옮겨졌다면
        for(i = fIdx; i<=mid;i++,sIdx++){
            sortArr[sIdx] = arr[i]; //앞부분을 arr에 그대로 옮김
        }
    }
    for(i=left; i<=right;i++){
        arr[i] = sortArr[i];
    }
    free(sortArr);
}

void MergeSort(int arr[],int left,int right){
    int mid;
    if(left < right){
        mid = (left+right)/2;
        MergeSort(arr,left,mid); //둘로 나눠서 각각 정렬
        MergeSort(arr,mid+1,right);
        MergeTwoArea(arr,left,mid,right);
    }
}
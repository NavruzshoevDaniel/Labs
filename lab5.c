#include <stdio.h>
#include <stdlib.h>

void outPut(int *arr,int n){

    for(int i=0; i<n;i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
}

void swap(int i, int j, int *arr){
    int c;
    c = arr[i];
    arr[i] = arr[j];
    arr[j] = c;
}

void siftup(int i, int *arr){
    while((i > 0) && ((arr[(i - 1) / 2]) < arr[i])){
        swap(i, (i - 1) / 2, arr);
        i = (i - 1) / 2;
    }
}

void insert(int count, int *arr, int  i){
    arr[i] = count;
    siftup(i,arr);
}

void shifdown(int *arr,int i,int N){
    int j=i;
    while ((2*i+1) < N){

        if(arr[2*i+1]>arr[j])
            j=2*i+1;

        if ((2*i+2<N)&&(arr[2*i+2]>arr[j]))
            j=2*i+2;

        if (i==j)
            break;
        swap(i,j,arr);
        i=j;


    }
}



int main() {
    long N=0;
    int count, *arr;
    scanf("%ld", &N);
    arr = (int*)malloc(N * sizeof(int));
    scanf("%d",&arr[0] );
    for (int i = 1; i < N; i++){
        scanf("%d", &count);
        insert(count, arr, i);
    }
    int l=N;
    for (int i=0; i<N;i++){
        int a=arr[0];
        arr[0]=arr[l-1];
        arr[l-1]=a;
        shifdown(arr,0,l-1);
        l--;
    }
    outPut(arr,N);
    free(arr);
    return 0;
}

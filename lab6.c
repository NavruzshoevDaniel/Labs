#include <stdio.h>
void outPut(int arr[],int n){

    for(int i=0; i<n;i++){
        printf("%d ",arr[i]);
    }
}

void quickSort(int arr[], int l, int r){
    int i=l,j=r;
    int mid=arr[(l+r)/2];

            do{
                while (arr[i] < mid)
                    i++;
                while (arr[j] > mid)
                    j--;
                if (i <= j){
                    int c=arr[i];
                    arr[i]=arr[j];
                    arr[j]=c;
                    i++;
                    j--;
                }
            } while (i<=j);

            if (l < j) quickSort(arr,l,j);
            if (i < r) quickSort(arr,i,r);

}

int main() {
    int N=0;
    scanf("%d",&N);
    int arr[N];
     for (int i=0;i < N; i++){
         scanf("%d",&arr[i]);
     }
     quickSort(arr,0,N-1);
     outPut(arr,N);

    return 0;
}

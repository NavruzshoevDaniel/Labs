#include <stdio.h>
#include <string.h>
void bubbleSort(int a[], int n,int l)
{
    int j, nn;

    do {
        nn = 0;
        for (j = l+1; j < n; ++j)
            if (a[j-1] > a[j]) {
                int c=0;
                c=a[j-1];
                a[j-1]=a[j];
                a[j]=c;
                nn = j;
            }
        n = nn;
    } while (n);
}

int lenMas(int count){
    int g=count,i=0;
    while (g!=0){
        g/=10;
        i++;
    }
    return i;
}

void createMas(char str[10], int mas[],int len){
    for (int i=0; i < len; i++){
        mas[i] = str[i] - '0';
    }
}

void outputMas(int mas[],int n){
    for (int i=0; i<n;i++){
        printf("%d",mas[i]);
    }
}

int isSort(int mas[], int len){
    int count=0;
    for(int i = 0; i<len-1; i++ ){
        if(mas[i]>mas[i+1])
            count++;
    }
    if(count==len)
        return 0;

    return 1;

}

int checkBadInput(int *mas,int n){
    int arr[10]={0};
    for( int i = 0; i < n; i++ ){
        arr[mas[i]]++;
        if(arr[mas[i]]>1)
            return 1;
    }
    return 0;

}

void functionDecstr(int mas[],int len,int p){
    int i=0,check=0;
    int s=isSort(mas,len);
    while((i<p) && (s)){
        for (int j = len-1; j >= 0; j--){
            for (int k = j - 1 ; k >= 0; k--) {
                if(mas[j]>mas[k]) {
                    int c=mas[j];
                    mas[j]=mas[k];
                    mas[k]=c;
                    bubbleSort(mas,len,k+1);
                    outputMas(mas,len);
                    check++;
                    break;
                }
            }
            if(check){
                check--;
                break;
            }
        }
        i++;
        printf("\n");
    }
}

int main() {
    int p;
    char str[11];
    scanf("%s",str);
    int len = strlen(str);
    int mas[len];
    createMas(str, mas,len);
    scanf("%d",&p);
    if (checkBadInput(mas,len)){
        printf("bad input");
        return 0;
    }
    for (int i = 0; i < len; i++) {
        if ((mas[i] < 0) || (mas[i] > 9)) {
            printf("bad input");
            return 0;
        }
    }
    functionDecstr(mas,len,p);
    return 0;
}

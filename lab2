#include <stdio.h>
#include <string.h>
void fillTable(unsigned char str[],unsigned char word[]){
    int j=strlen(word);
    for(int i=0; i<strlen(word)-1;i++){
        int c=word[i];
        str[c]=j-1-i;
    }
}

int findString( unsigned char strASCII[], unsigned char str[], unsigned char word[], int ind,int sdvig){

    int i=strlen(word)-1,j=i;

    while (i < strlen(str)){
        int k=j,l=i;
        printf("%d ", i+1+ind);
        while((k>0) && (str[l]==word[k])){
            k--;
            l--;
            printf("%d ",l+1 + ind);
        }
        sdvig=strASCII[str[i]];
        i+=strASCII[str[i]];
    }

    return sdvig;
}

int main() {
    unsigned char str[255]={0},word[255]={0};
    unsigned char strASCII[255]={0};
    gets(word);
    memset(strASCII,strlen(word),255);
    fillTable(strASCII,word);
    int count = 0, ind = 0,sdvig=0;
    char k = 0;

    while ((k = getchar()) != EOF){
        str[count++] = k;
        if (count == strlen(word)){
            sdvig=findString(strASCII,str,word,ind,sdvig);
            ind+=sdvig;
            memmove(str,str+sdvig,strlen(str)-sdvig);
            count-=sdvig;
        }
    }
    return 0;
}

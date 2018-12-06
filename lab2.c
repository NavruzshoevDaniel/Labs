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
    fgets(word,sizeof(word),stdin);
    word[strlen(word) - 1] = 0;
    if (strlen(word) > 0)
      memset(strASCII,strlen(word),255);
    fillTable(strASCII,word);
    int count = 0, ind = 0,sdvig=0;
    fgets(str,strlen(word)+1,stdin);

        if (strlen(str) == strlen(word)){
            sdvig=findString(strASCII,str,word,ind,sdvig);
            ind+=sdvig;
            memmove(str,str+sdvig,strlen(str)-sdvig);

        }
    while(1){
        fgets(str+(strlen(str)-sdvig),sdvig+1,stdin);
        if(!feof(stdin)){
            sdvig=findString(strASCII,str,word,ind,sdvig);
            ind+=sdvig;
            memmove(str,str+sdvig,strlen(str)-sdvig);
        } else
            return 0;
    }
    return 0;
}

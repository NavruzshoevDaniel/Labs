#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

int BaseorNot(const char let){
    if ( (let>='A' && let<='Z') || (let>='a' && let<='z') ||
         (let>='0' && let<='9') || (let=='+') || (let=='/') || (let=='='))
        return 1;
    else{
        return 0;
    }
}

int idBase64(const char *alpha, char letter){
    for(int i=0; i < 64; i++)
        if (letter==alpha[i])
            return i;
    return -1;
}

void decode(FILE *in, FILE *out, const char *alpha,int notBase){
    unsigned char buf[4]={0};
    char letter;
    int i=0;
    while ((letter=fgetc(in))!=EOF){
        if (BaseorNot(letter))
            buf[i++]=letter;
        else if (notBase==0){
            printf("%s","Error. Input file has characters not from Base64.\n");
            exit(0);
        }
        if (buf[3]=='=') i--;
        if (buf[2]=='=') i--;
        if(i==4){
            if(idBase64(alpha,buf[3])==-1) i-=1;
            if(idBase64(alpha,buf[2])==-1) i-=1;
            fprintf(out,"%c",idBase64(alpha,buf[0])<<2 | idBase64(alpha,buf[1])>>4);
            fprintf(out,"%c",idBase64(alpha,buf[1])<<4 | idBase64(alpha,buf[2])>>2);
            fprintf(out,"%c",idBase64(alpha,buf[2])<<6 | idBase64(alpha,buf[3]));
            i=0;
            memset(buf,0,4);
        }
    }
    if (i==3){
        fprintf(out,"%c",idBase64(alpha,buf[0])<<2 | idBase64(alpha,buf[1])>>4);
        fprintf(out,"%c",idBase64(alpha,buf[1])<<4 | idBase64(alpha,buf[2])>>2);
    }
    if(i==2){
        fprintf(out,"%c",idBase64(alpha,buf[0])<<2 | idBase64(alpha,buf[1])>>4);
    }
}

int linebreak(FILE *out,int c, const int line){
    if(c==line) {
        fprintf(out,"%c",'\n');
        return 0;
    }
    c++;
    return c;
}

void encode(FILE *in, FILE *out, const char *alpha,const int line){
    unsigned char buf[3]={0};
    int letter;
    int i=0,c=0;
    while ((letter=fgetc(in))!=EOF){
            buf[i++]=letter;
        if(i==3){
            fprintf(out,"%c",alpha[buf[0]>>2]);
            c=linebreak(out,c,line);
            fprintf(out,"%c",alpha[(buf[0]<<4) & 0x3F | buf[1]>>4]);
            c=linebreak(out,c,line);
            fprintf(out,"%c",alpha[(buf[1]<<2) & 0x3F | buf[2]>>6]);
            c=linebreak(out,c,line);
            fprintf(out,"%c",alpha[(buf[2]) & 0x3F]);
            c=linebreak(out,c,line);
            i=0;
            memset(buf,0,3);
        }
    }
    if(i==2){
        fprintf(out,"%c",alpha[buf[0]>>2]);
        c=linebreak(out,c,line);
        fprintf(out,"%c",alpha[(buf[0]<<4) & 0x3F | buf[1]>>4]);
        c=linebreak(out,c,line);
        fprintf(out,"%c",alpha[(buf[1]<<2) & 0x3F | buf[2]>>6]);
        c=linebreak(out,c,line);
        fprintf(out,"%c",'=');
        c=linebreak(out,c,line);
    }
    if(i==1){
        fprintf(out,"%c",alpha[buf[0]>>2]);
        c=linebreak(out,c,line);
        fprintf(out,"%c",alpha[(buf[0]<<4) & 0x3F | buf[1]>>4]);
        c=linebreak(out,c,line);
        fprintf(out,"%c",'=');
        c=linebreak(out,c,line);
        fprintf(out,"%c",'=');
        c=linebreak(out,c,line);
    }
}

int main(int argc, char **argv) {
    char alpha[]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    char *infile=argv[argc-2];
    char *outfile=argv[argc-1];
    FILE *in= fopen(infile, "rb");
    FILE *out= fopen(outfile, "w");
    int line=-1;
    int opt=0,di=-1,e=0,f=0,d=0,i=0,ef=-1;
    if (!strcmp(argv[1],"--help"))
        printf(" -e encode function\n -d decode function\n -d -i ignore symbols not from Base64\n");
    while ((opt=getopt(argc,argv,"edif:"))!=-1){
        switch (opt){
            case 'e':
                e=1;
                ef=0;
                break;
            case 'f':
                if(optarg!=NULL){
                    sscanf(optarg, "%d", &line);
                   ef=1;
                } else {
                    printf("Error: -f without count");
                    exit(0);
                }
                    f=1;
                break;
            case 'd':
                di=0;
                d=1;
                break;
            case 'i':
                di=1;
                i=1;
                break;
            case '?': printf("Use: --help\n");
        }

    }
   if((e || f) && (d || i) || (f==1 && e==0) || (d==0 && i==1)){
       printf("Error: too many parametrs");
       exit(0);
   }
    if (ef==0)
       encode(in,out,alpha,line);
    else if(ef==1)
        encode(in,out,alpha,line-1);
    if(di==1)
        decode(in,out,alpha,1);
    else if(di==0)
        decode(in,out,alpha,0);
    fclose(in);
    fclose(out);
    return 0;
}

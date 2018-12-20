#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

struct stack {
    int elem[1000];
    int top;
};

void push(struct stack *stk, int f) {
    if(stk->top < 1000) {
        stk->elem[stk->top] = f;
        stk->top++;
    }
}

int pop(struct stack *stk) {
    int elem;
    if((stk->top) > 0) {
        stk->top--;
        elem = stk->elem[stk->top];
        return(elem);
    } else {
        return 0;
    }
}

int stkTop(struct stack *stk) {
    if((stk->top) > 0)
        return( stk->elem[stk->top-1]);
    else{
        printf("syntax error");
        exit(0);
    }
}

int isempty(struct stack *stk) {
    if((stk->top) == 0)    return(1);
    else return(0);
}

struct stackChar {
    char elem[1000];
    int top;
};

void pushChar(struct stackChar *stk, char f) {
    if(stk->top < 1000) {
        stk->elem[stk->top] = f;
        stk->top++;
    }
}

int popChar(struct stackChar *stk) {
    char elem;
    if((stk->top) > 0) {
        stk->top--;
        elem = stk->elem[stk->top];
        return(elem);
    } else {
        return 0;
    }
}

int stkTopChar(struct stackChar *stk) {
    if((stk->top) > 0) {
        return( stk->elem[stk->top-1]);
    } else {
        return 0;
    }
}

int isemptyChar(struct stackChar *stk) {
    if((stk->top) == 0)    return(1);
    else return(0);
}

int checkIC(char k){
    if((k >= '0')&&(k <= '9'))
        return k;
    else return -1;
}

int checkFunOrNot(int k){
    if((k=='+')||(k=='-')||(k=='+')||(k=='*')||(k=='/')||(k=='(')||(k==')'))
        return 1;
    else return 0;
};

int priority(char ch){
    if((ch=='+')||(ch=='-'))
        return 1;
    else if((ch=='*')||(ch=='/'))
        return 2;
    else return 0;
}

void calculate(struct stack *stack, char k) {
    int a=0,b=0;

    if( !isempty(stack) )
        a=pop(stack);
    else{
        printf("syntax error");
        exit(0);
    }


    if( !isempty(stack) )
        b=pop(stack);
    else{
        printf("syntax error");
        exit(0);
    }

    if(( k=='/' ) && (a == 0) ){
        printf("Division by zero");
        exit(0);
    }

    switch (k){
        case '+':
            push(stack,a+b);
            break;
        case '-':
            push(stack,b-a);
            break;
        case '*':
            push(stack,a*b);
            break;
        case '/':
            push(stack,b/a);
            break;
    }


}


int main() {
    struct stack stk;
    struct stackChar stkChar;
    char k=0,x=0;
    int value=0,i=0,bracket=0,emptbrack=0;
    char digit[1000]={0};
    stk.top=0;
    stkChar.top=0;

    while( (k=getchar()) != EOF) {

        if (isdigit(k)) {
            digit[i++] = k;

            while (isdigit(k = getchar()) != 0) {
                digit[i++] = k;
            }
            push(&stk, atoi(digit));
            memset(digit, 0, i);
            i = 0;
            emptbrack++;
        }

        if (k == '(') {
            emptbrack=0;
            pushChar(&stkChar, k);
            bracket++;
            continue;

        } else if (k == ')') {
            bracket--;
            if( ( bracket >= 0 ) && ( emptbrack > 0 ) )
                while (stkTopChar(&stkChar) != '(') {
                    calculate(&stk, popChar(&stkChar));
                }
            else{
                printf("syntax error");
                return 0;
            }
            popChar(&stkChar);
            continue;

        } else if ((k == '+') || (k == '-') || (k == '/') || (k == '*')) {
            while ((!isemptyChar(&stkChar)) && (priority(k) <= priority(stkTopChar(&stkChar)))) {
                calculate(&stk, popChar(&stkChar));
            }
            pushChar(&stkChar, k);
            continue;

        } else if ((k != EOF) && (k != '\n'))
            printf("syntax error");

        if ((!isempty(&stk)) && (k == '\n')) {
            while (!isemptyChar(&stkChar))
                calculate(&stk, popChar(&stkChar));
        }

        if(bracket==0)
            printf("%d ", stkTop(&stk));
        else
            printf("syntax error");
        return 0;


    }

    return 0;
}


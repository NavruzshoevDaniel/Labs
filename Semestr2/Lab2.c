#include <stdio.h>
#include <stdlib.h>

struct avltree {
    int key;
    unsigned char height;
    struct avltree* left;
    struct avltree* right;
};

unsigned char height(struct avltree *p)
{
    return p?p->height:0;
}

int bfactor(struct avltree* p)
{
    return height(p->right)-height(p->left);
}

void fixheight(struct avltree* p)
{
    unsigned char hl = height(p->left);
    unsigned char hr = height(p->right);
    p->height = (hl>hr?hl:hr)+1;
}

struct avltree* rotateright(struct avltree* p)
{
    struct avltree* q = p->left;
    p->left = q->right;
    q->right = p;
    fixheight(p);
    fixheight(q);
    return q;
}

struct avltree* rotateleft(struct avltree* q)
{
    struct avltree* p = q->right;
    q->right = p->left;
    p->left = q;
    fixheight(q);
    fixheight(p);
    return p;
}

struct avltree* balance(struct avltree* p)
{
    fixheight(p);
    if( bfactor(p)==2 )
    {
        if( bfactor(p->right) < 0 )
            p->right = rotateright(p->right);
        return rotateleft(p);
    }
    if( bfactor(p)==-2 )
    {
        if( bfactor(p->left) > 0  )
            p->left = rotateleft(p->left);
        return rotateright(p);
    }
    return p;
}

struct avltree* insert(struct avltree* p, int k)
{
        if (!p) {
            p=malloc(sizeof(struct avltree));
            p->key = k;
            p->left = NULL;
            p->right = NULL;
            p->height = 1;
            return p;
        }

    if( k<p->key )
        p->left = insert(p->left,k);
    else
        p->right = insert(p->right,k);
    return balance(p);
}
void freeavl(struct avltree *tree){
    if(tree->right)
        freeavl(tree->right);
    if(tree->left)
        freeavl(tree->left);
    free(tree);
}

int main() {
    struct avltree *tree=NULL;
    int n=0,key=0;
    scanf("%d",&n);

    if (n==0){
        printf("0");
        return 0;
    }

    for (int i = 0; i < n; ++i) {
        scanf("%d",&key);
        tree=insert(tree,key);
    }
    printf("%d",height(tree));
    freeavl(tree);
    return 0;
}

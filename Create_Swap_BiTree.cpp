#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef int Status;
typedef char ElemType;

typedef struct BiNode
{
    ElemType data;
    struct BiNode *lchild;
    struct BiNode *rchild;
}BiNode, *BiTree;

//通过逐个输入结点和或者空格来创建二叉树，思想是先序遍历的递归算法。
Status CreateBiTree (BiTree &T, char s[], int &i)
{
    if (s[i]=='\0') return OK;
    else i++;
    // T = (BiTree) malloc (sizeof(BiNode));
    if (s[i]==' ') T = NULL;
    else
    {
        T = (BiNode *) malloc (sizeof(BiNode));
        T->data = s[i];
        CreateBiTree (T->lchild, s, i);
        CreateBiTree (T->rchild, s, i);
    }
    return OK;
}

Status ReverseTree (BiTree &T)
{
    BiTree temp = NULL;
    if (!T) return OK;
    else
    {
        temp = T->lchild;
        T->lchild = T->rchild;
        T->rchild = temp;
        ReverseTree (T->lchild);
        ReverseTree (T->rchild);
    }
    return OK;
}

Status PrintTree (BiTree &T)//用递归法先序打印二叉树
{
    BiNode *p = T;
    if (p) printf("%c ",p->data);
    else 
    {
        printf(" ");
        return OK;
    }

    PrintTree(p->lchild);
    PrintTree(p->rchild);
    return OK;
}

int main()
{
    ElemType s[1000];
    int i = -1;
    printf("范昊翔2019051364\n请输入需要构建的二叉树：\n");
    gets(s);
    BiTree T;
    CreateBiTree(T, s, i);
    PrintTree(T);
    printf("\n");
    ReverseTree(T);
    PrintTree(T);
    return 0;
}
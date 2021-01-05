#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ALPHA_RE 3
//ALPHA_RE定义的是n/m的倒数，m为表长，n为元素个数 m = ALPHA_RE * n，即表长由元素个数决定
#define NAME_LEN 20
#define TEL_LEN 20
#define MAX_DATA 15
typedef struct LLNode//链表中的结点
{
    char *name;
    char *telnum;
    LLNode *next;
}LLNode;

typedef LLNode *ElemType;

typedef struct
{
    int length;
    ElemType *elem;//elem域存了很多个ElemType元素，ElemType是一个LLnode的指针
}HashTable;


int HashFunction (char *name, int m)//传入名字和表长，返回其在哈希表的位置
{
    int x = int(name[0]);
    int y = int(name[1]);
    int result = ((x + y) - 1) % m;
    return result; 
}

void InitHashTable (HashTable &T)
{
    printf("一共想要录入几个人的电话？\n");
    scanf("%d",&T.length);
    T.elem = (ElemType*) malloc (sizeof(ElemType)*T.length*ALPHA_RE);
    for (int i=0; i<T.length*ALPHA_RE; i++)
    {
        T.elem[i] = NULL;
    }
}

void Insert (HashTable &T)
{
    for (int i=0; i<T.length; i++)
    {
        LLNode* node= (LLNode*) malloc (sizeof(LLNode));
        printf("请输入第%d个人的拼音\n",i+1);
        node->name = (char*) malloc (sizeof(char)*NAME_LEN);
        fflush(stdin);
        gets(node->name);
        printf("请输入第%d个人的电话\n",i+1);
        node->telnum = (char*) malloc (sizeof(char)*TEL_LEN);
        fflush(stdin);
        gets(node->telnum);
        node->next = NULL;
        int c = HashFunction(node->name, T.length*ALPHA_RE);
        ElemType p = T.elem[c];
        if (p==NULL) T.elem[c] = node;
        else 
        {
            while(p->next!=NULL) p = p->next;
            p->next = node;
        }
    }
}

void Search (HashTable T)
{
    printf("请输入你要查找的人名\n");
    char name[20];
    fflush(stdin);
    gets(name);
    int c = HashFunction(name,T.length*ALPHA_RE);
    LLNode *p = T.elem[c];
    while (p!=NULL && strcmp(p->name,name)!=0) p = p->next;
    if (!p) printf("电话簿中并没有此记录！\n");
    else if (strcmp(p->name,name)==0) printf("他的电话号码是%s\n",p->telnum);
    else printf("电话簿中并没有此记录！\n");
}

int main()
{
    printf("欢迎来到通讯录管理系统  范昊翔 2019051364\n");
    printf("---------------------------------------\n");
    while (1)
    {
        printf("请输入你想要的功能\n");
        int choice;
        printf("1.输入   2.查找   0.退出\n");
        scanf("%d",&choice);
        HashTable T;
        if (choice == 0) return 0;
        else if (choice == 1)
        {
            InitHashTable (T);
            Insert(T);
        }
        else if (choice == 2) Search(T);
        else printf("请重新输入\n");
    }

    system("pause");
    return 0;
}
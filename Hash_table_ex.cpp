#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ALPHA_RE 3
//ALPHA_RE�������n/m�ĵ�����mΪ����nΪԪ�ظ��� m = ALPHA_RE * n��������Ԫ�ظ�������
#define NAME_LEN 20
#define TEL_LEN 20
#define MAX_DATA 15
typedef struct LLNode//�����еĽ��
{
    char *name;
    char *telnum;
    LLNode *next;
}LLNode;

typedef LLNode *ElemType;

typedef struct
{
    int length;
    ElemType *elem;//elem����˺ܶ��ElemTypeԪ�أ�ElemType��һ��LLnode��ָ��
}HashTable;


int HashFunction (char *name, int m)//�������ֺͱ����������ڹ�ϣ���λ��
{
    int x = int(name[0]);
    int y = int(name[1]);
    int result = ((x + y) - 1) % m;
    return result; 
}

void InitHashTable (HashTable &T)
{
    printf("һ����Ҫ¼�뼸���˵ĵ绰��\n");
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
        printf("�������%d���˵�ƴ��\n",i+1);
        node->name = (char*) malloc (sizeof(char)*NAME_LEN);
        fflush(stdin);
        gets(node->name);
        printf("�������%d���˵ĵ绰\n",i+1);
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
    printf("��������Ҫ���ҵ�����\n");
    char name[20];
    fflush(stdin);
    gets(name);
    int c = HashFunction(name,T.length*ALPHA_RE);
    LLNode *p = T.elem[c];
    while (p!=NULL && strcmp(p->name,name)!=0) p = p->next;
    if (!p) printf("�绰���в�û�д˼�¼��\n");
    else if (strcmp(p->name,name)==0) printf("���ĵ绰������%s\n",p->telnum);
    else printf("�绰���в�û�д˼�¼��\n");
}

int main()
{
    printf("��ӭ����ͨѶ¼����ϵͳ  ����� 2019051364\n");
    printf("---------------------------------------\n");
    while (1)
    {
        printf("����������Ҫ�Ĺ���\n");
        int choice;
        printf("1.����   2.����   0.�˳�\n");
        scanf("%d",&choice);
        HashTable T;
        if (choice == 0) return 0;
        else if (choice == 1)
        {
            InitHashTable (T);
            Insert(T);
        }
        else if (choice == 2) Search(T);
        else printf("����������\n");
    }

    system("pause");
    return 0;
}
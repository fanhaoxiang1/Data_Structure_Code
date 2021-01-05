#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LIST_INCREMENT 10
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define DEFAULT 1
typedef int Status;

typedef struct Score
{
    float digital_logic;
    float data_structure;
    float graph_algebra;
    float probability_theory;
}Score;

typedef struct Student
{
    long no;
    char name[20];
    Score score;
}Student, ElemType;

typedef struct ManagementSystem
{
    ElemType *elem;
    int length;
    int size;
}SqList;

Status WhetherMoreSize (SqList &S)
{
    if (S.size <= S.length)
    {
        ElemType *base = (ElemType *) realloc (S.elem,
        sizeof(ElemType)*(S.size+LIST_INCREMENT));
        if (!base) exit(OVERFLOW);
        S.size += LIST_INCREMENT;
        S.elem = base;
    }
    return OK;
}
Status InitSqList (SqList &S)
{
    char y;
    printf("�˲���������������ϵͳ����ͷ��ʼ¼�룬ȷ��������y\n");
    fflush(stdin);
    y = getchar();
    if (y != 'y')
    {
        printf("����ȡ��\n");
        return ERROR;
    }
    int init_list_size;
    printf("������Ŀǰѧ��������\n");
    scanf("%d",&init_list_size);
    S.elem = (ElemType *) malloc (sizeof(ElemType) * init_list_size * 2);
    //Ϊ�˱������Ƿ��䣬�����һ��Ŀռ�
    if (!S.elem) exit(OVERFLOW);
    S.length = 0;
    S.size = 2 * init_list_size;
    printf("��ʼ���ɹ���\n");
    return OK;
}
Status Averange(SqList S, int index)
{
    float averange;
    averange =(S.elem[index].score.digital_logic +
        S.elem[index].score.data_structure + S.elem[index].score.graph_algebra +
        S.elem[index].score.probability_theory) / 4;
    printf("ƽ����%.2f",averange);
    return OK;
}

Status GetOneInSqList (SqList S, int index)
{
    printf("%d %ld %s\n�����߼�:%.2f���ݽṹ:%.2fͼ��:%.2f������:%.2f ",index+1, S.elem[index].no,
        S.elem[index].name, S.elem[index].score.digital_logic,
        S.elem[index].score.data_structure, S.elem[index].score.graph_algebra,
        S.elem[index].score.probability_theory);
    Averange(S, index);
    printf("\n");
    return OK;
}
Status PutOneInSqList (SqList &S,int x)
{
    
    printf("ѧ�ź������ǣ�\n");
    scanf("%ld",&S.elem[x].no);
    fflush(stdin);
    scanf("%s",&S.elem[x].name);
    printf("�������������������߼������ݽṹ��ͼ�ۡ������۵ķ���\n");
    scanf("%f%f%f%f",&S.elem[x].score.digital_logic,
    &S.elem[x].score.data_structure,&S.elem[x].score.graph_algebra,
    &S.elem[x].score.probability_theory);
    S.length += 1;
    return OK;
}
Status PutInSqList (SqList &S)
{
    char y;
    printf("��ʼ¼�룺\n");
    while(1)
    {
        WhetherMoreSize(S);//�ж������Ƿ����
        printf("��%d��ͬѧ��",S.length+1);
        PutOneInSqList(S,S.length);
        printf("¼����ɣ��Ƿ������¸�ͬѧ����������y\n");
        fflush(stdin);
        y = getchar();
        if (y !='y')
        break;
    }
    return OK;
}

Status GetFromSqlist (SqList S)
{
    printf("ȫ��ɼ���\n");
    int index = 0;
    while(index < S.length)
    {
        GetOneInSqList(S,index);
        index++;
    }
    printf("����Ϊȫ��ɼ�\n");
    return OK;
}

Status InsertSqList(SqList &S)
{
    int x;
    printf("��Ҫ�ڵڼ���λ�ò��룿");
    scanf("%d",&x);
    WhetherMoreSize(S);
    int p = 0;
    if (p>S.length) exit(ERROR);
    int q = S.length;
    while(q>p)
    {
        S.elem[q] = S.elem[q-1];
        q--;
    }
    PutOneInSqList(S,x-1);
    return OK;
}

Status SearchInSqList(SqList S)
{
    printf("����Ҫ���ҵĹؼ����ǣ�");
    char search[20];
    fflush(stdin);
    scanf("%s",search);
    int p = 0;
    int flag = 0;
    while (flag == 0 && p<S.length)
    {
        if (strcmp(S.elem[p].name, search) == 0 || atof(search)==S.elem[p].no)
        flag = 1;
        else    p++;
    }
    if (p>=S.length)
    {
        printf("û�н����");
        return OK;
    }
    GetOneInSqList(S,p);
    return OK;
}

Status DeleteOneInSqList(SqList &S)
{
    int i;
    printf("��Ҫɾ����һ����?");
    scanf("%d",&i);
    int p = i;
    while(p<=S.length)
    {
        S.elem[p-1] = S.elem[p];
        p++;
    }
    S.length--;
    return OK;
}
Status Menu(SqList &S)
{
    system("cls");
    int choice;
    printf("           �ɼ�����ϵͳprod.by�����2019051364\n");
    printf("--------------------------------------------------------------\n");
    printf("1.�ɼ�¼�� 2.����ɼ����ÿ�ſγɼ� 3.����ɼ� 4.ɾ���ɼ� 5.��ѯ\n");
    printf("��Ҫִ���Ǹ�����?     0.�˳�\n");
    scanf("%d",&choice);
    switch (choice)
    {
    case 0:
        printf("��л����ʹ��!");
        exit(OK);
        break;
    case 1:
        if(InitSqList(S)==0)
        break;
        PutInSqList(S);
        break;
    case 2:
        GetFromSqlist(S);
        system("pause");
        break;
    case 3:
        InsertSqList(S);
        break;
    case 4:
        DeleteOneInSqList(S);
        break;
    case 5:
        SearchInSqList(S);
        system("pause");
    default:
        break;
    }
    return OK;
}

int main()
{
    SqList myclass;
    while (1) Menu(myclass);
    return 0;
}
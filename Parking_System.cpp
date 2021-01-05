#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LIST_INIT_SIZE 10
#define LIST_INCREMENT 10
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define DEFAULT 1
typedef int Status;

//���峵����Ϣ�����ݽṹ
typedef struct Car
{
    char id[20];
    int arrive;//����ʱ��
    int leave;//�뿪ʱ��
    int pos;//Ӧͣ����,1��ʾͣ������0��ʾ���
    int no;//λ�ñ��
}Car;
typedef Car ElemType;

//�������֣�����˳��ջ����ʽ����
typedef struct SqStack
{
    ElemType *top;
    ElemType *base;
    int stacksize;
}SqStack;

Status InitStack (SqStack &S)
{
    S.base =NULL;
    S.top = NULL;
    S.base = (ElemType *) malloc (sizeof(ElemType) * LIST_INIT_SIZE);
    if (!S.base) exit(OVERFLOW);
    S.top = S.base;
    S.stacksize = LIST_INIT_SIZE;
    return OK;
}

Status Push(SqStack &S, ElemType &e, int &index)
{
    
    if (S.top-S.base==S.stacksize){
        S.base = (ElemType *) realloc (S.base, sizeof(ElemType) * (S.stacksize+LIST_INCREMENT));
        if (!S.base) exit(OVERFLOW);
        S.top = S.base + S.stacksize;
        S.stacksize += LIST_INCREMENT;
    }
    
    *S.top++ = e;
    index = S.top - S.base;
    return OK;
}

Status Pop(SqStack &S, ElemType &e)
{
    if(S.top <= S.base) return ERROR;
    else e = *--S.top;
    return OK;
}

Status DestroyStack(SqStack &S)
{
    free(S.base);
    return OK;
}

//ͨ����⳵�ƺ��жϳ��Ƿ���ͣ������
Status WhetherInStack(SqStack &S, char id1[], int &reply)
{
    int ind;//��ʱ����������
    reply = 0;//1���ڣ�0�ǲ���
    ElemType *p = S.base;
    while(p <= S.top)
    {
        if (strcmp(id1,p->id)==0) 
        {reply = 1; break;}
        p++;
    }
    return OK;
}

typedef struct Node
{
    ElemType data;
    struct Node *next;
}Node;

typedef struct LQueue
{
    Node *front;
    Node *rear;
    int length;
}LQueue;

Status InitLQueue (LQueue &L)
{
    L.front = (Node *) malloc (sizeof(ElemType));
    if (!L.front) exit(OVERFLOW);
    L.rear = L.front;
    L.front -> next = NULL;
    L.length = 0;
    return OK;
}

Status EnQueue (LQueue &L, ElemType &e, int &index)
{
    Node *node;
    node = (Node*) malloc (sizeof(ElemType));
    if (!node) exit(OVERFLOW);
    node->data = e;
    node->next = NULL;
    L.rear -> next = node;
    L.rear = node;
    index = ++L.length;
    return OK;
}

Status Dequeue (LQueue &L, ElemType &e)
{
    if (L.front == L.rear) return ERROR;
    Node *node = L.front->next;
    e = node->data;
    L.front ->next = node->next;
    if (L.rear == node) L.rear = L.front;
    L.length --;
    //free(node);
    return OK;
}

Status DestroyQueue (LQueue &L)
{
    while(L.front)
    {
        L.rear = L.front->next;
        free(L.front);
        L.front = L.rear;
    }
    return OK;
}

//�������̴���
Status CarIn (SqStack &S, LQueue &Q, int n, Car &car)
{
    printf("��ӭ���٣���������ĳ��ƺţ�\n");
    fflush(stdin);
    scanf("%s",car.id);
    printf("��������ĵ���ʱ��\n");
    scanf("%d",&car.arrive);
    if (S.top - S.base < n) 
    {
        car.pos = 1;
        Push(S, car, car.no);
    }
    else
    {
        car.pos = 0;
        EnQueue(Q, car, car.no);
    }
    return OK;
}

//������Ϣ��ʾ
Status CarInformationOut(Car &car)
{
    printf("ͣ��λ��");
    if (car.pos == 1) printf("ͣ����");
    else printf("���");
    printf(" %d��λ\n",car.no);
    return OK;
}

//ȷ����car�ĳ����Լ���ͣ����ʱ���Ժ󣬳���ͣ������
Status CarOut(SqStack &park, SqStack &wait, LQueue &Q, char id1[], int out, Car &car)
{
    int index = 0, temp;//index������¼��ջ����;temp��ʱ����������
    int i = 0;
    Car carnow = {NULL};
    while(1)//�ú���ĳ�Ϊ�˳���λ��
    {
        Pop(park, carnow);
        if (strcmp(id1,carnow.id)==0) break;
        Push(wait, carnow, index);
    }
    car = carnow;
    car.leave = out;
    //Push(park, carnow, temp);
    while(i<index)//����ʻ��
    {
        Pop(wait, carnow);
        Push(park, carnow, temp);
        i++;
    }
    if (Q.length!=0)//�ö����е�һ������ͣ����
    {
        Dequeue(Q, carnow);
        carnow.pos = 1;
        carnow.arrive = out;
        Push(park, carnow, temp);

    }
    return OK;
}

//������Ϣ����
Status CarLeftInformation(SqStack &S, SqStack &wait, LQueue &Q, Car &car)
{
    char id1[20];
    int out;//����ʱ��
    int reply;//�ж��Ƿ����ͣ����
    printf("��������ĳ��ƣ�\n");
    fflush(stdin);
    scanf("%s", id1);
    WhetherInStack(S, id1, reply);
    if (reply == 0) printf("��δ����ͣ����������ͣ����ѡ�\n");
    else
    {
        printf("��ʲôʱ���뿪ͣ������\n");
        scanf("%d",&out);
        CarOut(S, wait, Q, id1, out, car);
        printf("����ʱ��%d����ͣ������%d�뿪\n����%dСʱ��ÿСʱ2Ԫ��Ӧ��%dԪ\n",
        car.arrive, car.leave, car.leave-car.arrive, (car.leave-car.arrive)*2);
    }
    //����������
    printf("һ·˳�磡\n");
    return OK;
}

Status Menu(SqStack &park, SqStack &wait, LQueue &shortcut, Car &car, int length)
{
    int mode;
    printf("1.���� 2.����  0.�˳�\n");
    scanf("%d", &mode);
    switch (mode)
    {
    case 0:
        printf("�˳�����");
        exit(OK);
        break;
    case 1:
        CarIn(park, shortcut, length, car);
        CarInformationOut(car);
        break;
    case 2:
        CarLeftInformation(park, wait, shortcut, car);
        break;
    default:
        break;
    }
    return OK;
}

int main()
{
    int length;
    SqStack park, wait;
    LQueue shortcut;
    Car car;
    InitStack(park);
    InitStack(wait);
    InitLQueue(shortcut);
    printf("������ͣ������С��");
    scanf("%d", &length);
    printf("ͣ��������ϵͳ��prod.by ����� 2019051364\n");
    while(1)
    {
        Menu(park, wait, shortcut, car, length);
    }
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define Insig (-1)

typedef struct 
{
    int *elem;
    int length;
}SSTable;

void InitTable (SSTable &T)
{
    printf("������˳�����Ԫ������\n");
    scanf("%d", &T.length);
    T.elem = (int*) malloc (sizeof(int)*(T.length+1));
    T.elem[0] = Insig;
    printf("��������������Ԫ��\n");
    for (int i=1; i<T.length+1; i++)
    {
        scanf("%d",&T.elem[i]);
    }
    printf("��ʼ����ɣ�");
}

int SearchSeq (SSTable &T, int num)
{
    T.elem[0] = num;
    int p = T.length;
    int i;
    for (i=T.length; T.elem[i]!=num; --i);
    return i;
}

int SearchBin (SSTable &T, int num)
{
    int end = T.length;
    int begin = 1;
    while (!(begin>end))
    {
        int mid = (begin + end) / 2;
        if (T.elem[mid]<num) begin = mid + 1;
        else if (T.elem[mid]>num) end = mid - 1;
        else return mid;
    }
    return 0;
}

void InsertBin (SSTable &T, int num)
{
    int end = T.length;
    int begin = 1;
    while (!(begin>end))
    {
        int mid = (begin + end) / 2;
        if (T.elem[mid]<num) begin = mid + 1;
        else if (T.elem[mid]>num) end = mid - 1;
        else mid = num;
    }
}
int main()
{
    SSTable T;
    InitTable (T);
    int num;
    printf("����������ҵ���\n");
    scanf("%d", &num);
    int p = SearchSeq (T, num);
    if (p) printf("˳����ҳɹ������ǵ�%d����\n",p);
    else printf("˳�����û���ҵ�Ŀ��\n");
    int q = SearchBin (T, num);
    if (q) printf("�۰���ҳɹ������ǵ�%d����\n",p);
    else printf("�۰����û���ҵ�Ŀ��\n");
    system("pause");
    return 0;
}
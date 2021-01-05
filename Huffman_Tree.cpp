#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define DEFAULT 1
#define INF INT_MAX
#define MAX_SIZE 20
typedef int Status;
typedef int ElemType;

typedef struct HTNode
{
    unsigned int weight;
    unsigned int parent, lchild, rchild;
}HTNode, * HuffmanTree;//静态链表

typedef char **HuffmanCode;

void SelectMin (HuffmanTree &HT, int i, int &s1, int &s2)
{
    int j;
    int min1 = INF, min2 = INF;
    for (j = 1; j<=i; j++)
    {
        if (HT[j].weight < min1 && HT[j].parent==0)
        {
            min1 = HT[j].weight;
            s1 = j;
        }
    }
    for (j = 1; j<=i; j++)
    {
        if (HT[j].weight < min2 && HT[j].parent==0 && j!=s1)
        {
            min2 = HT[j].weight;
            s2 = j;
        }
    }
}

void HuffmanCoding (HuffmanTree &HT, HuffmanCode &HC, int *w, int n)//w中存放n个数的权值，返回huffman编码到HC
{
    int m = n * 2 - 1;//总结点数
    HT = (HuffmanTree) malloc (sizeof(HTNode) * (m+1));//第一个表不存,所以要多一个。
    HT[0] = {0, 0, 0, 0};
    for(int i = 1; i<=m; i++)
    {
        if (i<=n)
        {
            HT[i] = {w[i-1], 0, 0, 0};//将w中的权值存入HT中
        }
        else HT[i] = {0, 0, 0, 0};//多余的结点则是全0
    }//初始化完毕
    for(int i=n+1; i<=m; i++)
    {
        int s1 = 0, s2 = 0;
        SelectMin(HT ,i ,s1, s2);//s1,s2是最小权值的序号
        HT[s1].parent = i;
        HT[s2].parent = i;
        HT[i].lchild = s1;
        HT[i].rchild = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }
    //开始输出
    HC = (HuffmanCode) malloc ((n+1)*sizeof(char *));//分配存储n+1个数的数组，但这个HC中只存他们的指针，具体的HC[i]还没有初始化
    char *cd = (char *)malloc(n * sizeof(char));//分配了某一个字串cd的空间，大小是n-1个字符，但是肯定多了，这是最不优的二叉树上产生的。
    cd[n-1] = '\0';
    for (int i=1; i<=n; i++)
    {
        int start = n - 1;//由于求出来的码是逆向的，所以要从最后一位开始输入。
        for (int c=i, f=HT[i].parent; f!=0; c=f)//对于某一个结点，要开始找他的编码
        {
            if (HT[f].lchild == c) cd[--start] = '0';
            else cd[--start] = '1';
            f = HT[f].parent;
        }
        HC[i] = (char *) malloc ((n-start)*sizeof(char));
        strcpy(HC[i], &cd[start]);
    }
    free(cd);//临时空间需要free掉
}

void HuffmanDecoding (char *str, HuffmanCode HC, int n, char *Coded, char *Decoded)//str是字符组，HC是哈夫曼树，Coded是待解码字符串,Decoded返回结果
{
    
}
int main()
{
    HuffmanTree HT;
    HuffmanCode HC;
    int n;
    printf("请输入需要创建含有多少个字符的Haffman树？\n");
    scanf("%d",&n);
    char str[n+1];
    printf("请输入这n个字符，不需要分隔符\n");
    gets(str);
    int w[n];
    printf("请分别输入他们的权值\n");
    for (int i=0; i<n; i++)
    {
        scanf("%d",&w[i]);
    }
    HuffmanCoding(HT, HC, w, n);
}
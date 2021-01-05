#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    char data;
    Node* next;
} *Stack, Node;

void Init (Stack &S)
{
    Node *node = (Node*) malloc (sizeof(Node));
    S = node;
    S->next = NULL;
}

void Push (Stack &S, char e)
{
    Node *node = (Node *) malloc (sizeof(Node));
    node->data = e;
    node->next = S->next;
    S->next = node;
}

int Pop (Stack &S, char &e)
{
    if (S->next == NULL) return 0;
    Node *p = S->next;
    e = p->data;
    S->next = p->next;
    free (p);
    return 1;
}



int main()
{
    Stack S;
    Init(S);
    char e;
    char c;
    while (1)
    {
        scanf("%c",&e);
        if (e=='0') break;
        if (e=='('||e=='['||e=='{') Push(S,e);
        else if(e==')'||e=='}'||e=='}')
        {
            Pop(S,c);
            if(e==')')
            {
                if(c!='(') 
                {
                    printf("∆•≈‰ ß∞‹");
                    break;
                }
            }
            if(e==']')
            {
                if(c!='[') 
                {
                    printf("∆•≈‰ ß∞‹");
                    break;
                }
            }
            if(e=='}')
            {
                if(c!='{') 
                {
                    printf("∆•≈‰ ß∞‹");
                    break;
                }
            }
        }
    }
    char tmp;
    if (Pop(S,tmp)) printf ("∆•≈‰ ß∞‹£°");
    else printf("∆•≈‰≥…π¶");
    system("pause");
    return 0;
}
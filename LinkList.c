#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 50
typedef struct NODE
{
    int date;
    struct NODE *next;
} Node;
void OutputList(Node *L) //对线性表进行输出操作
{
    Node *p = L;
    do
    {
        p = p->next;
        printf("%d ", p->date);
    } while (p->next != NULL);
    printf("\n");
}
Node *del(Node *L, int n) //对线性表进行删除元素操作
{
    Node *p = L;
    Node *t = NULL;
    do
    {
        t = p;
        p = p->next;
        if (p->date == n)
        {
            t->next = p->next;
            p = t;
        }
    } while (p->next != NULL && p);
    return L;
}
Node *quchong(Node *L) //对排好序的线性表进行去重操作
{
    Node *p = L->next;
    Node *q = NULL;
    do
    {
        q = p->next;
        if (q->date == p->date && q)
        {
            p->next = q->next;
            free(q);
        }
        p = p->next;
    } while (p && p->next);
    return L;
}
Node *sort(Node *L) //对链表进行升序排序
{
    Node *pfirst = NULL, *psecond = NULL, *pend = NULL;
    pfirst = L;
    psecond = L;
    int temp;
    while (pfirst != pend)
    {
        while (pfirst->next != pend)
        {
            if (pfirst->date > pfirst->next->date)
            {
                temp = pfirst->date;
                pfirst->date = pfirst->next->date;
                pfirst->next->date = temp;
            }
            pfirst = pfirst->next;
        }
        pend = pfirst;
        pfirst = L;
    }
    return L;
}
Node *reverse(Node *L) //对链表进行逆置操作
{
    Node *head = L->next;
    Node *side = L->next;
    if (!side || !head)
    {
        return L;
    }
    Node *end = head->next;
    while (end)
    {
        side->next = end->next;
        end->next = head;
        head = end;
        end = side->next;
    }
    L->next = head;
    return L;
}
Node *Mov(Node *L, char p, int n) //对线性表进行左右循环移动操作
{
    Node *head = L->next;
    Node *tmp = head->next;
    int num = 2;
    while (tmp && tmp->next)
    {
        tmp = tmp->next;
        num++;
    }
    tmp->next = head;
    int i, j;
    if (p == 'L' || p == 'l')
    {
        j = 1;
    }
    else if (p == 'R' || p == 'r')
    {
        j = -1;
    }
    for (i = 0; i < (num + j * n) % num; i++)
    {
        head = head->next;
        tmp = tmp->next;
    }
    tmp->next = NULL;
    L->next = head;
    return L;
}
void link(Node *L1, Node *L2)
{
    Node *p = L1->next;
    Node *q = L2->next;
    Node *t = L1;
    while (p && q)
    {
        if (p->date < q->date)
        {
            t->next = p;
            t = p;
            p = p->next;
        }
        else if (p->date >= q->date)
        {
            t->next = q;
            t = q;
            q = q->next;
        }
    }
    t->next = q ? q : p;
}
int main()
{

    Node *List = NULL;
    int n;
    List = (Node *)malloc(sizeof(Node));
    List->next = NULL;
    List->date = 0;
    Node *tmp = List;
    int a[9] = {2, 3, 3, 5, 9, 11, 12, 14, 14};
    int i;
    printf("创建元素如下的链式线性表：\n");
    for (i = 0; i < 9; i++)
    {
        Node *p = NULL;
        p = (Node *)malloc(sizeof(Node));
        p->date = a[i];
        p->next = NULL;
        tmp->next = p;
        tmp = p;
        printf("%d ", a[i]);
    }
    printf("\n想要删除的元素值为多少?\n");
    scanf("%d", &n);
    fflush(stdin);
    List = del(List, n);
    printf("删除后结果为：\n");
    OutputList(List);
    List = sort(List);
    printf("对线性表进行去重操作后，结果为：\n");
    List = quchong(List);
    OutputList(List);
    printf("对线性表进行逆置操作后，结果为：\n");
    List = reverse(List);
    OutputList(List);
    printf("想对线性表进行左移还是右移?左移输入L或l,右移输入R或r\n");
    char pos;
    scanf("%c", &pos);
    fflush(stdin);
    printf("你想移动几位？（输入整数）\n");
    int len;
    scanf("%d", &len);
    List = Mov(List, pos, len);
    printf("移动后结果为：\n");
    OutputList(List);
    printf("对该链表进行升序排序,结果为：\n");
    sort(List);
    OutputList(List);
    printf("现创建另一升序链式线性表，元素如下：\n");
    Node *List1 = NULL;
    List1 = (Node *)malloc(sizeof(Node));
    List1->next = NULL;
    List1->date = 0;
    int b[9] = {1, 3, 7, 7, 8, 11, 15, 16, 19};
    tmp = List1;
    for (i = 0; i < 9; i++)
    {
        Node *p = NULL;
        p = (Node *)malloc(sizeof(Node));
        p->date = b[i];
        p->next = NULL;
        tmp->next = p;
        tmp = p;
        printf("%d ", b[i]);
    }
    printf("\n合并完线性表后,结果为：\n");
    link(List, List1);
    OutputList(List);
    return 0;
}
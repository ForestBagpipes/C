#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 100
int visited[MAXSIZE];
int c = 1; //记录深度优先编号

//创建一个左子女右兄弟结构的树的结构体
typedef struct tree
{
    int n;
    struct tree *first; //树的左子女
    struct tree *next;  //树的右兄弟
} tree;

//创建边表结点结构体
typedef struct enode
{
    struct enode *next; //指向下一边的指针域
    int adj;            //邻接点域（下标）
} enode;

//创建顶点表结点结构体
typedef struct vnode
{
    enode *first; //边表首结点
    char date;    //顶点名称
} vnode;

//创建邻接表结构体
typedef struct
{
    vnode vlist[MAXSIZE];
    int n; //邻接表顶点数
    int e; //邻接表边数
} algragh;

//创建邻接矩阵结构体
typedef struct mgragh
{
    int n, e;
    char vex[MAXSIZE];
    int edg[MAXSIZE][MAXSIZE];
} mgragh;

//建立一个栈的结构体
typedef struct Stack
{
    tree *base[MAXSIZE];
    int top;
} * stack;

tree *DFSal1(algragh g, int i, tree *t);

//初始化栈
stack inits()
{
    stack s;
    s = (stack)malloc(sizeof(struct Stack));
    s->top = -1;
    return s;
}

//入栈
void push(stack s, tree *p)
{
    if (s->top < MAXSIZE - 1)
    {
        s->base[++(s->top)] = p;
    }
    else
    {
        printf("栈满！\n");
    }
}

//出栈
void pop(stack s, int *i)
{
    if (s->top == -1)
    {
        printf("栈空！\n");
    }
    else
    {
        *i = s->base[s->top]->n;
        s->top--;
    }
}

//返回栈顶元素
tree *gettop(stack s, tree *i)
{
    if (s->top == -1)
    {
        return NULL;
    }
    else
    {
        i = s->base[s->top];
    }
    return i;
}

//判断栈空
int isempty(stack s)
{
    if (s->top == -1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//清空栈
void clears(stack s)
{
    s->top = -1;
}

//销毁栈
void destroys(stack s)
{
    free(s);
}
//初始化邻接表
void initalgragh(algragh *g)
{
    int i;
    for (i = 0; i < MAXSIZE; i++)
    {
        g->vlist[i].first = NULL;
    }
}

//创建邻接表
void createalgragh(algragh *g)
{
    int i;
    char a;
    printf("请输入邻接表顶点数和边数: \n");
    scanf("%d %d", &g->n, &g->e);
    printf("\n");
    fflush(stdin);
    printf("请输入顶点的名称（连续输入不需要空格或逗号）\n");
    for (i = 0; i < g->n; i++)
    {
        scanf("%c", &a);
        g->vlist[i].date = a;
    }
    printf("\n");
    fflush(stdin);
    char b, c;
    int j, k;
    for (i = 0; i < g->e; i++)
    {
        printf("请输入边的两个顶点：\n");
        scanf("%c%c", &b, &c);
        fflush(stdin);
        for (j = 0; j < g->n; j++)
        {
            if (g->vlist[j].date == b)
                break;
        }
        for (k = 0; k < g->n; k++)
        {
            if (g->vlist[k].date == c)
                break;
        }
        enode *p1, *p2;
        p1 = (enode *)malloc(sizeof(enode));
        p1->adj = j;
        p1->next = g->vlist[k].first;
        g->vlist[k].first = p1;
        p2 = (enode *)malloc(sizeof(enode));
        p2->adj = k;
        p2->next = g->vlist[j].first;
        g->vlist[j].first = p2;
    }
}

//输出邻接表
void outputal(algragh g)
{
    int i, j;
    enode *p;
    printf("该邻接表为:\n");
    for (i = 0; i < g.n; i++)
    {
        printf("%c ", g.vlist[i].date);
        p = g.vlist[i].first;
        while (p)
        {
            printf(" -> %c ", g.vlist[p->adj].date);
            p = p->next;
        }
        printf("\n");
    }
}

//创建邻接矩阵
void createmgragh(mgragh *g)
{
    int i, j, k;
    char a, b, c;
    memset(g->edg, 0, sizeof(g->edg));
    memset(g->vex, ' ', sizeof(g->vex));
    printf("请输入邻接矩阵的顶点数和边数: \n");
    scanf("%d %d", &g->n, &g->e);
    printf("\n");
    fflush(stdin);
    printf("请输入顶点的名称（连续输入不需要空格或逗号）\n");
    for (i = 0; i < g->n; i++)
    {
        scanf("%c", &a);
        g->vex[i] = a;
    }
    printf("\n");
    fflush(stdin);
    for (i = 0; i < g->e; i++)
    {
        printf("请输入边的两个顶点：\n");
        scanf("%c%c", &b, &c);
        fflush(stdin);
        for (j = 0; j < g->n; j++)
        {
            if (g->vex[j] == b)
                break;
        }
        for (k = 0; k < g->n; k++)
        {
            if (g->vex[k] == c)
                break;
        }
        g->edg[j][k] = 1;
        g->edg[k][j] = 1;
    }
}

//输出邻接矩阵
void outputm(mgragh g)
{
    int i, j;
    printf("该邻接矩阵为：\n");
    for (i = 0; i < g.n; i++)
    {
        for (j = 0; j < g.n; j++)
        {
            printf("%d ", g.edg[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

//输出生成森林
void outputtree(tree *t, mgragh *g1, algragh *g2)
{
    if (t && g1)
    {
        printf("           %d              %d               %c \n", c++, t->n, g1->vex[t->n]);
        outputtree(t->first, g1, g2);
        outputtree(t->next, g1, g2);
    }
    if (t && g2)
    {
        printf("           %d              %d               %c \n", c++, t->n, g2->vlist[t->n].date);
        outputtree(t->first, g1, g2);
        outputtree(t->next, g1, g2);
    }
}

//实现邻接表转邻接矩阵
mgragh *altom(algragh g)
{
    mgragh *r;
    r = (mgragh *)malloc(sizeof(mgragh));
    memset(r->edg, 0, sizeof(r->edg));
    memset(r->vex, ' ', sizeof(r->vex));
    r->e = g.e;
    r->n = g.n;
    int i;
    char a;
    enode *p;
    for (i = 0; i < g.n; i++)
    {
        r->vex[i] = g.vlist[i].date;
    }
    for (i = 0; i < g.n; i++)
    {
        p = g.vlist[i].first;
        while (p)
        {
            r->edg[i][p->adj] = 1;
            p = p->next;
        }
    }
    return r;
}

//邻接矩阵转邻接表
algragh *mtoal(mgragh g)
{
    algragh *r;
    r = (algragh *)malloc(sizeof(algragh));
    r->e = g.e;
    r->n = g.n;
    int i, j, n;
    enode *p, *tmp;
    for (i = 0; i < g.n; i++)
    {
        r->vlist[i].date = g.vex[i];
        r->vlist[i].first = NULL;
    }
    for (i = 0; i < g.n; i++)
    {
        n = 0;
        tmp = NULL;
        for (j = g.n - 1; j >= 0; j--)
        {
            if (g.edg[i][j])
            {
                n++;
                p = (enode *)malloc(sizeof(enode));
                p->adj = j;
                p->next = NULL;
                if (n == 1)
                {
                    r->vlist[i].first = p;
                    tmp = p;
                }
                else
                {
                    tmp->next = p;
                    tmp = p;
                }
            }
        }
    }
    return r;
}

//邻接表的深度优先搜索递归主函数
tree *traDFSal1(algragh g, tree *t)
{
    memset(visited, 0, sizeof(visited));
    int i;
    c = 1;
    t = NULL;
    tree *q = NULL;
    for (i = 0; i < g.n; i++)
    {
        if (!visited[i])
        {
            tree *p = (tree *)malloc(sizeof(tree));
            p->n = i;
            p->first = NULL;
            p->next = NULL;
            if (!t)
            {
                t = p;
            }
            else
            {
                q->next = p;
            }
            q = p;
            p->first = DFSal1(g, i, p->first);
        }
    }
    return t;
}

//邻接表的深度优先递归搜索
tree *DFSal1(algragh g, int i, tree *t)
{
    enode *tmp;
    tree *q;
    int index, f = 1;
    visited[i] = 1;
    tmp = g.vlist[i].first;
    while (tmp)
    {
        for (index = 0; index < g.n; index++)
        {
            if (tmp->adj == index)
            {
                break;
            }
        }
        if (!visited[index])
        {
            tree *t1;
            t1 = (tree *)malloc(sizeof(tree));
            t1->n = index;
            t1->first = NULL;
            t1->next = NULL;
            if (f)
            {
                t = t1;
                f = 0;
            }
            else
            {
                q->next = t1;
            }
            q = t1;
            t1->first = DFSal1(g, index, t1->first);
        }
        tmp = tmp->next;
    }
    return t;
}

//非递归---邻接表的深度优先函数
tree *DFSal2(algragh g, int i, tree *t)
{
    c = 1;
    tree *q, *T;
    T = t;
    stack s;
    s = inits();
    push(s, t);
    visited[i] = 1;
    int result, first = 1;
    while (!isempty(s))
    {
        q = gettop(s, q);
        enode *tmp;
        first = 1;
        tmp = g.vlist[q->n].first;
        while (tmp)
        {
            if (!visited[tmp->adj])
            {
                visited[tmp->adj] = 1;
                tree *t1;
                t1 = (tree *)malloc(sizeof(tree));
                t1->n = tmp->adj;
                t1->first = NULL;
                t1->next = NULL;
                if (first)
                {
                    first = 0;
                    q->first = t1;
                }
                else
                {
                    q->next = t1;
                }
                q = t1;
                push(s, t1);
                tmp = g.vlist[tmp->adj].first;
            }
            else
            {
                tmp = tmp->next;
            }
        }
        if (!tmp)
        {
            pop(s, &result);
        }
    }
    clears(s);
    destroys(s);
    return T;
}

//非递归---邻接表的深度优先主函数
tree *traDFSal2(algragh g, tree *t)
{
    memset(visited, 0, sizeof(visited));
    int i;
    c = 1;
    t = NULL;
    tree *q = NULL;
    for (i = 0; i < g.n; i++)
    {
        if (!visited[i])
        {
            tree *p = (tree *)malloc(sizeof(tree));
            p->n = i;
            p->first = NULL;
            p->next = NULL;
            if (!t)
            {
                t = p;
            }
            else
            {
                q->next = p;
            }
            q = p;
            p = DFSal2(g, i, p);
        }
    }
    return t;
}

//邻接表的广度优先递归搜索
tree *BFSal1(algragh g, int i, tree *t)
{
    enode *tmp;
    tree *T = t;
    tree *que[MAXSIZE];
    memset(que, 0, sizeof(que));
    int top = -1;
    int bot = -1;
    int a;
    visited[i] = 1;
    que[++top] = t;
    ++bot;
    while (top >= bot)
    {
        tree *q;
        int f = 1;
        q = que[bot++];
        a = q->n;
        tmp = g.vlist[a].first;
        while (tmp)
        {
            if (!visited[tmp->adj])
            {
                visited[tmp->adj] = 1;
                tree *t1;
                t1 = (tree *)malloc(sizeof(tree));
                t1->n = tmp->adj;
                t1->first = NULL;
                t1->next = NULL;
                que[++top] = t1;
                if (f)
                {
                    f = 0;
                    q->first = t1;
                }
                else
                {
                    q->next = t1;
                }
                q = t1;
            }
            tmp = tmp->next;
        }
    }
    return T;
}

//邻接表的广度优先搜索递归主函数
tree *traBFSal1(algragh g, tree *t)
{
    memset(visited, 0, sizeof(visited));
    int i;
    c = 1;
    t = NULL;
    tree *q = NULL;
    for (i = 0; i < g.n; i++)
    {
        if (!visited[i])
        {
            tree *p = (tree *)malloc(sizeof(tree));
            p->n = i;
            p->first = NULL;
            p->next = NULL;
            if (!t)
            {
                t = p;
            }
            else
            {
                q->next = p;
            }
            q = p;
            p = BFSal1(g, i, p);
        }
    }
    return t;
}

//邻接矩阵的深度优先递归搜索
tree *DFSm1(mgragh g, int i, tree *t)
{
    tree *q;
    int j, f = 1;
    visited[i] = 1;
    for (j = g.n - 1; j >= 0; j--)
    {
        if (g.edg[i][j] == 1 && !visited[j])
        {
            tree *t1;
            t1 = (tree *)malloc(sizeof(tree));
            t1->n = j;
            t1->first = NULL;
            t1->next = NULL;
            if (f)
            {
                t = t1;
                f = 0;
            }
            else
            {
                q->next = t1;
            }
            q = t1;
            t1->first = DFSm1(g, j, t1->first);
        }
    }
    return t;
}

//邻接矩阵的深度优先生成森林主函数
tree *traDFSm1(mgragh g, tree *t)
{
    memset(visited, 0, sizeof(visited));
    int i;
    c = 1;
    t = NULL;
    tree *q = NULL;
    for (i = 0; i < g.n; i++)
    {
        if (!visited[i])
        {
            tree *p = (tree *)malloc(sizeof(tree));
            p->n = i;
            p->first = NULL;
            p->next = NULL;
            if (!t)
            {
                t = p;
            }
            else
            {
                q->next = p;
            }
            q = p;
            p->first = DFSm1(g, i, p->first);
        }
    }
    return t;
}

//非递归---邻接矩阵的深度优先函数
tree *DFSm2(mgragh g, int i, tree *t)
{
    tree *q = NULL, *T;
    T = t;
    stack s1;
    s1 = inits();
    visited[i] = 1;
    push(s1, t);
    int pos,k, j = 0, first = 1;
    while (!isempty(s1))
    {
        q = gettop(s1, q);
        pos = q->n;
        for (j = g.n - 1; j >= 0; j--)
        {
            if (g.edg[pos][j] == 1 && !visited[j])
            {
                tree *p = (tree *)malloc(sizeof(tree));
                p->n = j;
                p->first = NULL;
                p->next = NULL;
                if (first)
                {
                    q->first = p;
                    first = 0;
                }
                else
                {
                    q->next = p;
                }
                q = p;
                push(s1, p);
                visited[j] = 1;
                break;
            }
        }
        if (j == -1)
        {
            pop(s1, &k);
            first = 1;
        }
        else
        {
            first = 0;
        }
    }
    clears(s1);
    destroys(s1);
    return T;
}

//非递归---邻接矩阵的深度优先生成森林主函数
tree *traDFSm2(mgragh g, tree *t)
{
    memset(visited, 0, sizeof(visited));
    int i;
    c = 1;
    t = NULL;
    tree *q = NULL;
    for (i = 0; i < g.n; i++)
    {
        if (!visited[i])
        {
            tree *p = (tree *)malloc(sizeof(tree));
            p->n = i;
            p->first = NULL;
            p->next = NULL;
            if (!t)
            {
                t = p;
            }
            else
            {
                q->next = p;
            }
            q = p;
            p = DFSm2(g, i, p);
        }
    }
    return t;
}

//邻接矩阵的广度优先递归搜索
tree *BFSm1(mgragh g, int i, tree *t)
{
    enode *tmp;
    tree *T = t;
    tree *que[MAXSIZE];
    memset(que, 0, sizeof(que));
    int top = -1;
    int bot = -1;
    int a, j;
    visited[i] = 1;
    que[++top] = t;
    ++bot;
    while (top >= bot)
    {
        tree *q;
        int f = 1;
        q = que[bot++];
        a = q->n;
        for (j = g.n - 1; j >= 0; j--)
        {
            if (g.edg[a][j] && !visited[j])
            {
                visited[j] = 1;
                tree *t1;
                t1 = (tree *)malloc(sizeof(tree));
                t1->n = j;
                t1->first = NULL;
                t1->next = NULL;
                que[++top] = t1;
                if (f)
                {
                    f = 0;
                    q->first = t1;
                }
                else
                {
                    q->next = t1;
                }
                q = t1;
            }
        }
    }
    return T;
}

//邻接矩阵的广度优先搜索递归主函数
tree *traBFSm1(mgragh g, tree *t)
{
    memset(visited, 0, sizeof(visited));
    int i;
    c = 1;
    t = NULL;
    tree *q = NULL;
    for (i = 0; i < g.n; i++)
    {
        if (!visited[i])
        {
            tree *p = (tree *)malloc(sizeof(tree));
            p->n = i;
            p->first = NULL;
            p->next = NULL;
            if (!t)
            {
                t = p;
            }
            else
            {
                q->next = p;
            }
            q = p;
            p = BFSm1(g, i, p);
        }
    }
    return t;
}

//输出邻接表各结点的度
void aldegree(algragh g)
{
    int n, i;
    enode *tmp;
    printf("该邻接表的各结点的度为：\n");
    for (i = 0; i < g.n; i++)
    {
        tmp = g.vlist[i].first;
        n = 0;
        while (tmp)
        {
            n++;
            tmp = tmp->next;
        }
        printf("结点%c 的度为%d \n", g.vlist[i].date, n);
    }
    printf("\n");
}

//输出邻接矩阵各结点的度
void mdegree(mgragh g)
{
    int n, i, j;
    printf("该邻接矩阵的各结点的度为：\n");
    for (i = 0; i < g.n; i++)
    {
        n = 0;
        for (j = 0; j < g.n; j++)
        {
            if (g.edg[i][j])
            {
                n++;
            }
        }
        printf("顶点%c 的度为%d \n", g.vex[i], n);
    }
    printf("\n");
}

int main()
{
    algragh g1, *r2;
    mgragh g2, *r1;
    tree *t1 = NULL;
    tree *t2 = NULL;
    tree *t3 = NULL;
    tree *t4 = NULL;
    tree *t5 = NULL;
    tree *t6 = NULL;
    initalgragh(&g1);
    createalgragh(&g1);
    outputal(g1);
    r1 = altom(g1);
    printf("将该邻接表转换为邻接矩阵后\n");
    outputm(*r1);
    aldegree(g1);
    t1 = traDFSal1(g1, t1);
    printf("递归情况下：\n");
    printf("深度优先编号  深度优先序列   深度优先森林先序遍历\n");
    outputtree(t1, NULL, &g1);
    t5 = traDFSal2(g1, t5);
    printf("\n非递归情况下：\n");
    printf("深度优先编号  深度优先序列   深度优先森林先序遍历\n");
    outputtree(t5, NULL, &g1);
    printf("\n");
    t2 = traBFSal1(g1, t2);
    printf("广度优先编号  广度优先序列   广度优先森林先序遍历\n");
    outputtree(t2, NULL, &g1);
    printf("\n----------------------------------------------------------------------------\n");
    createmgragh(&g2);
    outputm(g2);
    r2 = mtoal(g2);
    printf("将该邻接矩阵转换为邻接表后\n");
    outputal(*r2);
    mdegree(g2);
    t3 = traDFSm1(g2, t3);
    printf("\n递归情况下：\n");
    printf("深度优先编号  深度优先序列   深度优先森林先序遍历\n");
    outputtree(t3, &g2, NULL);
    t6 = traDFSm2(g2, t6);
    printf("\n非递归情况下：\n");
    printf("深度优先编号  深度优先序列   深度优先森林先序遍历\n");
    outputtree(t6, &g2, NULL);
    t4 = traBFSm1(g2, t4);
    printf("广度优先编号  广度优先序列   广度优先森林先序遍历\n");
    outputtree(t4, &g2, NULL);
    return 0;
}
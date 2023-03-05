#include <stdio.h>
#include <string.h>
void hanoi(int n, char x,char y, char z)
{
    if (n == 1)
    {
        printf("将%c盘中的%d盘子移动到%c盘\n",x,n,z);
    }
    else
    {
        hanoi(n-1,x,z,y);
        printf("将%c盘中的%d盘子移动到%c盘\n",x,n,z);
        hanoi(n-1,y,x,z);
    }
}
int main()
{
    printf("输入汉诺塔层数：");
    int n;
    scanf("%d", &n);
    hanoi(n,'A','B','C');
    return 0;
}
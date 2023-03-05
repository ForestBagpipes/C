#include<stdio.h>
#include<stdlib.h>
int jiaogu(int n,int c)
{
    if(n==1)
    {
        c++;
        return c;
    }
    else if(n>1 && n %2 ==0)
    {
        c++;
        n = n/2;
        return jiaogu(n,c);
    }
    else if(n>1 && n%2!=0)
    {
        c++;
        n = n*3+1;
        return jiaogu(n,c);
    }
}
int main()
{
    int max=1,t=1;
    for(int i = 2;i<=99;i++)
    {
        int c = 0;
        c = jiaogu(i,c);
        if(c<0)
        {
            printf("验证失败");
        }
        if(c>max)
        {
            max=c;
            t=i;
        }
    }
    printf("验证成功\n");
    printf("整数%d的序列最长,长度为%d\n",t,max);
    printf("该序列为：");
    printf("%d ",t);
    while(t!=1)
    {
        if(t%2==0)
        {
            t = t/2;
        }
        else if(t%2!=0)
        {
            t = t*3+1;
        }
        printf("%d ",t);
    }
    return 0;
}
#include<stdio.h>
void bang(int paopao[],int n);
void show(int paopao[],int n);
int main()
{
	int n=0,i;
	printf("要几个数？\n");
	scanf("%d",&n);
	int paopao[n];
	printf("请输入%d个数\n",n);
	for(i=0;i<n;i++)
	{
		scanf("%d",&paopao[i]);
	}
	bang(paopao,n);
	show(paopao,n);
	return 0;
}

void bang(int paopao[],int n)
{//right的代表x每次从最右边开始，逐一与相邻的左边的值比较，若小则互换值且将right移到此处，若大则继续走，当x遇到left时表示一轮结束
//此时记住right的下标， 作为下一次冒泡的最左端left=right，直到left=n-1 
	int left=0,right,x,temp;
	while(left<n-1)
	{
		right=n-1;
		for(x=n-1;x>left;x--)
		{
			if(paopao[x]<paopao[x-1])
			{
				temp=paopao[x];
				paopao[x]=paopao[x-1];
				paopao[x-1]=temp;
				right=x;
			}
		}
		left=right;
	}
}

void show(int paopao[],int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		printf("%d ",paopao[i]);
	}
}

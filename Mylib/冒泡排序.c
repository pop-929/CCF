#include<stdio.h>
void bang(int paopao[],int n);
void show(int paopao[],int n);
int main()
{
	int n=0,i;
	printf("Ҫ��������\n");
	scanf("%d",&n);
	int paopao[n];
	printf("������%d����\n",n);
	for(i=0;i<n;i++)
	{
		scanf("%d",&paopao[i]);
	}
	bang(paopao,n);
	show(paopao,n);
	return 0;
}

void bang(int paopao[],int n)
{//right�Ĵ���xÿ�δ����ұ߿�ʼ����һ�����ڵ���ߵ�ֵ�Ƚϣ���С�򻥻�ֵ�ҽ�right�Ƶ��˴�������������ߣ���x����leftʱ��ʾһ�ֽ���
//��ʱ��סright���±꣬ ��Ϊ��һ��ð�ݵ������left=right��ֱ��left=n-1 
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

#include<stdio.h>
#include<stdlib.h>
int choose(int i,int sum);
int main()
{
	int i,sum;
	printf("有几个猴子玩儿？\n");
	scanf("%d",&sum);
	printf("第几个滚蛋？\n");
	scanf("%d",&i);
	while(1)
	{
		if(sum<=i)
		{
			printf("犯规了啊你，重新输入一个数\n");
			scanf("%d",&i);
		}
		else  break;
	}
	printf("The king is monkey:%d",choose(i,sum));
	return 0;
}

int choose(int i,int sum)
{
	int m,a=0,x=0,king,*p;
	p=(int*)malloc(sum*sizeof(int));
	if(p==NULL)
	{
		printf("内存空间不足，拜拜！\n");
		exit(1);
	}
	for(m=0;m<sum;m++)
	{
		p[m]=m+1;
	//	printf("%d ",p[m]);
	} 
	printf("\n");
	while(sum>1)
	{
		x=(x+i-1)%sum;
		printf("滚蛋的编号是%d  --  \n",p[x]);
		for(a=x+1;a<sum;a++)
		{
			p[a-1]=p[a];
		}
		sum--;
	//	printf("长度=%d  -- ",sum);
		if(x==sum)
		{
	//		printf("%d",sum); 
			x=0;
		}
		/* 
		printf("\t此时下标为%d--",x);
		int d=0;
		for(;d<sum;d++)
		{
			printf("p[%d]=%d  ",d,p[d]);
		}
		printf("\n\n");
		*/
	}
	king=p[0];
	free(p);
	return king;
}




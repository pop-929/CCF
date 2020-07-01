#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int x=0; 
void aaa(char *c,const char *p,const char *r);
int pipei(char *c,const char *p,const char *r ,int i,int lenall);
void shenqing(char *c); 
int main()
{
	char *c=(char*)malloc(5*sizeof(char));
	shenqing(c);
	char *p=(char*)malloc(2*sizeof(char));
	shenqing(p);
	char *r=(char*)malloc(2*sizeof(char));
	shenqing(r);
	printf("输入字符串\n");
	gets(c);                           
	printf("被替换的字符\n");
	scanf("%s",r);							 
	printf("替换成那些字符\n");
	scanf("%s",p);
	aaa(c,p,r);
	puts(c);
	free(c);
	free(p);
	free(r);
	return 0;
}

void shenqing(char *c)
{
	if(c==NULL)
	{
		printf("不好意思了这位爷，没有地儿了！！！\n");
		exit(1);
	}
}

void aaa(char *c,const char *p,const char *r)
{
	int lenall=strlen(c),lenp=strlen(p),lenr=strlen(r),last=0,i=0,s=lenp-lenr,lenall_1=lenall+s;
	i=pipei(c,p,r,i,lenall);                                             //总字符c，c里面被替换的字符r，目标字符字符p 
	while(i<lenall-lenr+1)
	{
//		printf("lenall_1=%d\n",lenall_1);
		if(s>0)//2.11
		{
//			printf("s>0\n"); 
			int   m=lenall_1-1+s,  n=i+s;//s要改  下面的也是 
			for(;m>n;m--)
			{
//				printf("c[%d]=%c变为-->",m,c[m]);
				c[m]=c[m-s];
//				printf("\tc[%d]=%c\n",m,c[m]);
			}
		}else
		{
			if(s<0)//2.12
			{
//				printf("s<0\n");
				int   m=i,  n=lenall_1-1-s;                     //总字符c，c里面被替换的字符r，目标字符字符p, 
				for(;m<n;m++)		
				{
//					printf("c[%d]=%c变为-->",m,c[m]);
					c[m]=c[m-s];
//					c[m-s]='\0';
//					printf("\tc[%d]=%c\n",m,c[m]);
				}
			}
		}
//		printf("第%d次进入替换程序---当前：%s---i=%d  开始替换：\n",x,c,i);
		last=i+lenp;//即将进入第三阶段 
		int k=0;
		while(i<last)
		{
//			printf("由c[%d]=%c",i,c[i]); 
			c[i++]=p[k++];
//			printf("变为-->c[%d]=%c",i-1,c[i-1]);                     //总字符c，c里面被替换的字符r，目标字符字符p ,s=lenp-lenr为替换后总长增加的字符 
		}
		lenall_1=lenall+s;
		lenall=lenall_1;/*
		int o;
		printf("\n");
		for(o=0;o<lenall_1;o++)
		{
			printf("%c",c[o]);
		}
		printf("\n\n");*/
		i=pipei(c,p,r,i,lenall);//再次执行第一阶段  
	}
	if(x<2) printf("没有符合要求的字符！\n");
}

int pipei(char *c,const char *p,const char *r,int i,int lenall)
{
	x++;
	//printf("第%d次查找\n",x);
	int lenp=strlen(p),lenr=strlen(r),lastr=lenr-1,k;//1.1
	if(lenr==1)//如果是一个字符  则直接比较首字符 
	{
	//	printf("第%d次进入单字符判断\n",x);
		for(;i<lenall-1;i++)
		{
			if(c[i]==r[0])
			{   
	//			printf("\n匹配成功，此时c[%d]=%c--r=%c\n",i,c[i],r[0]);
				break;//注意这里是返回i还是i++   下面的也一样                      //总字符c，c里面被替换的字符r，目标字符字符p ,s=lenp-lenr为替换后总长增加的字符 
			}
			/*else
			{
				printf("i=%d  ",i);
			}*/
		}
	}else {
	//	printf("第%d次进入长字符匹配\n",x);
		for(;i<lenall-lenr+1;i++)  
		{
	//		printf("循环里面的c[%d]=%c--r[0]=%c\n",i,c[i],r[0]); 
			if(c[i]==r[0])//1.2
			{
				int lastr_c=lastr+i;
	//			printf("首字符匹配成功，此时c[%d]=%c  r[0]=%c  c[%d]=%c  r[%d]=%c\n",i,c[i],r[0],lastr_c,c[lastr_c],lastr,r[lastr]);
				if(c[lastr_c]==r[lastr])//1.3
				{
	//				printf("尾字符也匹配成功，进入中间字符匹配:\n");
					int n=1;//n是匹配的中间字符的下标 
					for(k=i+1;k<i+lenr-1;k++)//1.4
					{
	//					printf(" -正在匹配第%d个字符-此时：c[%d]=%c-r[%d]=%c\n ",n,k,c[k],n,r[n]); 
						if(c[k]!=r[n])  break;//这个break意思是字符匹配失败，结束第四步返回到第二步 
						else	n++;
					}
	//				if(n!=lenr-1)  printf("中间字符匹配失败，要找的不是这个，失败原因：c[%d]=%c--r[%d]=%c\n",k,c[k],n,r[n]);
					if(n==lenr-1)
					{	
	//					printf("第%d次匹配成功！\n",x);
						break;//1.5   这个break意思是字符匹配成功，结束整个匹配工作 
					}
				}
			}
	//		printf("  %d\n",lenall-lenr);
		}	
	}
//	printf("匹配里的i=%d\n",i);
	return i; 
}
/*总字符c，c里面被替换的字符r，目标字符字符p ，s为替换后总长增加的字符 
第一阶段：匹配阶段 
第一步，使用strlen函数记录c的长度lenall，p的长度lenp，r的长度lenr，s=lenp-lenr 
第二步，取出r的首字符，与c字符逐一进行比对，当比对到lenall-lenr的时候，停止比对，输出（没有符合要求的字符）结束程序，因为此时已经超出了字符上限，没有比对的必要了
第三步，若c中第i个字符与r的首字符相匹配，则比较r的尾字符lastr=lenr-1与c的第lastr_c=i+lastr字符是否匹配，若不匹配，则执行第二步
第四步，继续匹配中间字符，若遇到不匹配，则返回执行第二步 
第五步，至此   记录此时的 c中字符下标i  进入第二阶段 

 第二阶段：移位阶段
 第一步，比较p的长度lenp和r的长度lenr，
 	 1.若lenp>lenr，相差字符为s=lenp-lenr>0,即被替换的字符r比目标字符p短，原总长c增加 
	  	则后面的字符从后边开始移动，即lenall-1移动到m=lenall-1+s的位置，一直将m移动到n=i+s+1的位置
	 2.若lenp<lenr,相差字符为s=lenr-lenp<0,即被替换的字符r比目标字符p长，原总长c减小 
	 	则后面的字符从前边开始移动，即 i-s移动到m=i的位置，一直将m移动到n=lenall-1+s的位置
	 3.若lenp=lenr，则不移动
 第二步，记录到替换开始的位置i，和结束位置last=i+lenr，进入第三阶段
  
 第三阶段：替换阶段
 第一步，替换 从i开始到last结束
 第二步，返回第一阶段 
*/

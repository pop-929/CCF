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
	printf("�����ַ���\n");
	gets(c);                           
	printf("���滻���ַ�\n");
	scanf("%s",r);							 
	printf("�滻����Щ�ַ�\n");
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
		printf("������˼����λү��û�еض��ˣ�����\n");
		exit(1);
	}
}

void aaa(char *c,const char *p,const char *r)
{
	int lenall=strlen(c),lenp=strlen(p),lenr=strlen(r),last=0,i=0,s=lenp-lenr,lenall_1=lenall+s;
	i=pipei(c,p,r,i,lenall);                                             //���ַ�c��c���汻�滻���ַ�r��Ŀ���ַ��ַ�p 
	while(i<lenall-lenr+1)
	{
//		printf("lenall_1=%d\n",lenall_1);
		if(s>0)//2.11
		{
//			printf("s>0\n"); 
			int   m=lenall_1-1+s,  n=i+s;//sҪ��  �����Ҳ�� 
			for(;m>n;m--)
			{
//				printf("c[%d]=%c��Ϊ-->",m,c[m]);
				c[m]=c[m-s];
//				printf("\tc[%d]=%c\n",m,c[m]);
			}
		}else
		{
			if(s<0)//2.12
			{
//				printf("s<0\n");
				int   m=i,  n=lenall_1-1-s;                     //���ַ�c��c���汻�滻���ַ�r��Ŀ���ַ��ַ�p, 
				for(;m<n;m++)		
				{
//					printf("c[%d]=%c��Ϊ-->",m,c[m]);
					c[m]=c[m-s];
//					c[m-s]='\0';
//					printf("\tc[%d]=%c\n",m,c[m]);
				}
			}
		}
//		printf("��%d�ν����滻����---��ǰ��%s---i=%d  ��ʼ�滻��\n",x,c,i);
		last=i+lenp;//������������׶� 
		int k=0;
		while(i<last)
		{
//			printf("��c[%d]=%c",i,c[i]); 
			c[i++]=p[k++];
//			printf("��Ϊ-->c[%d]=%c",i-1,c[i-1]);                     //���ַ�c��c���汻�滻���ַ�r��Ŀ���ַ��ַ�p ,s=lenp-lenrΪ�滻���ܳ����ӵ��ַ� 
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
		i=pipei(c,p,r,i,lenall);//�ٴ�ִ�е�һ�׶�  
	}
	if(x<2) printf("û�з���Ҫ����ַ���\n");
}

int pipei(char *c,const char *p,const char *r,int i,int lenall)
{
	x++;
	//printf("��%d�β���\n",x);
	int lenp=strlen(p),lenr=strlen(r),lastr=lenr-1,k;//1.1
	if(lenr==1)//�����һ���ַ�  ��ֱ�ӱȽ����ַ� 
	{
	//	printf("��%d�ν��뵥�ַ��ж�\n",x);
		for(;i<lenall-1;i++)
		{
			if(c[i]==r[0])
			{   
	//			printf("\nƥ��ɹ�����ʱc[%d]=%c--r=%c\n",i,c[i],r[0]);
				break;//ע�������Ƿ���i����i++   �����Ҳһ��                      //���ַ�c��c���汻�滻���ַ�r��Ŀ���ַ��ַ�p ,s=lenp-lenrΪ�滻���ܳ����ӵ��ַ� 
			}
			/*else
			{
				printf("i=%d  ",i);
			}*/
		}
	}else {
	//	printf("��%d�ν��볤�ַ�ƥ��\n",x);
		for(;i<lenall-lenr+1;i++)  
		{
	//		printf("ѭ�������c[%d]=%c--r[0]=%c\n",i,c[i],r[0]); 
			if(c[i]==r[0])//1.2
			{
				int lastr_c=lastr+i;
	//			printf("���ַ�ƥ��ɹ�����ʱc[%d]=%c  r[0]=%c  c[%d]=%c  r[%d]=%c\n",i,c[i],r[0],lastr_c,c[lastr_c],lastr,r[lastr]);
				if(c[lastr_c]==r[lastr])//1.3
				{
	//				printf("β�ַ�Ҳƥ��ɹ��������м��ַ�ƥ��:\n");
					int n=1;//n��ƥ����м��ַ����±� 
					for(k=i+1;k<i+lenr-1;k++)//1.4
					{
	//					printf(" -����ƥ���%d���ַ�-��ʱ��c[%d]=%c-r[%d]=%c\n ",n,k,c[k],n,r[n]); 
						if(c[k]!=r[n])  break;//���break��˼���ַ�ƥ��ʧ�ܣ��������Ĳ����ص��ڶ��� 
						else	n++;
					}
	//				if(n!=lenr-1)  printf("�м��ַ�ƥ��ʧ�ܣ�Ҫ�ҵĲ��������ʧ��ԭ��c[%d]=%c--r[%d]=%c\n",k,c[k],n,r[n]);
					if(n==lenr-1)
					{	
	//					printf("��%d��ƥ��ɹ���\n",x);
						break;//1.5   ���break��˼���ַ�ƥ��ɹ�����������ƥ�乤�� 
					}
				}
			}
	//		printf("  %d\n",lenall-lenr);
		}	
	}
//	printf("ƥ�����i=%d\n",i);
	return i; 
}
/*���ַ�c��c���汻�滻���ַ�r��Ŀ���ַ��ַ�p ��sΪ�滻���ܳ����ӵ��ַ� 
��һ�׶Σ�ƥ��׶� 
��һ����ʹ��strlen������¼c�ĳ���lenall��p�ĳ���lenp��r�ĳ���lenr��s=lenp-lenr 
�ڶ�����ȡ��r�����ַ�����c�ַ���һ���бȶԣ����ȶԵ�lenall-lenr��ʱ��ֹͣ�ȶԣ������û�з���Ҫ����ַ�������������Ϊ��ʱ�Ѿ��������ַ����ޣ�û�бȶԵı�Ҫ��
����������c�е�i���ַ���r�����ַ���ƥ�䣬��Ƚ�r��β�ַ�lastr=lenr-1��c�ĵ�lastr_c=i+lastr�ַ��Ƿ�ƥ�䣬����ƥ�䣬��ִ�еڶ���
���Ĳ�������ƥ���м��ַ�����������ƥ�䣬�򷵻�ִ�еڶ��� 
���岽������   ��¼��ʱ�� c���ַ��±�i  ����ڶ��׶� 

 �ڶ��׶Σ���λ�׶�
 ��һ�����Ƚ�p�ĳ���lenp��r�ĳ���lenr��
 	 1.��lenp>lenr������ַ�Ϊs=lenp-lenr>0,�����滻���ַ�r��Ŀ���ַ�p�̣�ԭ�ܳ�c���� 
	  	�������ַ��Ӻ�߿�ʼ�ƶ�����lenall-1�ƶ���m=lenall-1+s��λ�ã�һֱ��m�ƶ���n=i+s+1��λ��
	 2.��lenp<lenr,����ַ�Ϊs=lenr-lenp<0,�����滻���ַ�r��Ŀ���ַ�p����ԭ�ܳ�c��С 
	 	�������ַ���ǰ�߿�ʼ�ƶ����� i-s�ƶ���m=i��λ�ã�һֱ��m�ƶ���n=lenall-1+s��λ��
	 3.��lenp=lenr�����ƶ�
 �ڶ�������¼���滻��ʼ��λ��i���ͽ���λ��last=i+lenr����������׶�
  
 �����׶Σ��滻�׶�
 ��һ�����滻 ��i��ʼ��last����
 �ڶ��������ص�һ�׶� 
*/

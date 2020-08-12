/*
 * @Description: 
 * @Author: pop
 * @E-mail: pop929@qq.com
 * @Date: 2020-07-05 21:11:02
 * @Version: 1.0.1
 * @LastEditTime: 2020-08-10 21:14:54
 */ 
#include <stdio.h>
#define N 100000              //注意写死为最大限度（对应下面子程序中的n < 100000）
int a[N];
int main(void)                //括号里参数是否多余
{
	int n;
	scanf("%d", &n);
	for(int i=0; i<n; i++)
		scanf("%d", &a[i]);                             //明明一样，在DEV++中就是要多输入个0
	int mina = a[0], maxa = a[n - 1];                   //初始化，省事
	if(mina > maxa) {int tmp = mina; mina = maxa; maxa = tmp;}      
	if(n % 2 == 1) {
		printf("%d %d %d", maxa, a[n / 2], mina);
	} else {
		if((a[n / 2 - 1] + a[n / 2]) % 2 == 1)
				printf("%d %.1lf %d", maxa, (double)((a[n / 2 - 1] + a[n / 2]) / 2.0), mina);       //注意中位数的小数
		else
				printf("%d %d %d", maxa, (a[n / 2 - 1] + a[n / 2]) / 2, mina);
	}
	return 0;
}
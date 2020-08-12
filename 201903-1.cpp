/*
 * @Description: CCF 201903-1题
 * @Author: pop
 * @E-mail: pop929@qq.com
 * @Date: 2020-08-10 20:03:01
 * @Version: 1.0.1
 * @LastEditTime: 2020-08-10 21:34:52
 */ 

/*
[题目描述]
    老师给了你n个整数组成的测量数据，保证有序(可能为升序或降序)，可能存在重复的数据。
请统计出这组测量数据中的最大值、中位数以及最小值，并按照从大到小的顺序输出这三个数。
*/

#include<iostream>
using namespace std;


int main()
{
    int n,*x,max,min,temp;
    cin>>n;
    x=new int[n];
    for(int i=0;i<n;i++){
        cin>>x[i];
    }
    max=x[0];
    min=x[n-1];
    if(max<min){
        temp=max;
        max=min;
        min=temp;
    }
    if(n%2==1){
        cout<<max<<" "<<x[n/2]<<" "<<min;
    }else{
        if(((x[n/2-1]+x[n/2])%2)==1){
            printf("%d %.1lf %d",max,(x[n/2-1]+x[n/2])/2.0,min);
        }else{
            cout<<max<<" "<<(x[n/2-1]+x[n/2])/2<<" "<<min;
        }
    }
    delete[] x;
    return 0;
}
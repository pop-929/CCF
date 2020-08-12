/*
 * @Description: 
 * @Author: pop
 * @E-mail: pop929@qq.com
 * @Date: 2020-08-12 20:49:13
 * @Version: 1.0.1
 * @LastEditTime: 2020-08-12 22:16:12
 */
/*
[问题描述]
    一次放学的时候，小明已经规划好了自己回家的路线，并且能够预测经过各个路段的时间。同时,小明通过学校里安
装的“智慧光明”终端，看到了出发时刻路上经过的所有红绿灯的指示状态。请帮忙计算小明此次回家所需要的时间。
[输入格式]
    输入的第一行包含空格分隔的三个正整数r、y、g，表示红绿灯的设置。这三个数均不超过10^6。
    输入的第二行包含一个正整数n,表示小明总共经过的道路段数和路过的红绿灯数目。
    接下来的n行，每行包含空格分隔的两个整数k、t。k=0表示经过了一段道路，将会耗时t秒，此处t不超过10^6; 
k=1、2、3时，分别表示出发时刻，此处的红绿灯状态是红灯、黄灯、绿灯，
且倒计时显示牌上显示的数字是t,此处t分别不会超过r、y、g。
[输出格式]
    输出一个数字，表示此次小明放学回家所用的时间。
[注意事项]
    数据类型确定好。题目中清楚的描述了【所有测试点保证 n ≤ 10^5】。
题目中可能出现的最大的数为10^6*10^5=10^11，int型最大表示的数是2147483647=2*10^9，表示不了，
所以需要用大点的类型，如long long 或者是unsigned long long。long long最大存储范围是10^18。
*/

#include<iostream>
using namespace std;

int main()
{
    long long r,y,g,t,k,tn=0,n,light,tt;
    cin>>r>>y>>g>>n;
    for(int i=0;i<n;i++){
        cin>>k>>t;
        if(k==0){
            tn+=t;
        }else{
            //tt为出发时刻相对与红绿灯循环开始时的时间，即红绿灯的0时刻
            switch (k){
                case 1:tt=r-t;      break;
                case 2:tt=r+y+g-t;  break;
                case 3:tt=r+g-t;    break;
            }
            light=(tn+tt)%(r+y+g);//距离最近的红灯亮起的时间
            if(light<=r){//红灯
                tn+=r-light;
            }else if(light>=r+g){//黄灯
                tn+=r+y+g-light+r;
            }
        }
    }
    cout<<tn;
    return 0;
}
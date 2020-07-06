/*
 * @Description: CCF 201912-1题
 * @Author: pop
 * @E-mail: pop929@qq.com
 * @Date: 2020-07-05 21:36:21
 * @Version: 1.0.1
 * @LastEditTime: 2020-07-05 23:49:28
 */ 

/*
[题目描述]
甲乙丙丁决定玩一个报数的游戏来打发时间。游戏规则为四个人从1开始轮流进
行报数，但如果需要报出的数是7的倍数或含有数字7则直接跳过。
此外大家约定，在总共报出了n个数后(不计入被跳过的数)游戏结束。现在需要
你来帮忙统计，游戏过程中每个人各自跳过了几次。.
*/
#include<iostream>

//是否是7的倍数或含有数字7 是则返回true
bool ignore(int i)
{
	//是7的倍数
	if(i%7==0){
		return true;
	}
    while(i>6){
        //对i逐位查看是否含有7
        if(i%10==7){
            return true;
        }
        i/=10;
    }
    return false;
}

int main()
{
    int in,nmb=7,i;
    std::cin>>in;
    int list[4]={0};
    for(i=7;nmb<=in;i++){
        if(ignore(i)){
            ++list[(i-1)%4];
        }else{
            ++nmb;
        }
    }
    for(int i=0;i<4;i++){
        std::cout<<list[i]<<std::endl;
    }
    return 0;
}
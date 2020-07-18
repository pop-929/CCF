/*
 * @Description: 
 * @Author: pop
 * @E-mail: pop929@qq.com
 * @Date: 2020-07-18 19:43:03
 * @Version: 1.0.1
 * @LastEditTime: 2020-07-18 20:35:48
 */ 
/*
【题目描述】
    小明在他的果园里种了一些苹果树。为了保证苹果的品质，在种植过程中要进行若干轮疏果操作，
也就是提前从树上把不妤的苹果去掉。第一轮疏果操作开始前，小明记录了每棵树上苹果的个数。
每轮疏果操作时，小明都记录了从每棵树上去掉的苹果个数。在最后一轮疏果操作结束后，请帮助小明统计相关的信息
*/

#include<iostream>
using namespace std;


int main(){
    int N,M;//苹果树和疏果操作轮数
    cin>>N>>M;
    int id=0,P=0,input,apples=0,down;

    for(int i=0;i<N;i++){
        cin>>input;
        apples+=input;
        down=0;
        for(int j=0;j<M;j++){
            cin>>input;
            down+=input;
        }
        apples+=down;
        if(down<P){
            P=down;
            id=i;
        }
    }

    cout<<apples<<" "<<id+1<<" "<<-P;
    return 0;
}
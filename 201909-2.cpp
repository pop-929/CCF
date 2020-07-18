/*
 * @Description: 
 * @Author: pop
 * @E-mail: pop929@qq.com
 * @Date: 2020-07-18 20:39:53
 * @Version: 1.0.1
 * @LastEditTime: 2020-07-18 22:09:49
 */ 
/*
【题目描述】
    小明在他的果园里种了一些苹果树，这些苹果树排列成一个圆。为了保证苹果的品质，在种植过程中要进行疏果操作。
为了更及时地完成疏果操作，小明会不时地检査每棵树的状态，根据需要进行疏果。
检査时，如果发现可能有苹果从树上掉落，小明会重新统计树上的苹果个数
（然后根据之前的记录就可以判断是否有苹果掉落了）。在全部操作结束后，请帮助小明统计相关的信息。
*/
#include<iostream>
#include<vector>
using namespace std;

int main(){
    int N;//苹果树棵树
    cin>>N;
    vector<bool> drop(N);//是否掉落
    int input,apples=0,down=0,E=0,apple;
    for(int i=0;i<N;i++){
        drop[i]=false;
        cin>>input;
        int n=input-1;
        cin>>apple;
        down=0;
        for(int j=0;j<n;j++){
            cin>>input;
            //重新统计了苹果个数
            if(input>0){
                //重新统计之前 减去 疏果的个数 不等于 新统计的苹果个数，表明有苹果掉落了
                if(apple+down!=input){
                    drop[i]=true;
                }
                down=0;
                apple=input;
            }else{
                down+=input;
            }
        }
        apple+=down;
        apples+=apple;
    }
    down=0;
    for(int i=1;i<N-1;i++){
        if(drop[i]){
            down++;
            if(drop[i+1]&&drop[i-1]){
                ++E;
            }
        }
    }
    if(drop[0]){
        down++;
        if(drop[1]&&drop[N-1]){
            ++E;
            if(drop[N-2]){
                ++E;
            }
        }
    }
    if(drop[N-1]){
        ++down;
    }
    if(E==down){
        E-=2;
    }
    
    cout<<apples<<" "<<down<<" "<<E;
    return 0;
}
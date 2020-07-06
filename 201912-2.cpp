/*
 * @Description: CCF 201912-2题
 * @Author: pop
 * @E-mail: pop929@qq.com
 * @Date: 2020-07-06 21:10:22
 * @Version: 1.0.1
 * @LastEditTime: 2020-07-07 00:49:07
 */ 

/*
[题目描述]
通过无人机航拍我们已经知晓了n处尚待清理的垃圾位置，其中第i (1≤i≤n)处的坐标为(x, y;),保证所有的坐标均为整数。
我们希望在垃圾集中的地方建立些回收站。具体来说，对于一个位置(x,y)是否适合建立回收站，我们主要考虑以下几点:
●(x,y)必须是整数坐标，且该处存在垃圾; 
●上下左右四个邻居位置，即(x,y+1)、(x,y-1)、 (x+1,y) 和(x-1,y)处，必须全部存在垃圾:
●进一步地，我们会对满足上述两个条件的选址进行评分，分数为不大于4的自然数，表示在(x±1,y±1)四个对角位置中有几处存在垃圾。
现在，请你统计一下每种得分的选址个数。
*/
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct coordinates
{
    int x,y;
};

//根据x坐标由小到大排序
bool operator < (const coordinates &a,const coordinates &b){
        if(a.x==b.x) return a.y<b.y;
        else return a.x<b.x;
    }

int near(vector<coordinates>::iterator now,int xb)
{
    int count=0;
    vector<coordinates>::iterator p=now-1;
    bool left=false,right=false,up=false,down=false;
    //cout<<"\nxb:"<<xb<<" now("<<now->x<<","<<now->y<<")";
    //如果now前面的横坐标为x-1或x
    while(p->x==(now->x-1)||p->x==now->x){
        //cout<<"  p("<<p->x<<","<<p->y<<")";
        //y比自己小1以上就跳过
        if(p->y<(now->y-1)){
            //cout<<"  跳过p("<<p->x<<","<<p->y<<") now.y-1="<<(now->y-1);
            --p;
            continue;
        }
        //横坐标为x
        if(p->x==now->x){
            //在now的下面
            if(p->y==(now->y-1)){
                down=true;
                //cout<<" -down- ";
            }
            //在now的上面
            if(p->y==(now->y+1)){
                up=true;
                //cout<<" -up- ";
            }
        }
        //横坐标为x-1
        else{
            //在同一y轴上
            if(p->y==now->y){
                left=true;
                //cout<<" -left- ";
            }
            if(p->y==(now->y-1)){
                ++count;
            }
            if(p->y==(now->y+1)){
                ++count;
            }
        }
        --p;
    }
    //cout<<"  ++前面的找完了++  ";
    if(!left) return -1;
    //如果now后面的横坐标为x+1
    p=now+1;
    while(p->x==(now->x+1)||p->x==now->x){
        //cout<<"  p("<<p->x<<","<<p->y<<")";
        //y比自己大1以上就不用找了
        if(p->y>(now->y+1)){
            //cout<<"  跳过p("<<p->x<<","<<p->y<<") now.y+1="<<(now->y+1);
            ++p;
            continue;
        }
        //横坐标为x
        if(p->x==now->x){
            //在now的下面
            if(p->y==(now->y-1)){
                down=true;
                //cout<<" -down- ";
            }
            //在now的上面
            if(p->y==(now->y+1)){
                up=true;
                //cout<<" -up- ";
            }
        }
        else{
            if(p->y==now->y){
                right=true;
                //cout<<" -right- ";
            }
            if(p->y==(now->y-1)){
                ++count;
            }
            if(p->y==(now->y+1)){
                ++count;
            }
        }
        ++p;
    }
    //cout<<" --left-- "<<left<<" --right "<<right<<" --up "<<up<<" --down "<<down;
    if(left&&right&&up&&down) return count;
    return -1;
}

int main()
{
    int n,k;
    cin>>n;
    vector<coordinates> site(n);
    vector<int> score(n);
    for(int i=0;i<n;i++){
        cin>>site[i].x>>site[i].y;
    }
    sort(site.begin(),site.end());
    // for(int i=0;i<n;i++){
    //     cout<<site[i].x<<"  "<<site[i].y<<endl;
    // }
    for(int i=2;i<n;i++){
        k=near(site.begin()+i,i);
        if(k!=-1){
            ++score[k];
        }
    }
    //cout<<endl;
    for(int i=0;i<5;i++){
        cout<<score[i]<<endl;
    }
    return 0;
}
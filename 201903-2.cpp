/*
 * @Description: CCF 201903-1题
 * @Author: pop
 * @E-mail: pop929@qq.com
 * @Date: 2020-08-10 21:39:28
 * @Version: 1.0.1
 * @LastEditTime: 2020-08-11 00:09:22
 */

/*
[题目背景]
    二十四点是一款著名的纸牌游戏，其游戏的目标是使用3个加减乘除运算使得4张纸牌上数字的运算结果为24。
[题目描述]
    定义每一一个游戏由4个从1-9的数字和3个四则运算符组成，保证四则运算符将数字两两隔开，
不存在括号和其他字符，运算顺序按照四则运算顺序进行。其中加法用符号+表示，减法用符号二表示，
乘法用小写字母x表示，除法用符号L表示。在游戏里除法为整除，例如2/3=0，3/2=1,4/2=2。
老师给了你n个游戏的解，请你编写程序验证每个游戏的结果是否为24。
[输入格式]
    从标准输入读入数据。
    第一行输入一个整数n，从第2行开始到第n+1行中，每一行包含一个长度为7
的字符串，为上述的24点游戏，保证数据格式合法。
[输出格式]
    输出到标准输出。
    包含n行，对于每一个游戏，如果其结果为24则输出字符串Yes,否则输出字符串No。
*/

#include<iostream>
#include<string>
using namespace std;

bool judge(string &str);
int calculate(string &str,int i);

int main()
{
    string str;
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>str;
        if(judge(str)) cout<<"Yes\n";
        else cout<<"No\n";
    }
    return 0;
}

int calculate(char ch,int a,int b)
{
    switch (ch)
    {
    case '+':return a+b;
    case '-':return a-b;
    case 'x':return a*b;
    case '/':return a/b;
    }
}

bool judge(string &str)
{
    int n1=str[0]-'0',n2=str[2]-'0',n3=str[4]-'0',n4=str[6]-'0';
    int a,b,c,result;//三处的算符优先级
    char opa=str[1],opb=str[3],opc=str[5];
    a=(opa=='x'||opa=='/')?1:0;
    b=(opb=='x'||opb=='/')?1:0;
    c=(opc=='x'||opc=='/')?1:0;
    if(a==b){//a，b运算符相等
        if(a<c){//a，b是加减，c是乘除 c,a,b
            c=calculate(opc,n3,n4);
            a=calculate(opa,n1,n2);
            result=calculate(opb,a,c);
        }else{//a，b是乘除，c是加减 或都相等，运算顺序就是从左往右
            a=calculate(opa,n1,n2);
            b=calculate(opb,a,n3);
            result=calculate(opc,b,n4);
        }
    }else if(a>b){//b为加减a为乘除 不管c为什么 顺序一定可以用a，c，b
        a=calculate(opa,n1,n2);
        c=calculate(opc,n3,n4);
        result=calculate(opb,a,c);
    }else{//a<b的情况 此时b为乘除，a为加减，不管c是什么，顺序一定可以用b，c，a
        b=calculate(opb,n2,n3);
        c=calculate(opc,b,n4);
        result=calculate(opa,n1,c);
    }
    return result==24?true:false;
}
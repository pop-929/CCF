/*
 * @Description: CCF 201912-3题
 * @Author: pop
 * @E-mail: pop929@qq.com
 * @Date: 2020-07-07 19:08:33
 * @Version: 1.0.1
 * @LastEditTime: 2020-07-08 20:30:23
 */ 

/*
化学方程式，也称为化学反应方程式，是用化学式表示化学反应的式子。给出一组化学方程式，
请你编写程序判断每个方程式是否配平(也就是方程式中等号左右两边的元素种类和对应的原子个数是否相同)。
本题给出的化学方程式由大小写字母、数字和符号(包括等号=、加号+、左圆括号(和右圆括号))组成，
不会出现其他字符(包括空白字符，如空格、制表符等)。化学方程式的格式与化学课本中的形式基本相同
(化学式中表示元素原子个数的下标用正常文本，如H2O写成H20)，用自然语言描述如下:
    ●化学方程式由左右两个表达式组成，中间用一个等号=连接，如2H2+02=2H20;
    ●表达式由若干部分组成，每部分由系数和化学式构成，部分之间用加号+连接，如2H2+02、2H20;
    ●系数是整数或空串，如为空串表示系数为1; .
    ●整数由一个或多个数字构成; .
    ●化学式由若干部分组成，每部分由项和系数构成，部分之间直接连接，如H20、C02、ca(0H)2、 Ba3(P04)2;
    ●项是元素或用左右圆括号括起来的化学式，如H、Ca、 (0H)、 (P04); .
    ●元素可以是一个大写字母，也可以是一个大写字母跟着一一个小写字母，如H、0、Ca。

用巴科斯范式(Backus-Naur form, BNF) 给出的形式化定义如下:
<equation> ::= <expr> "=" <expr>
<expr> ::= <coef> <formula>| <expr> "+" <coef> <formula>
<coef> ::= <digits>| " .
<digits> ::= <digit>| <digits> <digit>
<digit> ::= "0"| "1" | ...1 "9"
<formula> ::= <term> <coef>| <formula> <term> <coef>
<term> ::= <element>| "(" <formula> ")"
<element> ::= <uppercase>| <uppercase> <lowercase>
<uppercase> ::= "A"| "B" | ... | "Z"
<lowercase> ::= "a"| "b”| ...1 "z"
*/
/*用string做容器
首先将string用site=find_last_of找到‘=’的位置。再根据返回的site使用substr分成两部分
（可能需要在开后结尾加‘括号’来满足递归要求）
用map存储元素
从前往后扫，递归定义
括号：遇到‘（’进入函数，‘）’退出函数，并判断后面的字符，若为数字，map里面所有元素乘以该数字，
若为字母或括号，则map里的值不变
元素：大写开头，如果下一字符为小写，则仍为该元素，若为大写，则判断为其他元素，若为数字，则为元素个数
*/
#include<iostream>
#include<string>
#include<vector>
#include<map>
using namespace std;

bool judge(string& chemical);
void split(const string& str,vector<string> &result);

struct equation
{
    vector<int> site;//右括号位置表
    vector<string> left,right;
    map<string,int> ato_left,ato_right;
    map<string,int> calculate(const string & str);
    void calculate_all(const vector<string> & singal,bool is_left);
    void display(map<string,int> &ato){
        for(auto item:ato){
            cout<<"{"<<item.first<<","<<item.second<<"} , ";
        }
        cout<<endl;
    }
    ~equation(){
        site.clear();
        left.clear();right.clear();
        ato_left.clear();ato_right.clear();
    }
};


int main()
{
    int n;
    cin>>n;
    vector<string> equations(n);
    for(int i=0;i<n;i++){
        cin>>equations[i];
    }
    for(int i=0;i<n;i++){
        bool result=judge(equations[i]);
        if(result) cout<<"Y\n";
        else cout<<"N\n";
    }
    return 0;
}

bool judge(string& chemical)
{
    int site=chemical.find_last_of("=");
    equation eq;
    map<string,int> temp;
    split(chemical.substr(0,site),eq.left);
    split(chemical.substr(site+1),eq.right);
    eq.calculate_all(eq.left,true);
    //eq.display(eq.ato_left);
    eq.calculate_all(eq.right,false);
    //eq.display(eq.ato_right);
    if(eq.ato_left==eq.ato_right) return true;
    else return false;
}

bool is_capital(const char str)
{
    if(str>='A'&&str<='Z') return true;
    else return false;
}
bool is_lowercase(const char str)
{
    if(str>='a'&&str<='z') return true;
    else return false;
}
bool is_digital(const char str)
{
    if(str>='0'&&str<='9') return true;
    else return false;
}
bool is_other(const char str)
{
    if(str=='('||str==')'||str=='+')return true;
    else return false;
}

void split(const string& str,vector<string> &result)
{
    int i=0,j;
    j=str.find('+');
    if(j==string::npos){
        result.push_back(str);
    }else{
        while (j!=string::npos){
            result.push_back(str.substr(i,j-i));
            i=j+1;
            j=str.find('+',i+1);
        }
        result.push_back(str.substr(i));
    }
    /* for(int i=0;i<result.size();i++){
        cout<<"  --"<<result[i];
    } 
    cout<<endl;*/
}

map<string,int> equation::calculate(const string& str)
{
    //cout<<str<<endl;
    map<string,int> atomics;
    string atomic,digit_s;
    int n=str.size(),digit;
    for(int i=0;i<n;i++){
        if(is_capital(str[i])){
            atomic.clear();
            atomic.push_back(str[i]);
            if(is_lowercase(str[i+1])) {
                ++i;
                atomic.push_back(str[i]);
            }
            ++atomics[atomic];
        }
        else if(is_other(str[i])){
            if(str[i]==')') {//遇到右括号，需要返回这对括号里面的元素数据
                site.push_back(i+1);//记录右括号后一字符的位置
                break;
            }
            else if(str[i]=='('){
                //site.push_back(0);
                map<string,int> result= calculate(str.substr(i+1));//走完这条代码就是遇到右括号了
                i+=site.back()+1;
                site.pop_back();
                //cout<<"出来之后i="<<i<<endl;
                //本对括号之后是数字的话，就将括号内的元素乘以该数字再加
                if(is_digital(str[i])){
                    digit_s.clear();
                    while(is_digital(str[i])){
                        digit_s.push_back(str[i]);
                        ++i;
                        digit=stoi(digit_s);
                    }
                    --i;
                    for(auto item:result){
                        atomics[item.first]+=item.second*digit;
                    }
                }//是非数字就不用乘直接加
                else{
                    for(auto item:result){
                        atomics[item.first]+=item.second;
                    }
                }
            }
        }else{
            digit_s.clear();
            while(is_digital(str[i])){
                digit_s.push_back(str[i++]);
            }
            if(!digit_s.empty()){
                digit=stoi(digit_s);
                atomics[atomic]+=digit-1;
            }
            --i;
        }
    }
    return atomics;
}

void equation::calculate_all(const vector<string> & singal,bool is_left)
{
    map<string,int> result;
    int n,digit;
    string digit_s;
    for(int i=0;i<singal.size();i++){
        n=0;
        //如果是数字开头，则需要翻倍
        if(is_digital(singal[i][n])){
                digit_s.clear();
            while(is_digital(singal[i][n])){
                digit_s.push_back(singal[i][n]);
                ++n;
                digit=stoi(digit_s);
            }
            result=calculate(singal[i].substr(n));
            for(auto item:result){
                if(is_left) ato_left[item.first]+=item.second*digit;
                else ato_right[item.first]+=item.second*digit;
            }
        }//是非数字就不用乘直接加
        else{
            result=calculate(singal[i]);
            for(auto item:result){
                if(is_left) ato_left[item.first]+=item.second;
                else ato_right[item.first]+=item.second;
            }
        }
    }
}
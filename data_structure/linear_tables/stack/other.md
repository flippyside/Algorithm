
```cpp
#include<iostream>
#include<cstring>
using namespace std;
typedef unsigned long long ull;
const int N = 1e6, K = 1e4 * 3 + 10;
char stk1[N], tt1 = -1;
char stk2[N], tt2 = -1;

// 对于每一个右括号，找它左边还没被弹掉的左括号，如果可以匹配，则出栈，否则补全该括号。
/*
()[()]
])) 
([(
()
]) 
([
()[
]) 
([
()[()]
*/
string f(string s){
    int len=s.size();
    for(int i=len-1;i>=0;i--){
        if(s[i] == ')'||s[i] == ']'){
            stk1[++tt1] = s[i];
        }else{
            stk2[++tt2] = s[i];
        }
    }
    string ans;
    while(tt1>=0){
        char c1 = stk1[tt1--];
        char c2 = stk2[tt2];
        if((c2=='('&&c1==')') || (c2=='['&&c1==']')){
            ans+= (c2+c1);
            tt2--;
        }else{
            int tmp = tt2-1;
            while(tmp>=0){
                if((stk2[tmp]=='('&&c1==')') || (stk2[tmp]=='['&&c1==']')){
                    
                }
            }
        }

    }
}

int main(){
    string s;
    cin>>s;
}
```
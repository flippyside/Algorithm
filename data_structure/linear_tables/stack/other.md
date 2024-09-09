index
- 括号序列


# 括号序列

```t
problem: 给定一个全是括号的字符串，使其变成一一配对的平衡括号序列。如果不匹配，就在它旁边加一个括号使其匹配。
([()->()[]()
```

思路：
从前往后遍历。
- 遇到前括号就入栈，遇到后括号就把它和栈顶的前括号匹配。
    - 如果匹配，就给他俩一个标记，并将栈顶pop。
    - 如果不匹配就继续。
输出时，如果没有标记，就补全后输出。否则直接输出。

```cpp
const int N = 1e6;
struct P{
    char c;
    int idx;
}stk[N];   

int tt = -1;
bool st[N];

void f(string s){
    int len=s.size(), cnt = 0;
    char c;
    string ans = s;
    for(int i=0;i<len;i++){
        c = s[i];
        if(c == '(' || c == '['){
            stk[++tt].c = c;
            stk[tt].idx = i;
        }
        else{
            char top = stk[tt].c;
            int idx = stk[tt].idx;
            if((top=='['&&c==']')||(top=='('&&c==')')){
                tt--; // 弹出左括号
                st[i] = true; st[idx] = true;
            }
        }
    }
    for(int i = 0; i < len; i++){
        if(st[i]) cout << s[i];
        else{
            if(s[i]=='(' || s[i]==')')cout<<"()";
            if(s[i]=='[' || s[i]==']')cout<<"[]";
        }
    }
}

int main(){
    string s;
    cin>>s;
    f(s);
}
```

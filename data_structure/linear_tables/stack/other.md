index
- 匹配括号序列
- 验证栈序列


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


# 验证栈序列

```
problem: 给定一个数字n代表栈的大小，然后输入两行数字，第一行代表入栈序列，第二行代表出栈序列。询问这两组序列操作是否满足栈的性质。共询问q次。
```

思路：
- 用两个数组存储push、pop序列
- 用stk模拟：遍历push数组并将其推进stk，如果栈顶等于当前popped的元素，就弹出栈顶。否则继续push。
- push完所有数字后，检查栈是否为空。如果为空，说明满足栈的性质。

```cpp
int stk[N];
int pushed[N], popped[N];
int main(){
    int q; cin >> q;
    while(q--){
        // initialize
        int n; cin >> n;
        int x, tt = -1;
        memset(stk, 0, sizeof stk);
        memset(pushed, 0, sizeof pushed);
        memset(popped, 0, sizeof popped);
        // input
        for(int i = 0; i < n; i++){
            cin >> x;
            pushed[i] = x;
        }
        for(int i = 0; i < n; i++){
            cin >> x;
            popped[i] = x;
        }
        // Simulate stack
        int i = 0, idx = 0;
        for(int i = 0; i < n; i++){
            stk[++tt] = pushed[i];
            while(stk[tt] == popped[idx]){
                tt--;
                idx++;
                if(tt < 0) break; // stack is empty
            }
        }
        if(tt >= 0) cout << "No" << endl; // stack is not empty
        else cout << "Yes" << endl;
    }
}
```


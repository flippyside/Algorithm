index
- 前缀表达式
- 后缀表达式
- 中缀表达式
- 表达式转换

# 前缀表达式

3*(5-2)+7 -- +*3.-5.2.7@

数据结构：栈
从右往左扫描表达式：
- 遇到数字就压入栈，
- 遇到运算符就弹出栈的两个数字，「栈顶」 运算 「次栈顶」
- 运算结果压入栈。





# 后缀表达式

```
P1449 计算后缀表达式 reverse polish notation RPN
所谓后缀表达式是指这样的一个表达式：式中不再引用括号，运算符号放在两个运算对象之后，所有计算按运算符号出现的顺序，严格地由左而右新进行（不用考虑运算符的优先级）。
本题中运算符仅包含 +-*/。保证对于 / 运算除数不为 0。特别地，其中 / 运算的结果需要**向 0 取整**（即与 C++ `/` 运算的规则一致）。
如：3*(5-2)+7 对应的后缀表达式为：3.5.2.-*7.+@。在该式中，`@` 为表达式的结束符号。`.` 为操作数的结束符号。
```

数据结构：栈
从左往右扫描后缀表达式：
- 遇到数字就压入栈，
- 遇到运算符就弹出栈的两个数字，「次栈顶」 运算 「栈顶」
- 运算结果压入栈。

```cpp
int stk[N], tt = -1;

int string_to_num(string s){
    int len = s.size();
    int idx = 1, res = 0;
    for(int i = len - 1; i >= 0; i--){
        res += (s[i] - '0') * idx;
        idx *= 10;
    }
    return res;
}// 或者直接用 int num = stoi(s);

int cal_RPN(char exp[]){
    int len = strlen(exp);
    for(int i = 0; i < len; i++){
        // number
        if('0' <= exp[i] && exp[i] <= '9'){
            int num = 0, idx = 1;
            string tmp;
            while(exp[i] != '.'){
                tmp += exp[i];
                i++;
            }
            num = string_to_num(tmp);
            stk[++tt] = num;
        }
        if(exp[i] == '@') break; // boarder
        if(exp[i] == '.') continue;
        int b = stk[tt--], a = stk[tt--]; 
        switch(exp[i]){
            case '+': {stk[++tt] = a + b; break;}
            case '-': {stk[++tt] = a - b; break;}
            case '*': {stk[++tt] = a * b; break;}
            case '/': {stk[++tt] = a / b; break;}
        }
    }
    return stk[tt];
}
int main(){
    char s[N];
    cin >> s;
    cout << cal_RPN(s);
}
```

# 中缀表达式

1. 只有+与*的表达式：直接压栈，同时考虑乘的优先级

> tips:题目要求结果`只保留后n位`，就在全部运算式上 `%1en`

```cpp
求表达式的值
const int MOD = 1e4;

int stk[N], tt = -1;

ull cal_expression(){
    ull num; char op;
    cin >> num;
    stk[++tt] = num % MOD;
    while(cin >> op >> num){
        if(op == '*'){
            stk[tt] = stk[tt] * num % MOD;
        }
        else(op == '+') stk[++tt] = num % MOD; 
    }  
    ull res = 0;
    while(tt > -1)
        res = (res + stk[tt--]) % MOD;
    return res;
}
// 1+1*3+4
int main(){
    cout << cal_expression();
}
```

中缀转前缀：



index

- 前缀表达式
- 后缀表达式
- 中缀表达式
- 表达式转换

# 前缀表达式

形式：+AB

3*(5-2)+7 -- +*3.-5.2.7@

数据结构：栈
从右往左扫描表达式：

- 遇到数字就压入栈，
- 遇到运算符就弹出栈的两个数字，「栈顶」 运算 「次栈顶」
- 运算结果压入栈。

# 后缀表达式

形式：AB+

数据结构：栈

从左往右扫描后缀表达式：

- 遇到数字就压入栈，
- 遇到运算符就弹出栈的两个数字，「次栈顶」 运算 「栈顶」
- 运算结果压入栈。

```
P1449 计算后缀表达式 reverse polish notation RPN
所谓后缀表达式是指这样的一个表达式：式中不再引用括号，运算符号放在两个运算对象之后，所有计算按运算符号出现的顺序，严格地由左而右新进行（不用考虑运算符的优先级）。
本题中运算符仅包含 +-*/。保证对于 / 运算除数不为 0。特别地，其中 / 运算的结果需要**向 0 取整**（即与 C++ `/` 运算的规则一致）。
如：3*(5-2)+7 对应的后缀表达式为：3.5.2.-*7.+@。在该式中，`@` 为表达式的结束符号。`.` 为操作数的结束符号。
```

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

# 求中缀表达式

形式：A+B

## 只有+与*的表达式

直接压栈，同时考虑乘的优先级

> tips:题目要求结果 `只保留后n位`，就在全部运算式上 `%1en`

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

## 中缀转后缀

```
A+B*(C-D)-E/F -> ABCD-*+EF/-
```

性质：

- 操作数的顺序不变，可以直接输出
- 操作符的顺序改变，需要找到合适时机输出: 当前操作符比它前面和后面的操作符优先级都**高**时，可以输出
  - 需要用栈和优先级

操作符优先级（数字越大，优先级越高）：

- `*/%`的优先级始终高于 `+-`
- `(`在栈外的优先级最高，因为它括号里的表达式优先级高；而它在栈内的优先级最低，因为它需要让后续的括号里的内容入栈
- `)`在栈外的优先级最低，因为它预示着括号里的表达式已经全部入栈，需要计算出栈。
- 其他操作符进入栈中后优先数都升 `1`,这样可体现在中缀表达式中相同优先级的操作符**自左向右**计算的要求

栈内优先数(in stack priority)：

```
ch  #  (  */%  +-  )
isp 0  1   5   3   6
```

栈外优先数(in coming priority)

```
ch  #  (  */%  +-  )
icp 0  6   4   2   1
```

表达式用 `#`来标识开头和结尾

- 栈初始化，#入栈，左->右读取字符
  - ch为数字：输出ch，继续遍历
  - ch为操作符：比较ch的优先级icp和位于栈顶的操作符op的isp
    - icp(ch) > isp(op): ch入栈，继续遍历
    - icp(ch) < isp(op)：退栈，输出。此时ch的优先级高于它的前者和后者。
    - icp(ch) == isp(op)：(ch、op为左、右括号的情况)。退栈但不输出，若退出的是 `(`，继续遍历

```txt
A+B*(C-D)-E/F -> ABCD-*+EF/-

stk 0
+
stk 0 2
*
stk 0 3 4
(
stk 0 3 4 6
-
stk 0 3 4 1 2 
)
stk 0 3 4 1 3  1 <= 
out: ABCD-
stk 0 3 4 1  1 <=
退栈但不输出,退出的是(，故继续遍历
out: ABCD-
-
stk 0 3 4  2 <=
out: ABCD-*
out: ABCD-*+
stk 0 2
```

```cpp
// 输入表达式string类型，以#开头和结尾
const int N = 20, M = 1e5;

int isp[100], icp[100];

void init(){
    isp['#'] = 0;
    isp['('] = 1;
    isp['*'] = 5;
    isp['/'] = 5;
    isp['%'] = 5;
    isp['+'] = 3;
    isp['-'] = 3;
    isp[')'] = 6;
  
    icp['#'] = 0;
    icp['('] = 6;
    icp['*'] = 4;
    icp['/'] = 4;
    icp['%'] = 4;
    icp['+'] = 2;
    icp['-'] = 2;
    icp[')'] = 1;
}
char stk[N], tt = -1; 

bool isNum(char ch){
    return ((ch <= '9' && ch >= '0') || (ch <= 'Z' && ch >= 'A') || (ch <= 'z' && ch >= 'a'));
}

string exp(string s){
    string res;
    stk[++tt] = s[0];
    int i = 1;
    while(1){
        char ch = s[i];
        if(isNum(ch)) {
            res += ch;
            i++;
        }
        else{
            while(icp[ch] < isp[stk[tt]]){
                res += stk[tt]; tt--;
            }
            if(icp[ch] > isp[stk[tt]]) {
                stk[++tt] = ch;
                i++;
                ch = s[i];
            }
            if(icp[ch] == isp[stk[tt]]){
                if(stk[tt] == '(') i++;
                else break; // #结束符
                tt--;
            }
        }
    }
    return res;
}
// A+B*(C-D)-E/F -> ABCD-*+EF/-
int main(){
    init();
    cout << exp("#A+B*(C-D)-E/F#");
    cout << endl;
}

```

index

- 链表与邻接表
  - 单链表
  - 双链表
  - 邻接表
- 栈与队列
  - 栈
  - 队列
  - 单调栈
  - 单调队列
- KMP

# 链表与邻接表

- 单链表：邻接表：存储图、树
- 双链表：优化某些问题

## 单链表

`e[i]表示节点i的 值，ne[i]表示节点i的 next指针`

```
    head->3->5->7->9->null
idx       0  1  2  3  -1
e[0]=3 e[1]=5 e[2]=7 e[3]=9
ne[0]=1 ne[1]=2 ne[2]=3 ne[3]=-1
```

```cpp
const int N = 100010;
int head, e[N], ne[N], idx;
// head: 头节点的下标
// e[i]: 节点i的值
// ne[i]: 节点i的next指针
// idx：第idx个插入的数
// 第 k 个插入的点的下标是 k - 1

void init(){
    head = -1; idx = 0;
}

void add_to_head(int x){
    e[idx] = x;
    ne[idx] = head;
    head = idx;
    idx++;
}

// 将x插入 下标为 k（第 k + 1 个插入）的节点 的后面
void add(int k, int x){
    e[idx] = x;
    ne[idx] = ne[k];
    ne[k] = idx;
    idx++; 
}
// 删除 下标为 k（第 k + 1 个插入）的节点 的后面的点
void remove(int k){
    ne[k] = ne[ne[k]];
}

int main()
{
    int n;
    cin >> n;
    init();
    while(n--) {
        char op[2];
        int k,x;
        scanf("%s", op);
        if(op[0] == 'H') {
            scanf("%d", &x);
            add_to_head(x);
        }
        else if(op[0] == 'D'){
            scanf("%d", &k);
            if(k == 0) head = ne[head]; // 删除头节点
            else remove(k - 1);
        }
        else {
            scanf("%d%d", &k, &x);
            add(k - 1, x);
        }
    }
    for(int i = head; i != -1; i = ne[i])
        cout << e[i] << " ";
}
```

## 双链表

将idx为0、1分别作为head、tail节点，真正的节点从idx=2开始

0：head
1：tail

```cpp
int e[N], l[N], r[N] ,idx; // l[i]表示节点i的左边节点, r[i]表示节点i的右边节点

// 初始化
void init(){
    r[0] = 1, l[1] = 0;
    idx = 2;
}

// 将x插到下标为k的节点的右边
void add(int k, int x){
    e[idx] = x;
    r[idx] = r[k];
    l[idx] = k;
    l[r[k]] = idx;
    r[k] = idx;
}
// 将x插到下标为k的节点的左边：add(l[k], x)

// 将下标为k的点删除
void remove(int k){
    r[l[k]] = r[k];
    l[r[k]] = l[k];
}
```

```cpp
#include <memory.h>
using namespace std;
typedef pair<int,int> pii;

int n, m, q;
const int N = 100010;
int e[N], r[N], l[N], idx, head, tail;

void init(){
    idx = 2; head = 0; tail = 1;
    r[0] = 1;
    l[1] = 0;
}

void remove(int k){
    r[l[k]] = r[k];
    l[r[k]] = l[k];
}
void insert(int k, int x){
    e[idx] = x;
    r[idx] = r[k];
    l[idx] = k;
    l[r[k]] = idx;
    r[k] = idx;
    idx++;
}

int main(){
    cin >> m;
    init();
    while (m--)
    {
        int x, k;
        char op[2];
        cin >> op;
        if(op[0] == 'L') { cin >> x; insert(0, x); } // 在链表的最左端插入数 x
        else if(op[0] == 'R') { // 在链表的最右端插入数 x
            cin >> x;
            insert(l[1], x); // 插到 尾结点的左节点 的后面
        }
        else if(op[0] == 'D'){ // 将第 k 个插入的数删除
            cin >> k;
            remove(k + 1); // 链表从2开始。k - 1 + 2 = k + 1
        }
        else if(op[0] == 'I'){
            if(op[1] == 'L') { // 在第 k 个插入的数左侧插入一个数
                cin >> k >> x;
                insert(l[k + 1], x);
            }
            else{ // 在第 k 个插入的数右侧插入一个数
                cin >>k>>x;
                insert(k + 1, x);
            }
        }
    }
    for(int i = r[0]; i != 1; i = r[i]) cout << e[i] << " ";
}
```

## 邻接表

多个单链表组成。

```c
head[1]-> ->...
head[2]-> ->...
head[3]-> ->...
...
```

# 栈与队列

## 栈

先进后出

```cpp
int stk[N], tt;

// 插入
stk[++tt] = x;

// 弹出
tt--;

// 判断栈顶是否为空
if(tt > 0) not empty
else empty

// 栈顶
stk[tt];
```

表达式求值：

`((a * (b + c)) - d)`

- 中缀->前缀：`- ( * (a + (b  c))  d)`->`-*a+bcd`
- 中缀->后缀：`((a  (b  c) + ) * d)-`->`abc+*d-`

`((a+b)+(a+b)+(a+b))`

## 队列

先进先出

```cpp
int q[N], hh, tt = -1;

// 插入
q[++tt] = x;
// 弹出
h++;
// 判断队列是否为空
if(hh <= tt) not empty
else empty
// 取出对头元素
q[hh]
```

## 单调栈

给定一个长度为 N 的整数数列，输出每个数左边第一个比它小的数，如果不存在则输出 −1。

```cpp
int stk[N], tt = 0;

int main(){
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        int x;
        scanf("%d", &x);
        while(tt != 0 && stk[tt] >= x) tt--; // 弹出
        if(tt) printf("%d", stk[tt]);
        else printf("-1");
        stk[++tt] = x;
    }
}
```


## 单调队列

> 如果新来的那个比之前的人强，那么之前的人就出去。

给定一个长为n的数组。有一个大小为 k 的滑动窗口，它从数组的最左边移动到最右边。你只能在窗口中看到 k 个数字。每次滑动窗口向右移动一个位置。你的任务是确定滑动窗口位于每个位置时（窗口内必须有k个元素），窗口中的最大值和最小值。

思路：以最小值为例，当一个数将要进入窗口时，如果他比前面的数字更小，说明前面的数字不可能是最小值，所以可以弹出前面的数字，再将这个数字送进窗口。即，维护一个递增的队列，队头永远是最小值。
不断将索引加入窗口队列，如果窗口溢出，就弹出队头；若当前索引对应的元素小于队尾元素，就不断弹出队尾元素。将当前索引加入队列。如果窗口已经滑动过前k个元素，就可以输出队头，即为最小值。


```cpp
int n, k;
int q[N], hh = 0, tt = -1; // 双端队列，存储数组 a 中的索引
int a[N]; // 数组


int main(){
    scanf("%d", &n);
    scanf("%d", &k);
  
    for(int i = 0; i < n; i++) scanf("%d", &a[i]);

// 找max
    for(int i = 0; i < n; i++){
        if(hh <= tt && i - q[hh] + 1 > k) hh++;// 如果队列不为空且当前滑动窗口已经滑动过头部元素的索引(窗口溢出)，则将头部指针 hh 向右移动。（弹出队头）
        while(hh <= tt && a[q[tt]] >= a[i]) tt--; // 如果队列不为空且队尾元素的值大于或等于当前元素 a[i]，则移除队尾元素。
        q[++tt] = i; // 将当前元素的索引 i 添加到队列尾部。
        if(i >= k - 1) printf("%d", a[q[hh]]); // 当滑动窗口完全形成时（即 i >= k - 1），输出当前窗口中的最小值（即队列头部元素对应的值 a[q[hh]]）。
    }

    hh = 0, tt = -1;
    for(int i = 0; i < n; i++){
        if(hh <= tt && i - k + 1 > q[hh]) hh++;
        while(hh <= tt && a[q[tt]] <= a[i]) tt--;
        q[++tt] = i;
        if(i >= k - 1) printf("%d", a[q[hh]]);
    }
}
```

# KMP

前缀函数（数组π）：已知字符串s，π[i] = 子串s[0]~s[i]的最长的 相等的真前缀与真后缀的长度。
eg：abcabcd的前缀函数为 {0,0,0,1,2,3,0}

// 前缀函数：O(n)

int* prefix(string s){
    int* pi = new int[N];
    int len = s.size();
    for(int i = 1; i < len; i++){
        int j = pi[i - 1];
        while(j > 0 && s[i] != s[j]) j = pi[j - 1];
        if(s[i] == s[j])j++;
        pi[i] = j;
    }
    return pi;
}


```cpp
// 暴力算法
s[N], p[M]
for(int i = 1; i <= n; i++){
    bool flag = true;
    for(int j = 1; j <= m; j++){
        if(s[i] != p[j]) {
            flag = false;
            break;
        }
    }
}
```

`next[i] = k 意为 p[1, k] = p[i - k + 1, i]`

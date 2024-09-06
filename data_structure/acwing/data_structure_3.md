# 哈希表

index
- basic
- 拉链法
- 开放寻址法
- 字符串前缀哈希法

## basic

1. 存储结构：
   - 开放寻址法
   - 拉链法
2. 字符串哈希方式

哈希函数：h(x)
- 值域(0, a)
- h(x) = x mod a (a为质数，且距离2的n次方较远)
- 冲突


```
维护一个集合，支持如下几种操作：

I x，插入一个整数 x
Q x，询问整数 x 是否在集合中出现过；
进行 N 次操作，对于每个询问操作输出对应的结果。

输入格式
第一行包含整数 N，表示操作数量。

接下来 N 行，每行包含一个操作指令，操作指令为 I x，Q x 中的一种。

输出格式
对于每个询问指令 Q x，输出一个询问结果，如果 x 在集合中出现过，则输出 Yes，否则输出 No。
```

## 拉链法

> 一维数组。在冲突的地方拉一条链

```
h(11) = 3
h(23) = 3

0 1 2 3 4 ...
      11
      23
```

```cpp
const int N = 100003;
int h[N], e[N], ne[N], idx;

void insert(int x){
    int k = (x % N + N) % N; // 防止为负数
    // 将x插入k引申的链中
    e[idx] = x;
    ne[idx] = h[k];
    h[k] = idx++;
}

bool find(int x){
    int k = (x % N + N) % N;
    for(int i = h[k]; i != -1; i = ne[i])
        if(e[i] == x) return true;
    return false;
}

int main(){
    int n;
    scanf("%d", &n);
    memset(h, -1, sizeof(h)); // h[i] = -1表示 i 的链子中没有任何元素
    while(n--){
        char op[2];
        int x;
        scanf("%s%d", op, &x);
        if(op[0] == 'I') insert(x);
        else{
            if(find(x)) puts("Yes");
            else puts("No");
        }
    }
}
```

## 开放寻址法

> 一维数组。遇到冲突就换个地方。


```cpp
const int N = 200003, null = 0x3f3f3f3f; // null为标志位

int h[N], e[N], ne[N], idx;

bool find(int x){
    int k = (x % N + N) % N;
    while(h[k] != null && h[k] != x){ // h[k]有人且不是x
        k++;
        if(k == N) k = 0; // 循环
    }
    return k; // 返回无人的位置 or x的位置
}

int main(){
    int n;
    scanf("%d", &n);
    memset(h, 0x3f, sizeof(h)); // h[i] = -1表示 i 的链子中没有任何元素
    while(n--){
        char op[2];
        int x;
        scanf("%s%d", op, &x);
        int k = find(x);
        if(op[0] == 'I') h[k] = x; // 直接插入
        else{
            if(h[k] != null) puts("Yes");
            else puts("No");
        }
    }
}
```

## 字符串前缀哈希法

> 通常用于判断两个字符串是否相等

str = ABCD...

前缀的哈希值：
```
h[0] = 0
h[1] = A的哈希值
h[2] = AB的哈希值
...
```

将字符串看作 p进制数 mod m
ABCD -> ((1234)p) mod m

经验值：
p = 131 或 13331
m = 2^64 (或者直接将数据类型取成 unsigned long long，溢出就相当于取模)

通过前缀的哈希值求任意一段字符串的哈希值：
`h[k] - h[l - 1] * p^(k - l + 1)`


```
给定一个长度为 n 的字符串，再给定 m 个询问，每个询问包含四个整数 l1,r1,l2,r2
，请你判断 [l1,r1] 和 [l2,r2] 这两个区间所包含的字符串子串是否完全相同。

字符串中只包含大小写英文字母和数字。

输入格式
第一行包含整数 n 和 m，表示字符串长度和询问次数。

第二行包含一个长度为 n 的字符串，字符串中只包含大小写英文字母和数字。

接下来 m 行，每行包含四个整数 l1,r1,l2,r2，表示一次询问所涉及的两个区间。

注意，字符串的位置从 1 开始编号。

输出格式
对于每个询问输出一个结果，如果两个字符串子串完全相同则输出 Yes，否则输出 No。
```

```cpp
const int N = 100010, P = 131; // p进制

char str[N];
ull h[N], p[N]; //h[i]: 前i个字母的哈希值； p[i]：p的i次方

ull get(int l, int r){
    return h[r] - h[l - 1] * p[r - l + 1];
}

int main(){
    int n, m;
    scanf("%d%d%s", &n, &m, str + 1);
    p[0] = 1;
    for(int i = 1; i <= n; i++){
        p[i] = p[i - 1] * P;
        h[i] = h[i - 1] * P + str[i];
    }
    while(m--){
        int l1, r1, l2, r2;
        scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
        if(get(l1, r1) == get(l2, r2)) printf("Yes");
        else printf("No");
    }
}
```









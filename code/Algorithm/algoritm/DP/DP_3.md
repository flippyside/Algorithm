index

- 计数DP
- 数位统计DP
- 状态压缩DP
- 树形DP
- 记忆化搜索

# 计数类DP


# 数位DP

数位：一个数字的每一位

问题特征：

- 计数
- 提供数字区间
- 上界大

```txt
给定两个整数 a 和 b，求 a 和 b 之间的所有数字中 0∼9 的出现次数。
```

思路：

count(n, x): 求出1～n中 x 出现的次数
则结果即为 count(b, x) - count(a - 1, x)


count函数的实现：
统计数字x在每一位上出现的次数。
例如：1 ~ n，n = abcdegf，统计第 4 位上数字 1 出现的次数

- 所求数字 xxx1yyy 应满足 1 <= xxx1yyy <= abcdefg
- 分类讨论

  1. xxx < abc, 即 xxx = 001 ~ abc - 1， 此时xxx1yyy一定小于abcdefg，故yyy可以取任意值，即 yyy = 000 ~ 999。总数为 `abc*1000`
  2. xxx = abc

  - d < 1：abc1yyy一定大于abcdefg。总数为 0
  - d = 1：yyy = 000 ~ efg。总数为 `efg + 1`
  - d > 1：abc1yyy一定小于abcdefg。总数为1000。

  3. 边界条件：

  - 最高位为 1:
  - 最高位为 0：

最后，要求一个区间的答案，只需拆成两部分相减：$ans_{[l,r]}=ans_{[0,r]}-ans_{[0,l-1]}$


```cpp

```


# 树形DP

有一棵树，集合中有这个树的若干节点，不存在两个结点，其中一个是另一个的直接父节点。求集合的最大数量

- 状态表示 
  - f[u, 0]：所有以u为根的子树中选择的方案，并且**不选**u的方案
  - f[u, 1]: 所有以u为根的子树中选择的方案，并且**选择**u的方案
- 状态计算
  - $ f(u, 0) = \sum{max(f(s_i, 0), f(s_i, 1))} $ 没选根节点，它的子节点可选可不选
  - $f(u, 1) = \sum{f(s_i, 0)}$ 选了根节点，它的子节点就都不能选了


```txt
problem:
Ural 大学有 N 名职员，编号为 1∼N。
他们的关系就像一棵以校长为根的树，父节点就是子节点的直接上司。
每个职员有一个快乐指数，用整数 Hi 给出，其中 1≤i≤N。

现在要召开一场周年庆宴会，不过，没有职员愿意和直接上司一起参会。

在满足这个条件的前提下，主办方希望邀请一部分职员参会，使得所有参会职员的快乐指数总和最大，求这个最大值。
```


 ```cpp
int happy[N];
int h[N], e[N], ne[N], idx; // 用图存储树
bool has_father[N];
int f[N][2];

void add(int a, int b){
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}

void dfs(int u){
    f[u][1] = happy[u];
    for(int i = h[u]; i != -1; i = ne[i]){
        int j = e[i];
        dfs(j);
        f[u][0] += max(f[j][0], f[j][1]);
        f[u][1] += f[j][0];
    }
}

int main(){
    scanf("%d", &n);
    memset(h, -1, sizeof h);
    for(int i = 1; i <= n; i++) scanf("%d", &happy[i]);
    for(int i = 0; i < n - 1; i++){
        int a, b;
        // b is a's father
        scanf("%d%d", &a, &b);
        has_father[a] = true;
        add(b, a);
    }
    int rt = 1;
    // 找根节点
    while(has_father[rt]) rt++;
    dfs(rt);
    cout << max(f[rt][0], f[rt][1]);
}
 ```

# 记忆化搜索



```txt
problem

给定一个 R 行 C 列的矩阵，表示一个矩形网格滑雪场。

矩阵中第 i 行第 j 列的点表示滑雪场的第 i 行第 j 列区域的高度。

一个人从滑雪场中的某个区域内出发，每次可以向上下左右任意一个方向滑动一个单位距离。

当然，一个人能够滑动到某相邻区域的前提是该区域的高度低于自己目前所在区域的高度。

下面给出一个矩阵作为例子：

 1  2  3  4 5

16 17 18 19 6

15 24 25 20 7

14 23 22 21 8

13 12 11 10 9
在给定矩阵中，一条可行的滑行轨迹为 24−17−2−1
。

在给定矩阵中，最长的滑行轨迹为 25−24−23−…−3−2−1，沿途共经过 25 个区域。

现在给定你一个二维矩阵表示滑雪场各区域的高度，请你找出在该滑雪场中能够完成的最长滑雪轨迹，并输出其长度(可经过最大区域数)。
```

- 状态表示 f[i, j]
  - 集合：所有从(i, j)开始的路径
  - 属性：max
- 状态计算
  - 向上 (i,j)->(i,j-1)
  - 向下 (i,j)->(i,j+1) f[i,j] = f[i,j+1]+1
  - 向左 (i,j)->(i-1,j)
  - 向右 (i,j)->(i+1,j)

```cpp
int h[N][N]; // 高度
int f[N][N];

int dx[4] = {-1,0,1,0}, dy[4]={0,1,0,-1};
 
int dp(int x, int y){
    int &v = f[x][y];
    if(v != -1) return v; // 已经计算过

    v = 1;
    for(int i = 0; i < 4; i++){
        int a = x + dx[i], b = y + dy[i];
        // boarder judge
        if(a >= 1 && a <= n && b >= 1 && b <= m && h[a][b] < h[x][y])
            v = max(v, dp(a, b) + 1);
    }
    return v;
}

int main(){
    scanf("%d%d", &n, &m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%d", &h[i][j]);
    memset(f, -1, sizeof f);
    int res = 0;
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= m;j++)
            res = max(res, dp(i, j));
    printf("%d\n", res);
}

```

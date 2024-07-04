# DFS

深度优先。搜索到最底部时才回溯，并确保每条路都搜过

数据结构：stack

空间：O(h) h：层数

回溯

剪枝


```
给定一个整数 n，将数字 1∼n 排成一排，按照字典序将所有的排列方法输出。
```

```cpp
const int N = 8;

int n;
int path[N]; // 存储数字序列
bool st[N]; // status, 表示数字 i 已经被用过了

void dfs(int u){
    if(u == n) {
        for(int i = 0; i < n; i++) cout << path[i] << endl;
        return;
    }
    for(int i = 1; i <= n; i++){
        if(!st[i]){
            path[u] = i;
            st[i] = true;
            dfs(u + 1); // 继续深入
            st[i] = false; // 恢复现场!
        }
    }
}
int main(){
    cin >> n;
    dfs(0);
}
```

八皇后

法1: 利用“每行只能有一个皇后”这一推断

```cpp
#include <algorithm>
#include <memory.h>
using namespace std;

const int N = 20;

int n;
char g[N][N]; // 存储棋盘状态
bool co[N], dg[N], udg[N]; // co: 同一行、列 dg：同一对角线  udg：

void dfs(int u){
    if(u == n) {
        for(int i = 0; i < n; i++) cout << g[i] << endl;
        cout << endl;
        return;
    }
    for(int i = 0; i < n; i++){
        if(!co[i] && !dg[u + i] && !udg[n - u + i]){
            g[u][i] = 'Q';
            co[i] = dg[u + i] = udg[n - u + i] = true;
            dfs(u + 1); // 继续深入
            co[i] = dg[u + i] = udg[n - u + i] = false; // 恢复现场 
            g[u][i] = '.';
        }
    }
}    

// 确定最小值后，新的元素只需与最小值比较。最小值移除后，再确定一次最小值
int main(){
    cin >> n;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            g[i][j] = '.';
    dfs(0);
}
```

法2:

```cpp
int n;
char g[N][N]; // 存储棋盘状态
bool row[N], col[N], dg[N], udg[N]; // co: 同一行、列 dg：同一正对角线  udg：同一反对角线

void dfs(int x, int y, int s){ // x：行 y：列 s：已经放了几个皇后
    if(y == n) y = 0, x++;
    if(x == n){
        if(s == n) {
            for(int i = 0; i < n; i++) cout << g[i]<< endl;
            cout << endl;
        }
        return;
    }
    dfs(x, y + 1, s); // 不放皇后
    // 放皇后
    if(!row[x] && !col[y] && !dg[x + y] && !udg[x - y + n]){
        g[x][y] = 'Q';
        row[x] = col[y] = dg[x + y] = udg[x - y + n] = true;
        dfs(x, y + 1, s + 1);
        row[x] = col[y] = dg[x + y] = udg[x - y + n] = false;
        g[x][y] = '.';
    }
}
```


# BFS

广度优先。一层一层地搜

数据结构：queue

空间：O(2^h)

特点：最短路

```cpp
初始状态：queue 

while queue
    t <- 对头
    扩展 t
```


```
给定一个 n×m 的二维整数数组，用来表示一个迷宫，数组中只包含 0 或 1，其中 0 表示可以走的路，1 表示不可通过的墙壁。最初，有一个人位于左上角 (1,1) 处，已知该人每次可以向上、下、左、右任意一个方向移动一个位置。请问，该人从左上角移动至右下角 (n,m) 处，至少需要移动多少次。
```

```cpp
int n, m;
int g[N][N]; // 地图
int d[N][N]; // 每个点到起点的距离
pii q[N * N]; // 路线
pii Prev[N][N]; // 记录前一个点

int bfs(){
    int hh = 0, tt = 0;
    q[0] = {0, 0};
    memset(d, -1, sizeof(d));
    d[0][0] = 0;
    int dx[4] = {-1,0,1,0}, dy[4] = {0, 1, 0, -1}; // 向量
    while(hh <= tt){
        auto t = q[hh++]; // 取出对头
        for(int i = 0; i < 4; i++){ // 尝试向4个方向行走
            int x = t.first + dx[i], y = t.second + dy[i];
            if(x >= 0 && x < n && y >= 0 && y < m && g[x][y] == 0 && d[x][y] == -1){
                d[x][y] = d[t.first][t.second] + 1;
                Prev[x][y] = t; // (x, y) 的前一个点
                q[++tt] = {x, y}; // 走到（x， y）
            }
        }
    }
    // 输出路径
    int x = n - 1, y = m - 1;
    while (x || y)
    {
        cout << x << ' ' << y << endl;
        auto t = Prev[x][y];
        x = t.first, y = t.second;
    }
    
    return d[n-1][m-1]; // 终点
}
```


# 树和图的遍历

有向图

数据结构：
- 邻接矩阵
- 邻接表：每个顶点都有一个单链表，存有它所能到达的点。加边：在单链表里加点（通常加到头节点处）


1. 深度优先遍历

```cpp
int h[N], e[N], ne[N], idx; // h[i]: 第i个单链表
bool st[N]; // 存储点的遍历情况

void add(int a,int b){
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}

void dfs(int u){
    st[u] = true; // 已经被遍历
    for(int i = h[u]; i != -1; i = ne[i]){
        int j = e[i];
        if(!st[j]) dfs(j);
    }
}

int main(){
    memset(h, -1, sizeof(h)); // 初始化头节点
}
```




```
给定一颗树，树中包含 n 个结点（编号 1∼n）和 n−1 条无向边。请你找到树的重心，并输出将重心删除后，剩余各个连通块中点数的最大值。

重心定义：重心是指树中的一个结点，如果将这个点删除后，剩余各个连通块中点数的最大值最小，那么这个节点被称为树的重心。

输入: 第一行包含整数 n，表示树的结点数。接下来 n−1 行，每行包含两个整数 a 和 b
，表示点 a 和点 b 之间存在一条边。

输出：输出一个整数 m，表示将重心删除后，剩余各个连通块中点数的最大值。
```






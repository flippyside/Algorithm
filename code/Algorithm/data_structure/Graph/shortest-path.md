index

- Dijkstra
- bellman-ford
- spfa
- floyd
- prim
- kruskal

图的数据结构：

- 稠密图：邻接矩阵
- 稀疏图：邻接表

# 最短路问题


## 单源有向图的最短路问题（有源点）

```
图：点n 边m，可能有重边、自环
求出 1 号点到 n 号点的最短距离
```

```cpp
const int N = 100010, M = 1e6 * 2;
int n,m;
int h[N], e[M], ne[M], idx;
int q[N];
int d[N];
bool st[N];
void add(int a, int b){
    e[idx]=b;ne[idx]=h[a];h[a]=idx++;
}

int bfs(){
    // 初始化
    int hh = 0, tt = 0;
    q[tt] = 1;
    d[1] = 0;
  
    while(hh <= tt){
        int t = q[hh++];
        for(int i = h[t]; i != -1; i = ne[i]){
            int j = e[i];
            if(d[j] == -1){ // j未被遍历
                q[++tt] = j;
                d[j] = d[t] + 1;
            }
        }
    }
    return d[n];
}

int main(){
    cin >> n >> m;
    memset(h,-1,sizeof h);
    memset(d,-1,sizeof d);
    while(m--){
        int a,b;
        cin>>a>>b;
        add(a,b);
    }
    int t = bfs();
    cout << t;
}
```


n：点  m：边

- 源点：起点； 汇点：终点
- 单源最短路

  1. 边权为正：

  - 朴素Dijkstra: $O(n^2)$ ，适用于稠密图（边数大）
  - 堆优化Dijkstra: $O(mlog{n})$ ，适用于稀疏图

  2. 存在负权边：

  - bellman-ford：$O(nm)$
  - spfa： $一般为O(m)，最坏O(nm)$
- 多源汇最短路: floyd $O(n^3)$

## 单源最短路

### 朴素Dijkstra

$$
O(n^2)
$$

数据结构：邻接矩阵

思路：

1. 初始化集合S（空集），距离：d[1] = 0 , 其余为无穷
2. 遍历 0 到 n
3. 遍历 1 到 n，寻找不在集合 S 的，距离最近的点 t，并将 t 加入集合S
4. 更新 t 的邻居 j 到点 1 的距离：`d(j) = min(d(j), d(t) + w(t, j))`

```
S: 当前已确定最短距离的点的集合
dis[1] = 0, dis[i] = 无穷
for i : 0 ~ n
    t <- 不在S中的距离最近的点
    S <- t
    用 t 更新其他点的距离：查看`d(t)+w(t,i)`是否比原本的`d(i)`更小
```

```
给定一个 n 个点 m 条边的有向图，图中可能存在重边和自环，所有边权均为正值。
请你求出 1 号点到 n 号点的最短距离，如果无法从 1 号点走到 n 号点，则输出 −1。
```

```cpp
int n, m;
const int N = 510;
int g[N][N]; // 图
int dist[N]; // 距离
bool st[N]; // 该点的最短距离是否已经确定

int dijkstra(){
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;
    for(int i = 0; i < n; i++){ 
        int t = -1;
        for(int j = 1; j <= n; j++){ // 找 不在集合S中 且 距离最短的点
            if(!st[j] && (t == -1 || dist[j] < dist[t])) t = j;
        }
        st[t] = true; // 加入集合S
        for(int j = 1; j <= n; j++) // 用 t 更新其他点的距离
            dist[j] = min(dist[j], dist[t] + g[t][j]); 
    }
    if(dist[n] == 0x3f3f3f3f) return -1;
    return dist[n];
}

int main(){
    cin >> n >> m;
    memset(g, 0x3f, sizeof g);
    while(m--){
        int a,b,c;
        cin>>a>>b>>c;
        g[a][b] = min(g[a][b], c); // 存在重边，只需保留最短的边
    }
    cout << dijkstra();
}
```

### 堆优化Dijkstra

思路：在寻找 `不在S中的距离最近的点t`时，要遍历一次数组。优化：可以用小顶堆代替。

数据结构：优先队列（小顶堆）、邻接表

```cpp
int h[N], w[N], e[N], ne[N], idx; // 图
int dist[N]; // 距离
bool st[N]; // 该点的最短距离是否已经确定

void add(int a, int b, int c){
    e[idx] = b;
    ne[idx] = h[a];
    w[idx] = c;
    h[a] = idx++;
}

int dijkstra(){
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;
  
    priority_queue<pii, vector<pii>, greater<pii>> heap; // 小顶堆
    heap.push({0, 1}); // 起始点

    while(heap.size()){
        // 取出当前距离最小的点
        auto t = heap.top();
        heap.pop();

        int index = t.second, distance = t.first;
        if(st[index]) continue;
    
        st[index] = true;
        for(int i = h[index]; i != -1; i = ne[i]){
            int j = e[i];
            if(dist[j] > distance + w[i]){
                dist[j] = distance + w[i];
                heap.push({dist[j], j});
            }
        }
    }
    if(dist[n] == 0x3f3f3f3f) return -1;
    return dist[n];
}

int main(){
    cin >> n >> m;
    memset(h, -1, sizeof h);
    while(m--){
        int a,b,c;
        cin>>a>>b>>c;
        add(a, b, c);
    }
    cout << dijkstra();
}
```

### bellman-ford

$$
O(nm)
$$

针对有负权图的最短路算法，也可以判断有无负环。

数据结构：结构体数组

思想：松弛操作

```cpp
dist[u] = min(dist[u], dist[v] + w(u, v));
```

我们每进行一轮循环，就对图上所有的边都尝试进行一次松弛操作，当一次循环中没有成功的松弛操作时，算法停止。

时间复杂度：每次循环是 O(m) 的，那么最多会循环多少次呢？在最短路存在的情况下，由于一次松弛操作会使最短路的边数至少 +1，而最短路的边数最多为 n-1，因此整个算法最多执行 n-1 轮松弛操作。故总时间复杂度为 O(nm)。但还有一种情况，如果从 S 点出发，抵达一个负环时，松弛操作会无休止地进行下去。注意到前面的论证中已经说明了，对于最短路存在的图，松弛操作最多只会执行 n-1 轮，因此如果第 n 轮循环时仍然存在能松弛的边，说明从 S 点出发，能够抵达一个负环。

```
dis[1] = 0, dis[i] = 无穷
for i : 0 ~ n
    for 所有边(a, b, w)
        dist[b] = min(dist[b], dist[a] + w);
```

有[负权回路]的图不一定能用此算法求出最短路径。但如果题目 限制了边数 ，那么就可以了。

注意：需要备份dist数组上一次迭代的结果，防止出现串联。即

```cpp
dist[b] = min(dist[b], backup[a] + w);
```

```
给定一个 n 个点 m 条边的有向图，图中可能存在重边和自环， 边权可能为负数。
请你求出从 1 号点到 n 号点的最多经过 k 条边的最短距离，如果无法从 1 号点走到 n 号点，输出 impossible。注意：图中可能 存在负权回路 。
```

```cpp
struct Edge{
    int a, b, w;
}edges[M];
int dist[N]; // 距离
int backup[N]; // 备份dist数组上一次迭代的结果，防止出现串联

int bellman_ford(){
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;
    for(int i = 0; i < k; i++){
        memcpy(backup, dist, sizeof dist);
        for(int j = 0; j < m; j++){
            int a = edges[j].a, b = edges[j].b, w = edges[j].w;
            dist[b] = min(dist[b], backup[a] + w); // dist[b] = min(dist[b], dist[a] + w);
        }
    }
    return dist[n];
}

int main(){
    cin >> n >> m >> k; // 最多经过 k 条边
  
    for(int i = 0; i < m; i++){
        int a,b,c;
        cin >> a >> b >> c;
        edges[i] = {a, b, c};
    }
    int t = bellman_ford();
    if(t > 0x3f3f3f3f / 2) cout << "impossible";
    else cout << t;
} 
```

### spfa

bellman-ford的优化（用bfs的思想）。spfa也可以代替dijkstra（某些情况不行）。

数据结构：邻接表、队列

优化 `dist[b] = min(dist[b], dist[a] + w);`：只有当dist[a]变小后，dist[b]才会变小。所以可以用一个队列存储所有距离变小的点 a，然后用它更新所有的后继

```
queue <- 起点
while queue not empty{
    t <- 对头
    q.pop()
    更新 t 的所有边： （t 变小后，所有 t->b 的点 b 也会变小）
        如果 b 不在队列，就 queue <- b
}
```

```cpp
void _memset(int* d, int val, size_t size){
    for(size_t i = 0; i < size / sizeof(int); i++) d[i] = val;
}

const int N =  1e6 + 10, M = N * 2;
int n,m;
int h[N], e[N], ne[N], w[N], idx;
int d[N];
int q[N];
bool st[N];

void add(int a, int b, int c){
    e[idx] = b; ne[idx] = h[a]; w[idx] = c; h[a] = idx++;
}

int spfa(){
    int hh = 0, tt = 0;
    q[tt] = 1;
    d[1] = 0;
    while(hh <= tt){
        int t = q[hh++];
        st[t] = false;

        for(int i = h[t] ; i != -1; i = ne[i]){
            int j = e[i]; // 边 i 的目标节点
            if(d[j] > d[t] + w[i]){ // w[i]: t->j 的边的权重
                d[j] = d[t] + w[i];
                if(!st[j]){
                    q[++tt] = j;
                    st[j] = true;
                }
            }
        }
    }
    return d[n];
}

int main(){
    cin >> n >> m;
    _memset(h, -1, sizeof(h));
    _memset(d, 0x3f3f3f3f, sizeof d);
    while(m--){
        int x,y,z;
        cin>>x>>y>>z;
        add(x,y,z);
    }
    int t = spfa();
    if(t == 0x3f3f3f3f) cout << "impossible";
    else cout << t;
}
```

#### spfa求负环

思路：只需记录最短路经过了多少条边，当经过了至少 n 条边时，说明 s 点可以抵达一个负环。为了确保找到负环，必须在初始化队列时把所有点都加进来。

dist[x]：最短距离
cnt[x]：最短路的边数

dist[x] = dist[t] + w[i];
cnt[x] = cnt[t] + 1;

负环：所有边的边权和为负数的环。最短路问题的图如果出现负环，那么算法会无限次地走这个负环。

当 `cnt[x] >= n`时，由鸽笼原理，有两个点是相同的，即存在环，且由于算法是要找最小路，为负环。
只要某个点的入队数大于n，那就可以证明它在不停地松弛，也就是出现了负环。

```cpp
const int N =  1e6 + 10, M = 1e6 * 5;
int n,m;
int h[N], e[N], ne[N], w[N], idx;
int d[N];
int q[M];
bool st[N];
int cnt[M];

void add(int a, int b, int c){
    e[idx] = b; ne[idx] = h[a]; w[idx] = c; h[a] = idx++;
}

bool spfa(){
    int hh = 0, tt = -1;
    for(int i = 1; i <= n; i++){ // 把所有点都加进来
        st[i] = true;
        q[++tt] = i;
    }

    while(hh <= tt){
        int t = q[hh++];
        st[t] = false;

        for(int i = h[t] ; i != -1; i = ne[i]){
            int j = e[i];
            if(d[j] > d[t] + w[i]){
                d[j] = d[t] + w[i];

                cnt[j] = cnt[t] + 1;
                if(cnt[j] >= n) return true;

                if(!st[j]){
                    q[++tt] = j;
                    st[j] = true;
                }
            }
        }
    }
    return false;
}

int main(){
    cin >> n >> m;
    _memset(h, -1, sizeof(h));
    while(m--){
        int x,y,z;
        cin>>x>>y>>z;
        add(x,y,z);
    }
    if(spfa()) cout << "Yes";
    else cout << "No";
}
```

## 多源汇最短路

### Floyd

$$
O(n^3)
$$

数据结构：邻接矩阵

思路：三重循环 k i j。

```
d[i][j]: 存储所有的边
for k : 1, n
    for i : 1, n
        for j : 1, n
            d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
d[i][j]
```

图中不存在负权回路。

```cpp
const int N = 510, INF = 1e9;

// 稠密：邻接矩阵
int g[N][N];

// 三重循环：k i j
// d[i][j] = min(d[i][j], d[i][k] + d[k][j])
void floyd(){
    for(int k = 1; k <= n; k++)
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++)
                g[i][j] = min(g[i][j] , g[i][k] + g[k][j]);
}

int main(){
    cin>>n>>m>>k;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            if(i==j) g[i][j] = 0;
            else g[i][j] = INF;
        }
    }
    while(m--){
        int x,y,z;
        cin>>x>>y>>z;
        g[x][y] = min(g[x][y], z);
    }
    floyd();
    while(k--){
        int a,b;
        cin>>a>>b;
        if(g[a][b] > INF / 2) cout << "impossible" <<endl;
        else cout << g[a][b] <<endl;
    }
}
```

# 最大路问题

法1:
是最短路问题的相反数。
思路：建图时把权重变成相反数，然后跑最短路，最后结果取相反数即可。


法2：

```cpp
int h[N], e[N], ne[N], w[N], dis[N], idx;

int f(int n){
    dis[1] = 0;
    for(int i = 1; i <= n; i++){
        for(int j = h[i]; j != -1; j = ne[j]){
            int ve = e[j];
            dis[ve] = max(dis[ve], dis[i] + w[j]);
        }
    }
    if(dis[n] == -1e6) return -1;
    return dis[n];
}

memset(h, -1, sizeof h);
memset(w, -1e6, sizeof w);
```

注意，dis数组的初始值如果只是设置成0或者-1，就只能通过正权图的题目，因为加上负权总是会减小dis使他小于初始值。所以，要设置成负无穷，这样遇到负权边时也可以正常增大，没问题。




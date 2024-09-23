index

- 最小生成树

  - prim
    - 朴素版：稠密图 $O(n^2)$
    - 堆优化：稀疏图（较少用到） $O(mlogn)$
  - kruskal：$O(mlogm)$
- 二分图

  - ：$O(n + m)$
  - 匈牙利算法：$最坏：O(mn)，但实际运行时间一般很少$

图的数据结构：

- 稠密图：邻接矩阵
- 稀疏图：邻接表

## prim

思路：

1. 遍历n次
2. 寻找不在集合 S 的距离最近的点t
3. 将 t 加入集合 S
4. 用 t 更新点的距离。`d[j] = min(d[j], g[t][j])`

```
初始化：dist[i] <- INF
点集 S
for i : 0, n
    找到集合外距离最近的点t
    用t更新其它点到 集合 的距离
    将t加入集合
```

```cpp
const int N = 510, INF = 0x3f3f3f3f;
int g[N][N];
int dist[N];
bool st[N];

int prim(){
    memset(dist, 0x3f, sizeof dist);
    int res = 0; // 最小生成树的权重
    for(int i = 0; i < n; i++){
        // 找到集合外距离最近的点t
        int t = -1;
        for(int j = 1; j <= n; j++)
            if(!st[j] && (t == -1 || dist[j] < dist[t]))
                t = j;

        if(i && dist[t] == INF) return INF; // 没有最小生成树
        if(i) res += dist[t]; // 排除起点

        // 用t更新其它点到 集合 的距离
        for(int j = 1; j <= n; j++) dist[j] = min(dist[j], g[t][j]); // 如果t存在负自环，dist[t]会改变
  
        // 将t加入集合
        st[t] = true;
    }
    return res;
}

int main()
{
    cin>>n>>m;
    memset(g, 0x3f, sizeof g);
    while(m--){
        int u,v,w;
        cin >>u>>v>>w;
        g[u][v] = g[v][u] = min(g[u][v], w);
    }
    int t = prim();
    if(t == INF) cout << "impossible";
    else cout << t;
}
```

bug:

1. g 数组的初始化要放在main函数里，读入g之前。

## kruskal

```
1. 将边按权重从小到大排序。O(mlogm)
2. 枚举每条边(a, b, w)：如果a、b不连通，就将边ab加入集合
```

```cpp
int n, m;
const int N = 200010, INF = 0x3f3f3f3f;
int p[N]; // 并查集

struct Edge{
    int a, b, w;
    bool operator < (const Edge &W) const{
        return w < W.w;
    }
}edges[N];

int find(int x){
    if(p[x] != x) p[x] = find(p[x]);
    return p[x];
}

int main()
{
    cin>>n>>m;
    for(int i = 0; i < m; i++){
        int a, b, w;
        cin >>a>>b>>w;
        edges[i] = {a, b, w};
    }

    sort(edges, edges + m); // 排序所有边
    for(int i = 1; i <= n; i++) p[i] = i;

    int res = 0, cnt = 0;
    for(int i = 0; i < m; i++){
        int a = edges[i].a, b = edges[i].b, w= edges[i].w;
        a = find(a), b = find(b);
        if(a != b){
            p[a] = b; // 合并a、b所在的两个集合
            res += w;
            cnt++;
        }
    }
    if(cnt < n - 1) cout << "impossible";
    else cout << res;
}
```

# 判断二分图

## 染色法

原理：二分图无奇圈。

思路：
- 遍历当前顶点的邻居集
    - 如果i未染色，就对i染色。
染色：
- 首先随意选取一个未染色的点进行染色，然后尝试将它染成相反的颜色
    - 如果相邻的点已经被染色，且它的颜色与它应该被染的颜色不同，则不是二分
- 如果全部染色，则为二分图

```
for i : 1, n
  if i未染色
    dfs(i, 1)

dfs:
for u的邻居j
  if j未染色
       将j染成相反的颜色。如果染色失败，返回false
  else j已经染色，且与 u 的颜色相同，返回false
```

首先随意选取一个未染色的点进行染色，然后尝试将其相邻的点染成相反的颜色。

- 如果邻接点已经被染色 并且 现有的染色与它应该被染的颜色不同，那么就说明不是二分图。
- 如果全部顺利染色完毕，则说明是二分图。

```cpp
int n, m;
const int N = 100010, M = 200010;
int h[N], e[M], ne[M], idx; // 无向图
int color[N]; // 存储每个点的染色情况

void add(int a, int b){
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}

bool dfs(int u, int c){
    color[u] = c;
    for(int i = h[u] ; i != -1; i = ne[i]){ // 尝试将其相邻的点染成相反的颜色
        int j = e[i];
        if(!color[j]){
            if(!dfs(j, 3 - c)) return false;
        }
        else if(color[j] == c) return false;
    }
    return true;
}

int main(){
    cin >> n >> m;
    memset(h, -1, sizeof h);
    while(m--){
        int a, b;
        cin >> a >> b;
        add(a, b), add(b, a);
    }
    bool flag = true;
    for(int i = 1; i <= n; i++){
        if(!color[i]){ // 没有染色
            if(!dfs(i, 1)){
                flag = false;
                break;
            }
        }
    }
    if(flag) cout << "Yes";
    else cout << "No";
}
```

# 求二分图的最大匹配

## 匈牙利算法

$$
最坏：O(mn)，但实际运行时间一般很少
$$

二分图，其中左半部包含 n1 个点（编号 1∼n1），右半部包含 n2 个点（编号 1∼n2），二分图共包含 m 条边。求出二分图的最大匹配数。

所有匹配中包含边数最多的一组匹配被称为二分图的最大匹配，其边数即为最大匹配数。

匈牙利算法求最大匹配的思路：
- 遍历二分图的左半部的所有点，为他们寻找匹配。在遍历过程中，不断重置标记数组
  - 匹配：遍历当前点u的所有邻居j
    - 如果 j 没有被标记 
      - 标记j
      - 如果 j 已经被匹配
        - 重新为 与 j 的匹配的点 x 寻找匹配。（递归）
      - 如果 j 还没被匹配
        - 匹配成功
  - 如果仍然没有匹配，则匹配失败
- 遍历完成后，结果即为匹配的次数

```cpp
int n1, n2, m;
const int N = 510, M = 100010;
int h[N], e[M], ne[M], idx;
int match[N];
bool st[N];

void add(int a, int b){
    e[idx] = b; ne[idx] = h[a]; h[a] = idx++;
}

bool find(int u){
    for(int i = h[u]; i != -1; i = ne[i]){
        int j = e[i];
        if(!st[j]){ // 如果点 j 没有被遍历 (防止无限递归？)
            st[j] = true; // 点 j 被遍历
            if(match[j] == 0 || find(match[j])){ // 如果点j没有被匹配 或 点j可以有其他匹配选择
                match[j] = u;
                return true;
            }
        }
    }
    return false;
}

int main(){
    cin >>n1>>n2>>m;
    memset(h, -1, sizeof h);
    while(m--){
        int a, b;
        cin >>a>>b;
        add(a, b);
    }
    int res = 0;
    for(int i = 1; i <= n1; i++){ // 遍历左半部
        memset(st, false, sizeof st);
        if(find(i)) res++; // 匹配成功
    }
    cout << res;
}
```

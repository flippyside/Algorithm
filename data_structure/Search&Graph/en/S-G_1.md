index
- DFS
- BFS
- Tree and Graph Traversal
  - Directed Graph
  - Tree: Directed Acyclic Graph(DAG)
  - Application of Depth-first Search in Trees 
  - Application of Breadth-First search in Graphs
  - Topological Sorting


# DFS(Depth-first search)

it backtracks only after reaching the deepest level and ensures every path is explored.

Data Structure: Stack
Space Complexity: O(h). h: depth of the recursion

Tech: Backtracking, Pruning

## Permutations

```
Given an integer n, arrange the numbers from 1 to n in all possible ways in lexicographical order.
```

```cpp
const int N = 8;

int n;
int path[N]; // 存储数字序列
bool st[N]; // status, 表示数字 i 已经被用过了

void dfs(int u){
    if(u == n) { // 到达最底部（已经形成完整的序列）
        for(int i = 0; i < n; i++) cout << path[i] << endl;
        return;
    }
    for(int i = 1; i <= n; i++){
        if(!st[i]){
            path[u] = i;
            st[i] = true; // 标记：数字 i 已经被用过
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

## N-Queens

method 1: only 1 queen per row.

```cpp
#include <algorithm>
#include <memory.h>
using namespace std;

const int N = 20;

int n;
char g[N][N]; // 存储棋盘状态
bool co[N], dg[N], udg[N]; // co: 同一行、列 dg：同一对角线  udg：同一反对角线

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
            g[u][i] = '.'; // 恢复现场 
        }
    }
}  

int main(){
    cin >> n;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            g[i][j] = '.';
    dfs(0);
}
```

method 2:

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

# BFS(breadth-first search)

search layer by layer.

DS：queue
SC：O(2^h)
feature：the shortest path problem

1. initialize a queue: put the starting point into the queue.
2. while the queue is not empty:
    - take out the head of the queue
    - expapnd the head: find and mark all the adjacent, unvisited points, and push them into the queue.


```
Given an n × m 2D integer array representing a maze, where 0 represents a passable path and 1 represents an impassable wall. Initially, a person is located at the top-left corner (1,1). The person can move one position in any of the four directions: up, down, left, or right. Determine the minimum number of moves required to move from the top-left corner to the bottom-right corner (n,m).
```

```cpp
int n, m;
int g[N][N]; // 地图
int d[N][N]; // 每个点到起点的距离, 即移动到点(i, j)需要的步数
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
            if(x >= 0 && x < n && y >= 0 && y < m && g[x][y] == 0 && d[x][y] == -1){ // boarder judge
                d[x][y] = d[t.first][t.second] + 1; // 标记
                Prev[x][y] = t; // 为了能够打印出路线，记录(x, y) 的前一个点。这样可以形成一棵树
                q[++tt] = {x, y}; // 放入队列
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

# Tree and Graph Traversal

## Directed Graph

DS：

1. adjacency matrix
2. adjacency list：Each vertex has a linked list containing the vertices it can reach.
    - vertex: has a linked list storing all the vertices it can reach.
    - add edge: add a->b == add b to a's linked list
    - undirected graph: when adding edge, store both a->b and b->a

![Alt text](assets/S-G_1/image-1.png)
![Alt text](assets/S-G_1/image.png)


1. DFS: keep exploring until you hit the bottom, then backtrack, and before backtracking, remember to restore the state.

```cpp
int h[N], e[N], ne[N], idx; 
// h[i]: Head of the i-th linked list. corresponds to vertex i, storing the index of the vertices it can reach.
// e[idx]：store the destination vertex of an edge
// ne[idx]：next pointer, storing the index of the next edge
// idx：current index of the edge
bool st[N]; // store whether a vertex has been visited

void init(){
    memset(h, -1, sizeof(h)); // empty head node
}

// e: a->b
void add(int a,int b){
    e[idx] = b; // -e->b
    ne[idx] = h[a]; // -e->b->h[a]
    h[a] = idx;
    idx++;
}

void dfs(int u){
    st[u] = true; // u is visited
    for(int i = h[u]; i != -1; i = ne[i]){ // traverse the reachable vertices of u
        int j = e[i]; // j is the destination of the current edge
        if(!st[j]) dfs(j); // continue to traverse j
    }
}
```

## Tree: Directed Acyclic Graph(DAG)

$$
O(n+m)，n：number of vertices \qquad m：边数
$$

## Application of Depth-first Search in Trees 

### Tree Centroid

def: a point in the tree that, when removed, leaves the remaining subtrees with the smallest possible maximum size.

- When a vertex is removed, the tree is split into several subtrees. Calculate the size of each subtree and record the maximum value.
- iterate through all vertices and perform the above operation. the vertex for which the maximum value is minimized is the centroid. (when the max is the min, the subtrees are balanced)

```
Given a tree with n nodes (numbered from 1 to n) and n−1 undirected edges, find the centroid of the tree and output the maximum size of the remaining connected components after the centroid is removed.

Definition of centroid: The centroid is a node in the tree such that, when removed, the maximum size of the remaining connected components is minimized.

Input: The first line contains an integer n, representing the number of nodes in the tree. The next n−1 lines each contain two integers a and b, indicating that there is an edge between node a and node b.

Output: Output an integer m, representing the maximum size of the remaining connected components after the centroid is removed.

```

Thought process: It's a bit unclear...

1. Use DFS to calculate the size of each subtree in the tree.
2. Record the maximum size of the subtree downward.
3. The upward subtree size = total size - downward subtree size.

```cpp
int n;
const int N = 100010, M = 200020;
int h[N], e[M], ne[M], idx; // 图
bool st[N]; // 点是否已经被遍历
int ans = N;

void add(int a, int b){
    e[idx] = b;ne[idx] = h[a];h[a] = idx++;
}

// 返回以 u 为根的子树的大小
int dfs(int u){
    st[u] = true;
    int sum = 0; // 当前子树的大小（不包含u）
    int sz = 0; // 删除重心后，连通块大小的最大值
    for(int i = h[u]; i != -1; i = ne[i]){
        // 找剩余连通块中 点数的最大值（剩余子树的大小的最大值）
        int j = e[i];
        if(!st[j]) {
            int son = dfs(j);
            sz = max(sz, son);
            sum += son;
        }
    }
    sz = max(sz, n - sum - 1);
    ans = min(ans, sz);
    return sum + 1; // 记得把u加上
}

int main(){
    cin >> n;
    memset(h , -1, sizeof h);
    for(int i = 0; i < n; i++){
        int a, b;
        cin >> a>>b;
        add(a, b), add(b, a);
    }
    dfs(1);
    cout << ans;
}
```

## Applications of Breadth-First Search in Graphs


```cpp
// template
d[i] : the distance from the source to vertex i
init: queue <- 1
while queue is not empty{
    expand all neighbors x of the head 
        if x is unvisited (d[x] = -1)
            queue <- x
            d[x] = d[t] + 1
}
```

### single-source shortest path problem in a directed graph

```
Graph: n vertices, m edges, possibly with multiple edges and self-loops
Find the shortest distance from vertex 1 to vertex n.
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

# topological sorting

> AOV network(activity on vertices): A directed graph representing a project, where vertices are activities and a directed edge from a to b indicates that activity a must precede activity b.


> In a directed acyclic graph, arrange the vertices in a linear order such that for any directed edge u->v, u appears before v.

Detecting a directed cycle is equivalent to constructing the topological order of the AOV network.

Dependencies: If there is an edge i->j, then j depends on i (i is a prerequisite for j). Indirect dependency: If there is a path from i to j (i is reachable from j), then j indirectly depends on i.

The goal of topological sorting is to arrange all nodes such that no node depends on any node that appears after it.

![Alt text](assets/S-G_1/image-2.png)

In the AOV network, select a vertex with no direct predecessors and output it.
Remove this vertex from the graph, along with all its outgoing edges.
Nodes with in-degree 0 can serve as the starting points. A directed acyclic graph must have at least one node with in-degree 0.

Thought process: Continuously construct nodes with in-degree 0.

Initialize the queue: All nodes with in-degree 0 are enqueued.
Dequeue the head t: Enumerate all outgoing edges t->j of t and remove the edge t->j (just decrease the in-degree of j by 1).
If j's in-degree becomes 0, enqueue it.
When the number of enqueues reaches n - 1, the queue represents the final topological order; if not, it means some nodes still have direct predecessors, indicating the presence of a directed cycle, and the topological sequence does not exist.


```
d[i]：the in-degree of vertex i
queue <- all vertices with 0 in-degree
while queue not empty{
    enumerate all outgoing edges t->j of the head t
        remove t->j (d[j]--)
        if d[j] == 0
            queue <- j
}
```

```cpp
int h[N], e[M], ne[M], idx; // 有向图
int d[N], q[N]; // 入度、队列
int n, m;

void add(int a, int b){ // 加边
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}

bool topsort(){
    int hh = 0, tt = -1;
    for(int i = 1; i <= n; i++){
        if(!d[i]) q[++tt] = i;
    }
    while(hh <= tt){
        int t = q[hh++];
        for(int i = h[t]; i != -1; i = ne[i]){
            int j = e[i];
            d[j]--;
            if(d[j] == 0) q[++tt] = j;
        }
    }
    return tt == n - 1;
}

int main(){
    cin >> n >> m;
    memset(h, -1, sizeof(h));
    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        add(a,b); // 无向图
        d[b]++; // 入度增加
    }
    if(topsort()){
        for(int i = 0; i < n; i++) cout << q[i] << " ";
    }
    else cout << -1;
}
```



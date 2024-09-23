index

- 遍历
  - 反向建图+dfs


# 遍历

## 反向建图+dfs

problem: 给出 $N$ 个点，$M$ 条边的有向图，对于每个点 $v$，求 $A(v)$ 表示从点 $v$ 出发，能到达的编号最大的点。

```cpp
int g[N], e[N], ne[N], idx = 0;
int maxi[N]; // max[i]表示点 i 能到达的最大的点
int st[N];

void add(int u, int v){
    e[idx] = v;
    ne[idx] = g[u];
    g[u] = idx;
    idx++;
}

void dfs(int v){
    if(st[v]) return;
    st[v] = 1;
    maxi[v] = max(maxi[v], v);
    for(int i = g[v]; i != -1; i = ne[i]){
        int j = e[i];
        maxi[j] = max(maxi[j], maxi[v]);
        dfs(j);
    }
}

int main(){
    memset(g, -1, sizeof g);
    int m, n;
    cin>>m>>n;
    while(n--){
        int u, v;
        cin >> u >> v;
        // 反向建图
        add(v, u);
    }
    memset(maxi, -1, sizeof maxi);
    for(int i = m; i >= 1; i--) dfs(i);
    for(int i = 1; i <= m; i++) cout << maxi[i] << ' ';
}

```




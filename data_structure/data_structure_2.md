trie
并查集
堆
hash表

# trie

> 高效存储、查找字符串集合

```
维护一个字符串集合，支持两种操作：
I x 向集合中插入一个字符串 x；
Q x 询问一个字符串在集合中出现了多少次。
共有 N 个操作，字符串仅包含小写英文字母。

输入格式
第一行包含整数 N，表示操作数。

接下来 N 行，每行包含一个操作指令，指令为 I x 或 Q x 中的一种。

输出格式
对于每个询问指令 Q x，都要输出一个整数作为结果，表示 x 在集合中出现的次数。每个结果占一行。

数据范围
1≤N≤2∗104
输入样例：
5
I abc
Q abc
Q ab
I ab
Q ab
输出样例：
1
0
1

```

```cpp
const int N = 100005;

int son[N][26], cnt[N], idx = 0;
// son[p][u]：存储字母 u 在节点 p 下的子节点编号
// cnt[i]: 以 i 结尾的字符串在树中的数量
// p = 0时即为根节点

char str[N];

void insert(char str[]){
    int p = 0;
    for(int i = 0; str[i]; i++){
        int u = str[i] - 'a'; // 将字母 u 映射为数字
        if(!son[p][u]) son[p][u] = ++idx; // 如果son[p][u]不存在，则赋值idx（idx从1开始）
        p = son[p][u]; // 移动到子节点
    }
    cnt[p]++;
}

int query(char str[]){
    int p = 0;
    for(int i = 0; str[i]; i++){
        int u = str[i] - 'a';
        if(!son[p][u]) return 0;
        p = son[p][u];
    }
    return cnt[p];
}

int main(){
    int n;
    scanf("%d", &n);
    while(n--){
        char c[2];
        scanf("%s%s", c, str);
        if(c[0] == 'I') insert(str);
        else printf("%d\n", query(str));
    }
}
```

# 并查集

1. 将两个集合合并
2. 询问两个元素是否在一个集合当中

```cpp
// 暴力
belong[x] = a：x在集合a中
if(belong[x] == belong[y])：x、y是否在一个集合
```

每个集合用一棵树表示，树根的编号就是整个集合的编号，每个节点存储它的父节点，p[x]表示x的父节点

1. 判断树根：树根的p[x] == x。`if(p[x] == x)`
2. 求x的集合编号：一直往上走。`while(p[x] != x) x = p[x];`
3. 合并两个集合：x、y为两个集合的根节点，`p[x] = y`

优化：
2. 往上走过一遍之后，直接把走过的路上的所有点连到找到的根节点上，后续无需再走。

`M a b`，将编号为 a 和 b 的两个数所在的集合合并，如果两个数已经在同一个集合中，则忽略这个操作；
`Q a b`，询问编号为 a 和 b 的两个数是否在同一个集合中；

```cpp
int p[N];

int find(int x){
    if(p[x] != x) p[x] = find(p[x]);
    return p[x];
}

int main(){
    int n, m;
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++) p[i] = i;

    while(m--){
        char op[2];
        int a, b;
        scanf("%s%d%d", &op, &a, &b);
        if(op[0] == 'M') p[find(a)] = find(b);
        else{
            if(find(a) == find(b)) printf("Yes");
            else printf("No");
        }
    }
}
```

给定一个包含 n 个点（编号为 1∼n）的无向图，初始时图中没有边。

现在要进行 m 个操作，操作共有三种：

C a b，在点 a 和点 b 之间连一条边，a 和 b 可能相等；
Q1 a b，询问点 a 和点 b 是否在同一个连通块中，a 和 b 可能相等；
Q2 a，询问点 a 所在连通块中点的数量；
输入格式
第一行输入整数 n 和 m。

接下来 m 行，每行包含一个操作指令，指令为 C a b，Q1 a b 或 Q2 a 中的一种。

输出格式
对于每个询问指令 Q1 a b，如果 a 和 b 在同一个连通块中，则输出 Yes，否则输出 No。
对于每个询问指令 Q2 a，输出一个整数表示点 a 所在连通块中点的数量

每个结果占一行。

思路：用集合维护连通块。两个连通分支之间连边，即两个连通分支所对应的集合合并

```cpp
// 有问题
int p[N], size[N];
// size[i]表示第i棵树的节点个数

int find(int x){
    if(p[x] != x) p[x] = find(p[x]);
    return p[x];
}

int main(){
    int n, m;
    scanf("%d%d", &n, &m);

    // 初始化n棵树
    for(int i = 1; i <= n; i++){ p[i] = i; size[i] = 1; }

    while(m--){
        char op[2];
        int a, b;
        scanf("%s", &op);
        if(op[0] == 'C'){ // 连边
            scanf("%d%d", &a, &b);
            if(find(a) == find(b)) continue; // 已经在一个集合里
            size[find(b)] += size[find(a)]; // 合并
            p[find(a)] = find(b); // 合并
        }
        else if(op[1] == '1'){
            scanf("%d%d", &a, &b);
            if(find(a) == find(b)) printf("Yes");
            else printf("No");
        }
        else{
            scanf("%d", &a);
            printf("%d\n", size[find(a)]);
        }
    }
}
```

# 堆

- 数据结构：一维数组
- 左子节点：2x
- 右子节点：2x + 1
- down(x)：将x增加后，x需往下移动
- up(x)：将x减小后，x需往上移动（与父节点交换）

操作：

- 插入一个数 `heap[++size] = x; up(size);`
- 求集和当中的最小值 `heap[1]`
- 删除最小值：把队尾换到根节点，然后删去队尾，调整新根节点的位置 `heap[1] = heap[size]; size--; down(1);`
- 删除任意一个元素 `heap[k] = heap[size]; size--;` 想象成杀人要杀队列的最后一个
- 修改任意一个元素 `heap[k] = x; down(k); up(k);`

堆是一个完全二叉树：除了最后一层，所有节点的子节点都有2个。最后一层的节点从左到右排布

小根堆：越往上越小。父节点 <= 子节点

```cpp
int h[N], size; // 堆，堆的大小
void down(int u){
    int min = u; 
    if(h[u * 2] < h[min] && u * 2 <= size) min = u * 2; // 左子结点小于当前节点
    if(h[u * 2 + 1] < h[min] && u * 2 + 1 <= size) min = u * 2 + 1; // 右子结点小于当前节点
    if(u != min){ // 交换
        swap(h[min], h[u]);
        down(min); // 递归
    }
}

void up(int u){
    while(h[u / 2] > h[u] && u / 2){
        swap(h[u / 2], h[u]);
        u /= 2;
    }
}

int main(){
    int n, m;
    for(int i = 1; i <= m; i++) scanf("%d%d", &n, &m);
    size = n;
    for(int i = n / 2; i; i--) down(i); // 从最后一个非叶子节点开始向下调整，构建初始堆。时间复杂度为 O(n)。

    while(m--){
        printf("%d", h[1]);
        h[1] = h[size];
        size--;
        down(1);
    }
}
```

```
维护一个集合，初始时集合为空，支持如下几种操作：
I x，插入一个数 x
PM，输出当前集合中的最小值；
DM，删除当前集合中的最小值（数据保证此时的最小值唯一）；
D k，删除第 k 个插入的数；
C k x，修改第 k 个插入的数，将其变为 x
```

```cpp
/*
字母含义
p: 下标  h：堆
ph：下标->堆
*/
int h[N], size; // 堆，堆的大小
int ph[N]; // ph[i]: 第i个插入的点的下标
int hp[N]; // hp[i]: 下标为i的点是第几个插入的

void heap_swap(int a, int b){ // "重载"swap
    swap(ph[hp[a]], ph[hp[b]]);
    swap(hp[a], hp[b]);
    swap(h[a], h[b]);
}

void down(int u){
    int min = u; 
    if(h[u * 2] < h[min] && u * 2 <= size) min = u * 2; // 左子结点小于当前节点
    if(h[u * 2 + 1] < h[min] && u * 2 + 1 <= size) min = u * 2 + 1; // 右子结点小于当前节点
    if(u != min){ // 交换
        swap(h[min], h[u]);
        down(min); // 递归
    }
}

void up(int u){
    while(h[u / 2] > h[u] && u / 2){
        swap(h[u / 2], h[u]);
        u /= 2;
    }
}

int main(){
    int n, m = 0;
    scanf("%d", &n);

    while(n--){
        char op[10];
        int k, x;
        scanf("%s", op);
        if(!strcmp(op, "I")){
            scanf("%d", &x);
            size++;
            m++;
            ph[m] = size, hp[size] = m;
            h[size] = x;
            up(size);
        }
        else if(!strcmp(op, "PM")) printf("%d\n", h[1]);
        else if(!strcmp(op, "DM")){
            heap_swap(1, size);
            size--;
            down(1);
        }
        else if(!strcmp(op, "D")){
            scanf("%d", &k);
            k = ph[k];
            heap_swap(k, size);
            size--;
            down(k), up(k);
        }
        else{ // 修改第 k 个插入的数，将其变为 x
            scanf("%d%d", &k, &x);
            k = ph[k];
            h[k] = x;
            down(k), up(k);
        }
    }
}
```

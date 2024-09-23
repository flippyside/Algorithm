基本二叉树

index

- DEBUG
- 数据结构
- 遍历
  - DFS
    - 最大深度
  - BFS
    - 最大宽度
  - 前、中、后序列的关系
    - 根据前、中序序列构造后序序列
    - 根据中、后序序列构造前序序列
    - 根据前、后序列求中序序列的数量
- 搜索
- 最近公共祖先

# DEBUG

注意题目要求，输入的节点建立顺序可能不是之前已经出现过的结点！例如

```
1 2
2 3
3 4
```

这种情况下，不能直接用指针链表，而应用数组。

# 数据结构

```cpp
struct T{
    int l; int r;
}t[N];
```

# 遍历

## DFS 深度遍历

对于某种遍历，树中每个结点都要经过三次，pre是在第一次遇到时访问，mid是第二次，back是第三次
中序(preorder)遍历：按照左子树，根，右子树的顺序访问节点；
前序(inorder)遍历：按照根，左子树，右子树的顺序访问节点；
后序(postorder)遍历：按照左子树，右子树，根的顺序访问节点。

```cpp
void pre_traverse(int rt){
    if(rt == -1) return;
    cout << rt << endl;
    pre_traverse(t[rt].l);
    pre_traverse(t[rt].r);
}

void mid_traverse(int rt){
    if(rt == -1) return;
    mid_traverse(t[rt].l);
    cout << rt << endl;
    mid_traverse(t[rt].r);
}

void back_traverse(int rt){
    if(rt == -1) return;
    back_traverse(t[rt].l);
    back_traverse(t[rt].r);
    cout << rt << endl;
}
```

### 二叉树的最大深度

```cpp
int maxHeight(int rt){
    if(rt == -1) return 0;
    return max(maxHeight(t[rt].l), maxHeight(t[rt].r)) + 1;
}
```

### 结点到根节点的距离

```cpp
int disToRT(T*rt,int tar){
    if(rt == nullptr)return 0;
    if(tar == rt->e) return 0;
    return min(disToRT(rt->le,tar),disToRT(rt->ri,tar)) + 1; 
}
```

## BFS 广度遍历

时间复杂度 O(N) ： N 为二叉树的节点数量，即 BFS 需循环 N 次。
空间复杂度 O(N) : 最多有 N/2 个树节点同时在 queue 中，使用 O(N) 大小的额外空间。

```cpp
class Solution {
public:
    const int N = 1e6;
    vector<vector<int>> levelOrder(TreeNode* root) {
        queue<TreeNode*> q;
        vector<vector<int>> res;
        if(root != nullptr) q.push(root);
        while(!q.empty()){
            vector<int> vec;
            int len = q.size();
            for(int i = 0; i < len; i++){
                auto t = q.front();
                q.pop();
                vec.push_back(t->val);
                if(t->left!=nullptr) vec.push_back(t->left->val);
                if(t->right != nullptr) vec.push_back(t->right->val);
            }
            res.push_back(vec);
        }
        return res;
    }
};
```

### 二叉树的最大宽度

层级遍历：
数据结构：队列

- 根节点入队
- 不断取出队首节点值，出队，将它的左右孩子入队，循环sz - 1次
- 重复，直至队列为空

```cpp
int maxBreath(T* rt){
    int ans = 0;
    T* q[N];
    int hh = 0, tt = -1;
    if(rt != nullptr) q[++tt] = rt;
    while(hh <= tt){
        int sz = tt - hh + 1;
        ans = max(sz, ans);
        for(int i = 0; i < sz; i++){
            T* cur = q[hh++];
            if(cur->le != nullptr) q[++tt] = cur->le; 
            if(cur->ri != nullptr) q[++tt] = cur->ri;
        }
    }
    return ans;
}
```

## 前、中、后序列的关系

### 根据前、中序序列构造后序序列

法一：造树，然后后序遍历

- 中序序列的总框架为：左子树-根-右子树，而每个子树又由 左子树-根-右子树 组成
- 前序序列的第一个元素是root，记为c，c将mid序列切割为c的左子树和右子树。继续递归左子树、右子树
- 结束条件：树的长度为0

```cpp
struct T{
    char c;
    T*l;T*r;
    T(char e) : c(e),l(nullptr),r(nullptr){}
};
/*
前序遍历：根-左子树-右子树
中序遍历：左子树-根-右子树
*/
T* construtTree(char* pre, char* mid, int n){
    if(n == 0){return nullptr;}
    int k = 0;
    while(pre[0] != mid[k]) k++;
    T* root = new T(pre[0]);
    root->l = construtTree(pre + 1, mid, k); // 左子树
    // pre + k + 1：右子树在前序遍历中的起始位置. 前序遍历中，根节点后面的 k 个元素属于左子树
    root->r = construtTree(pre + k + 1, mid + k + 1, n - k - 1); // 右子树
    return root;
}

void postTraverse(T* rt){
    if(rt==nullptr)return;
    postTraverse(rt->l);
    postTraverse(rt->r);
    cout<<rt->c;
}

int main(){
    char s1[N], s2[N]; 
    cin >> s2 >> s1;
    n = strlen(s1);
    T* rt = construtTree(s1, s2, n);
    postTraverse(rt);
}
```

法二：不造树

最终每个结点都会成为根。不断递归切割前序、中序字符串，回溯时将根输出即为后序序列

```cpp
void f(string pre, string mid){
    if(pre.empty()) return;
  
    int k = mid.find(pre[0]);
    string mid_l = mid.substr(0, k);
    string mid_r = mid.substr(k + 1);
    string pre_l = pre.substr(1, k);
    string pre_r = pre.substr(k + 1);
  
    f(pre_l, mid_l);
    f(pre_r, mid_r);
  
    cout << pre[0];
}
```

### 根据中、后序序列构造前序序列

与前者基本完全一致
后序：左右根，最后一个是树的root
root将中序序列分为左子树和右子树

```cpp
T* build(char* in, char* post, int len){
    if(len == 0) return nullptr;
    int k = 0;
    while(post[len - 1] != in[k]) k++;
    T* root = new T(post[len - 1]);
    root->le = build(in, post, k);
    root->ri = build(in + k + 1, post + k, len - k - 1);
    return root;
}
```

### 根据前、后序列求中序序列的数量

# 搜索

```cpp
T* search(T*rt, int tar){
    if(rt == nullptr||rt->e == tar) return rt;
    T* left = search(rt->ri, tar);
    if(left != nullptr) return left; // 如果在左子树中找到了目标，则返回结果
    return search(rt->le, tar); // 否则递归搜索右子树
}
```

# 最近公共祖先（Lowest Common Ancestor）

性质

- 祖先可以是结点自己。LCA(u) = u
- u 是 v 的祖先，当且仅当 LCA(u,v) = u
- 如果 u 不为 v 的祖先并且 v 不为 u 的祖先，那么 u,v 分别处于 LCA(u,v) 的两棵不同子树中
- 两点集并的最近公共祖先为两点集分别的最近公共祖先的最近公共祖先
- 两点的最近公共祖先必定处在树上两点间的最短路上：d(u,v)=h(u)+h(v)-2h(LCA(u,v))，d 是树上两点间的距离，h 代表某点到树根的距离
- 前序遍历中，LCA(S) 出现在所有 S 中元素之前，后序遍历中 LCA(S) 则出现在所有 S 中元素之后

## 朴素算法

让更深的节点到达与另一节点一样的高度后，一起向上跳，直至相遇。

- 计算两节点分别到root的距离
- 让更深的节点向上跳到和另一节点一样的高度
- 两节点一起向上跳，直至相遇

复杂度：O(n)

```cpp
T* findParent(T* rt, int tar){
    if(rt == nullptr) return rt;
    if(rt->e == tar) return rt;
    if((rt->le != nullptr && rt->le->e == tar) || 
    (rt->ri != nullptr && rt->ri->e == tar)) return rt;
    T* tmp = findParent(rt->le, tar);
    if(tmp != nullptr) return tmp;
    return findParent(rt->ri, tar);
}

T* lca(T* rt, int a, int b){
    int ha = disToRT(rt, a), hb = disToRT(rt, b);
    T* aa = search(rt, a), *bb = search(rt, b);
    if(aa == nullptr || bb == nullptr) return nullptr;
    if(ha > hb){
        int tmp = ha - hb;
        while(tmp){ // 向上跳
            aa = findParent(rt, aa->e);
            tmp--;
        }
    }else if(ha < hb){
        int tmp = hb - ha;
        while(tmp){ // 向上跳
            bb = findParent(rt, bb->e);
            tmp--;
        }
    }
    while(aa != bb){
        aa = findParent(rt, aa->e);
        bb = findParent(rt, bb->e);
    }
    return aa;
}
```



如果建树过程中记录了父节点，更为方便

```cpp
struct T{
    int father;
    int le = -1, ri = -1;
}t[N];

int dis_to_root(int rt, int idx){ // 标号为idx的结点距离rt的距离
    int dis = 0;
    while(idx != rt && idx != -1){
        idx = t[idx].father;
        dis++;
    }
    if(idx == -1) return -1;
    return dis;
}

int lca(int rt, int a, int b){
    int a_dis = dis_to_root(rt, a), b_dis = dis_to_root(rt, b);
    // cout << a_dis << ' ' << b_dis << endl;
    if(a_dis == -1 || b_dis == -1) return -1;
    if(a_dis > b_dis){
        while(a_dis != b_dis && a != -1){
            a = t[a].father;
            a_dis--;
        }
    }
    else if(b_dis > a_dis){
        while(a_dis != b_dis && b != -1){
            b = t[b].father;
            b_dis--;
        }
    }
    while(a != b && a != -1 && b != -1){
        a = t[a].father;
        b = t[b].father;
    }
    if(a == -1 || b == -1) return -1;
    return a;
}
```

## 递归

若树有特殊性质：BST

```cpp
T* lca(T* rt, T* p, T* q){

// TODO
}
```


若无特殊性质：

```cpp
T* lca(T* rt, T* p, T* q){

// TODO
}
```



## 倍增

数据结构：邻接表

 `parent[][]`数组：

- `parent[u][]`：u的所有2次幂祖先结点
- `parent[u][0]`：u的父节点(2^0)
- `parent[u][1]`：u的爷爷节点(2^1)
- `parent[u][2]`：u的爷爷的爷爷节点(2^2)

index

- binary searching tree
  - 性质、数据结构
  - 操作：添加、遍历、查找、删除、最值、排名
  - application
- self balance tree
  - AVL
  - red and black
  - splay

# binary searching tree(BST)

![Alt text](assets/binary-tree/image.png)

> a BST is a binary tree where every node in the left subtree is less than the root, and every node in the right tree is larger than the root. The properties of BST are recrusive: if we consider any node as a root, the properties remain true.


性质：

- 左子树上所有点的值小于其根节点
- 右子树上所有点的值大于其根节点
- 空树是bst。bst的左右子树也是bst
- 操作的时间复杂度：最优O(logn) 最差O(n)
- BST的中序遍历输出的序列是升序序列

### 基础操作

数据结构：指针

```cpp
struct T{
    int e;
    T* l;
    T* r;
    int sz; // 当前节点为根的子树大小
    int cnt; // 当前节点的重复数量。1表示只出现1次。
    T(int val) : e(val), sz(1), cnt(1), l(nullptr), r(nullptr) { }
};
```

```cpp
void traverse(T* root){ // 中序遍历
    if(root==nullptr) return;
    traverse(root->l);
    cout << root->e;
    traverse(root->r);
}
```

返回最值: 
- 最大值位于最右边，最小值位于最左边

```cpp
int findMin(T* root){
    if(root == nullptr) return -1;
    while(root->l != nullptr) root = root->l;
    return root->e;
}
int findMax(T*root){
    if(root == nullptr) return -1;
    while(root->r != nullptr) root = root->r;
    return root->e;
}

// 返回最大值节点
T* findMaxNode(T*root){
    if(root == nullptr) return nullptr;
    while(root->r != nullptr) root=root->r;
    return root;
}
```

搜索：根据当前值与目标值的大小关系，决定往左or右走

```cpp
// 给定数值e，搜索，返回结点
T* search(T* r, int e){
    if(r == nullptr || r->e == e) return r;
    if(r->e > e) return search(r->l, e);
    else return search(r->r, e); // r->e < e
}
```

用迭代实现的search

```cpp
T* IteractiveSearch(T* rt, int e){
    while(rt != nullptr){
        if(e < rt->e ) rt = rt->l;
        else if(e > rt->e) rt = rt->r;
        else return rt;
    }
    return nullptr;
}
```

插入一个节点：根据性质，小于当前结点的值往左子树插，大于往右子树插
T: O(h)  S: O(1)

```cpp
T* insert(T* root, int e){
    if(root == nullptr) return new T(e);
    root->sz++;
    if(root->e > e) root->l = insert(root->l, e);
    else if(root->e < e) root->r = insert(root->r, e);
    else root->cnt++;
    return root;
}
```

删除一个结点：
- 首先递归找这个节点
- 找到后：
  - 如果cnt>1，说明有重复，cnt-1即可
  - 如果只有一个孩子，就用这个孩子代替它
  - 如果有两个孩子，就用他的中序遍历后继(例如，左子树的最右节点)代替它

```cpp
// root = remove(root, 1)
T* remove(T* root, int e){
    if(root == nullptr) return nullptr;
    else if(e < root->e) root->l = remove(root->l, e);
    else if(e > root->e) root->r = remove(root->r, e);
    else{ // e == root->e，删除root
        if(root->cnt > 1) root->cnt--;
        else{
            // 只有一个孩子，就用这个孩子代替它
            if(root->l == nullptr){ 
                T* tmp = root->r;
                delete root;
                return tmp;
            } else if(root->r == nullptr){ 
                T* tmp = root->l;
                delete root;
                return tmp;
            } else{ 
                // 有两个孩子，就用its inorder successor（左子树的最右节点(最大节点)）代替它
                T* succ = findMaxNode(root->l);
                root->e = succ->e; root->cnt = succ->cnt; // copy
                // 删去successor
                succ->cnt = 1; // 便于删去
                root->l = remove(root->l, succ->e);
            }
        }
    }
    return root;
}
```

### 求元素的排名 & 查找排名为 k 的元素

排名定义为将数组元素升序排序后第一个相同元素之前的数的个数加一。
查找一个元素的排名，首先从根节点跳到这个元素，若向右跳，答案加上左儿子节点个数加当前节点重复的数个数，最后答案加上终点的左儿子子树大小加一。
时间复杂度 O(h)。

```cpp
int queryRank(T*root, int e){
    if(root == nullptr) return 0;
    if(e > root->e) return queryRank(root->r, e) + root->cnt + (root->l ? root->l->sz : 0);
    else if(e < root->e) return queryRank(root->l, e);
    else{
        return (root->l ? root->l->sz : 0) + 1;
    }
}
```

查找排名为 k 的元素
在一棵子树中，根节点的排名取决于其左子树的大小。
若其左子树的大小大于等于 k，则该元素在左子树中；
若其左子树的大小在区间 [k-cnt,k-1]（count 为当前结点的值的出现次数）中，则该元素为根节点；
若其左子树的大小小于 k-cnt，则该元素在右子树中。
时间复杂度 O(h)。

```cpp
int queryKth(T* root, int k){
    if(root == nullptr) return INF * -1; // 不存在
    if(root->l){
        if(root->l->sz >= k) return queryKth(root->l, k); // 则该元素在左子树中
        else if(root->l->sz + root->cnt >= k) return root->e; // 为根节点
    }
    else{ // 左子树为空 
        if(k == 1) return root->e; // special judge?
    }
    // root->l->sz < k - root->cnt 该元素在右子树中
    return queryKth(root->r, k - (root->l ? root->l->sz : 0) - root->cnt);
}

```

### 检查树是不是BST

法一：中序遍历，看是不是升序排列

```cpp
bool isBST(T* rt, T* pre = nullptr){
    if(rt != nullptr) return true;

    if(!isBST(rt->l, pre)) return false;
    if(pre != nullptr && pre->e >= rt->e) return false;
    pre = rt;
    return isBST(rt->r, pre);
}
```

### 求前驱与后继


返回e的前驱元素的值(inorder predecessor)
solution1: inorder traversal

返回e的后继结点(inorder successor)
- if current node is e, ans it has right child: successor is the min in the right subtree
- if current node is larger than e, then it might be the answer, 
   we just let it be the answer and proceed to left
- if smaller, proceed to right

```cpp
void queryPrex(T* rt, int e, T*& pre){
    if(rt == nullptr) return;
    queryPrex(rt->l, e, pre);
    if(rt->e < e) pre = rt;
    queryPrex(rt->r, e, pre);
}

T* queryPost(T* rt, int e){
    if(rt == nullptr) return nullptr;
    if(rt->e == e && rt->l != nullptr) return findMinNode(rt->r);
    
    T* succ = nullptr;
    T* cur = rt;
    while(cur != nullptr){
        if(e < cur->e) {
            succ = cur;
            cur = cur->l;
        }
        else if(e > cur->e) cur = cur->r;
        else break;
    }
    return succ;
}
```

法二：inorder traverse

```cpp
void queryPost_2(T* rt, int e, T*& suc){
    if(rt == nullptr) return;

    queryPost_2(rt->l, e, suc);
    if(rt->e > e && (!suc || (suc && suc->e > rt->e))) suc = rt;
    queryPost_2(rt->r, e, suc);
}
```






### 数组实现

P5076待调整!!!!!卡关

```cpp

// BST
// 注意：特判 特判 特判！t[ & ] 的 & 是不是等于-1！

int idx = -1;
struct T{
    int x;
    int l = -1;
    int r = -1;
    int cnt; // 出现次数
    int sz = 0; // 子树大小(包括自己)
} t[N];


int add(int rt, int e){
    if(rt == -1) { 
        idx++; 
        t[idx].l = t[idx].r = -1; 
        t[idx].x = e; 
        t[idx].sz = 1; // 初始化大小为1
        t[idx].cnt = 1; // 初始化计数为1
        return idx; 
    }
    t[rt].sz++; // //如果查到这个节点，说明这个节点的子树里面肯定有v
    if(e < t[rt].x) {
        t[rt].l = add(t[rt].l, e); 
    }
    else if(e > t[rt].x) {
        t[rt].r = add(t[rt].r, e); 
    }else{
        t[rt].cnt++; // 重复出现
    }
    return rt; // !!!!
}

int findMaxNode(int rt){ // 返回最大结点的下标
    if(rt == -1) return -1;
    while(t[rt].r != -1) rt = t[rt].r;
    return rt;
}

int findMinNode(int rt){ // 返回最小结点的下标
    if(rt == -1) return -1;
    while(t[rt].l != -1) rt = t[rt].l;
    return rt;
}

int fd(int rt, int e){ // 返回值为e的结点的下标
    if(rt == -1) return -1;
    if(e < t[rt].x) return fd(t[rt].l, e); // 递归调用需要返回值!!!!!
    else if(e > t[rt].x) return fd(t[rt].r, e);
    else return rt;
}

// 找x的父节点，返回下标
int findFather(int rt = 0, int x = 0, int pre = -1){
    if(rt == -1) return -1;
    if(x < t[rt].x) return findFather(t[rt].l, x, rt);
    else if(x > t[rt].x) return findFather(t[rt].r, x, rt);
    else return pre;
}

/*
如果x为左节点：rk = 左子树大小
右：rk = 父节点的左子树大小 + 左子树大小
*/
int ranking(int rt, int x){ // 集合中小于 x 的数的个数 +1。
    if(rt == -1) return 0;
    if(x < t[rt].x) return ranking(t[rt].l, x);
    else if(x > t[rt].x) {
        if(t[rt].l == -1) return ranking(t[rt].r, x) + 1;
        else return ranking(t[rt].r, x) + t[t[rt].l].sz + 1;
    }
    else {
        if(t[rt].l == -1) return 1;
        else return t[t[rt].l].sz + 1;
    }
}

int ans = 0;
void queryRkX(int rt, int& k){ // 查询 排名为 k 的结点的值
    if(rt == -1) return;
    queryRkX(t[rt].l, k);
    k--;
    if(k == 0) ans = t[rt].x; 
    queryRkX(t[rt].r, k);
}

/*
如果节点有左子树：
前驱节点就是该左子树中最大值的节点（即左子树中最右的节点）。
如果节点没有左子树：
需要从该节点开始向上追溯其父节点，直到找到第一个比该节点小的祖先节点。这个祖先节点就是前驱节点。
*/

int queryPrex(int rt, int x, int ans){// 求x的前驱：小于x，且最大的数
    int idx = fd(rt, x);
    if(idx == -1) return -2147483647;
    if(t[idx].l != -1){
        return t[findMaxNode(t[idx].l)].x;
    }else{
        int father = findFather(rt, x, -1);
        while(father != -1){
            if(t[father].x < x) return t[father].x;
            father = findFather(rt, t[father].x, -1);
        }
        return -2147483647;
    }
}

int queryPost(int rt, int x){ // 求x的后继：大于x，且最小的数
    // 有右结点：右结点子树的最小值
    // 无：第一个大于x的父节点
    int idx = fd(rt, x);
    if(idx == -1) return 2147483647;
    if(t[idx].r == -1) {
        int father = findFather(rt, x, -1);
        while(father != -1){
            if(t[father].x > x) return t[father].x;
            father = findFather(rt, t[father].x, -1);
        }
        return 2147483647;
    }else{
        return t[findMinNode(t[idx].r)].x;
    }
}

int main(){
    int q, op, x;
    cin >> q;
    int rt = -1;
    while(q--){
        cin >> op >> x;
        switch(op){
            case 1:{
                cout << ranking(rt, x) << endl;
                break;
            }
            case 2:{
                ans = 0;
                queryRkX(rt, x);
                cout << ans << endl;
                break;
            }
            case 3:{ // 求x的前驱：小于x，且最大的数
                cout << queryPrex(rt, x, -2147483647) << endl;
                break;
            }
            case 4:{ // 求x的后继：大于x，且最小的数
                cout << queryPost(rt, x) << endl;
                break;
            }
            case 5:{
                rt = add(rt, x);
                break;
            }
        }
    }
}
```

## application

- self-balancing BST
- maintain a sorted stream of data
- double ended priority queues(双端优先队列)



# self balance tree

## AVL

> the difference between heights of left and right subtrees for any node cannot be more than 1




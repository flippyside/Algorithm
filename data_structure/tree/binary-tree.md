index
- binary searching tree
- balance tree


# binary searching tree(BST)

性质：
- 左子树上所有点的值小于其根节点
- 右子树上所有点的值大于其根节点
- 空树是bst。bst的左右子树也是bst
- 操作的时间复杂度：最优O(logn) 最差O(n)


```cpp
// 二叉搜索树
struct T{
    int e;
    T* l;
    T* r;
    int sz; // 当前节点为根的子树大小
    int cnt; // 当前节点的重复数量
    T(int val) : e(val), sz(1), cnt(1), l(nullptr), r(nullptr) { }
};

void traverse(T* root){ // 遍历
    if(root==nullptr) return;
    traverse(root->l);
    cout << root->e;
    traverse(root->r);
}

// 返回最大、最小值: 位于最右边、最左边
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

// 返回最大值的节点
T* findMaxNode(T*root){
    if(root == nullptr) return nullptr;
    while(root->r != nullptr) root=root->r;
    return root;
}

// 搜索
T* find(T* r, int e){
    if(r == nullptr) return nullptr;
    if(r->e > e) find(r->l, e);
    else if(r->e < e) find(r->r, e);
    else return r;
}

// 插入一个节点
T* add(T* root, int e){
    T* newT = new T(e);
    if(root == nullptr) return newT;
    if(root->e > e){
        root->l = add(root->l, e);
    }
    else if(root->e < e){
        root->r = add(root->r, e);
    }
    else{ // 重复的  
        root->cnt++;
    }
    // 更新节点的子树大小??
    if(root->l != nullptr) root->sz = root->cnt + root->l->sz;
    if(root->r != nullptr) root->sz = root->cnt + root->r->sz;
    return root;
}

// root = remove(root, 1)
T* remove(T* root, int e){
    if(root == nullptr){return nullptr;}
    else if(e < root->e){
        root = remove(root->l, e);
    }else if(e > root->e){
        root = remove(root->r, e);
    }else{
        if(root->cnt > 1) root->cnt--;
        else{
            if(root->l == nullptr){
                T* tmp = root->r;
                delete root;
                return tmp;
            } else if(root->r == nullptr){
                T* tmp = root->l;
                delete root;
                return tmp;
            } else{ // 用左子树的最右节点(最大值)代替要删去的节点
                T* maxNode = findMaxNode(root->l);
                root->e=maxNode->e; root->cnt=maxNode->cnt;
                // 删去原先的最右节点
                maxNode->cnt = 1;
                root->l = remove(root->r, maxNode->e);
            }
        }
    }
    return root;
}

// 名次：将数组元素升序排序后第一个相同元素之前的数的个数加一。
int queryRank(T*root, int e){
    int rk = 0;
// TODO 左子树
    T* t = find(root, e);
    return t->sz;

}

// 查找排名为 k 的元素
int queryKth(T* root, int k){
// TODO
    if(root->sz == k) return root;
    else{
        queryKth(root->l, k);
    }
}

```


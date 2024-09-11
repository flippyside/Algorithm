
- 数据结构
- 遍历
  - 最大深度
  - 根据前、中序序列构造后序序列(两种方法)

# 数据结构

```cpp
struct T{
    int l; int r;
}t[N];
```

# 遍历

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

## 最大深度

```cpp
int maxHeight(int rt){
    if(rt == -1) return 0;
    return max(maxHeight(t[rt].l), maxHeight(t[rt].r)) + 1;
}
```

## 根据前、中序序列构造后序序列

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





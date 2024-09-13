#include <iostream>
#include <string>
#include <cstring>
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;
const int N = 1e6 + 10;
const int INF = 2147483647;

// 二叉搜索树
struct T{
    int e;
    T* l;
    T* r;
    int sz; // 当前节点为根的子树大小
    int cnt; // 当前节点的重复数量
    T(int val) : e(val), sz(1), cnt(1), l(nullptr), r(nullptr) { }
};

void inorder(T* root){ // 中序遍历
    if(root==nullptr) return;
    inorder(root->l);
    cout << root->e << ' ';
    inorder(root->r);
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

// 返回最大值节点
T* findMaxNode(T*root){
    if(root == nullptr) return nullptr;
    while(root->r != nullptr) root=root->r;
    return root;
}

T* findMinNode(T* root){
    if(root == nullptr) return nullptr;
    while(root->l != nullptr) root=root->l;
    return root;
}

// 给定数值，搜索 
// T: O(h) h is the height of bst   S: O(h), recursion stack
T* search(T* r, int e){
    if(r == nullptr || r->e == e) return r;
    if(r->e > e) return search(r->l, e);
    else return search(r->r, e); // r->e < e
}

// 用迭代实现的search
T* IteractiveSearch(T* rt, int e){
    while(rt != nullptr){
        if(e < rt->e ) rt = rt->l;
        else if(e > rt->e) rt = rt->r;
        else return rt;
    }
    return nullptr;
}

// 插入一个节点：根据性质，小于当前结点的值往左插，大于往右插
T* insert(T* root, int e){
    if(root == nullptr) return new T(e);
    root->sz++;
    if(root->e > e) root->l = insert(root->l, e);
    else if(root->e < e) root->r = insert(root->r, e);
    else root->cnt++;
    return root;
}

int queryRank(T*root, int e){
    if(root == nullptr) return 0;
    if(e > root->e) return queryRank(root->r, e) + root->cnt + (root->l ? root->l->sz : 0);
    else if(e < root->e) return queryRank(root->l, e);
    else{
        return (root->l ? root->l->sz : 0) + 1;
    }
}

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

// 法二：inorder traverse
void queryPost_2(T* rt, int e, T*& suc){
    if(rt == nullptr) return;

    queryPost_2(rt->l, e, suc);
    if(rt->e > e){
        if(!suc || (suc && suc->e > rt->e)) suc = rt;
    }
    queryPost_2(rt->r, e, suc);
}

int main(){
    int q, op, x;
    cin >> q;
    T* rt = nullptr;
    while(q--){
        cin >> op >> x;
        switch(op){
            case 1:{
                cout << queryRank(rt, x) << endl;
                break;
            }
            case 2:{
                cout << queryKth(rt, x) << endl;
                break;
            }
            case 3:{ // 求x的前驱：小于x，且最大的数
                T* pre = nullptr;
                queryPrex(rt, x, pre);
                if(pre == nullptr) cout << INF * -1 << endl;
                else cout << pre->e << endl;
                break;
            }
            case 4:{ // 求x的后继：大于x，且最小的数
                T* suc = nullptr;
                // if(queryPost(rt, x) == nullptr) cout << INF << endl;
                // else cout << queryPost(rt, x)->e << endl;
                queryPost_2(rt, x, suc);
                if(suc == nullptr) cout << INF;
                else cout << suc->e << endl;
                break;
            }
            case 5:{
                rt = insert(rt, x);
                break;
            }
        }
    }
}
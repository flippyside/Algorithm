- binary searching tree
- 左子树上所有点的值小于其根节点
- 右子树上所有点的值大于其根节点
- 空树是bst。bst的左右子树也是bst
- 操作的时间复杂度：最优O(logn) 最差O(n)

// #include<iostream>
// #include<cstring>
// using namespace std;
// typedef unsigned long long ull;
// const int N = 32780;
// int a[N], idx = 1;
// ull ans=0;
// /*
// 平衡树
// 4 3 10 9
// 4 10
// 10
// */
// struct T{
//     int e;
//     T*l;
//     T*r;
//     int sz;
//     int cnt;
// };

// void tra(T* root){
//     if(root==nullptr){
//         return;
//     }
//         tra(root->l);
//         cout<<root->e;
//         tra(root->r);
// }

// int findMin(T*root){
//     if(root == nullptr) return -1;
//     while(root->l != nullptr){
//         root=root->l;
//     }
//     return root->e;
// }
// int findMax(T*root){
//     if(root == nullptr) return -1;
//     while(root->r != nullptr) root=root->r;
//     return root->e;
// }
// T* findMaxNode(T*root){
//     if(root == nullptr) return nullptr;
//     while(root->r != nullptr) root=root->r;
//     return root;
// }

// T* find(T* r, int e){
//     if(r==nullptr) return nullptr;
//     if(r->e > e) find(r->l, e);
//     else if(r->e < e) find(r->r, e);
//     else return r;
// }

// T* add(T* root, int e){
//     T*cur = root;
//     T* newT = new T;
//     newT->e = e; newT->l = nullptr; newT->r = nullptr;
//     if(root == nullptr) return newT;
//     while(cur!=nullptr){
//         if(cur->e > e){
//             add(cur->l, e);
//         }
//         else if(cur->e < e){
//             add(cur->r, e);
//         }else{
//             cur->cnt++;
//         }
//     }
//     return root;
// }
// // root = remove(root, 1)

// T* remove(T* root, int e){
//     if(root == nullptr){return nullptr;}
//     else if(e < root->e){
//         root = remove(root->l, e);
//     }else if(e > root->e){
//         root = remove(root->r, e);
//     }else{
//         if(root->l == nullptr && root->r == nullptr){
//             root = nullptr;
//         }else if(root->l == nullptr){
//             T* tmp = root->r;
//             delete root;
//             return tmp;
//         }else if(root->r == nullptr){
//             T* tmp = root->l;
//             delete root;
//             return tmp;
//         }else{ // 用左子树的最右节点(最大值)代替
//             T* maxNode = findMaxNode(root->l);
//             root->e=maxNode->e; root->cnt=maxNode->cnt;
//             maxNode->cnt=1;
//             delete maxNode;
        
//         }
//     }
//     return root;
// }
// // 排名定义为将数组元素升序排序后第一个相同元素之前的数的个数加一。

// int findRank(T*root, int e){
//     int rk = 0;
//     while(root != nullptr){
//         if(e < root->e){
//             root = root->l;
//         }else if(e>root->e){
//             root = root->r;
//         }else{
//             while(root!=nullptr){
//                 rk+=root->cnt;
//                 root=root->r;
//             }
//         }
//     }
//     return rk;
// }


// // min(a[j] - a[i]), j<i
// int main(){
//     int n;
//     cin>>n;
//     for(int i=0;i<n;i++) cin>>a[i];
//     ans+=a[0];
//     for(int i=1;i<n;i++){
//         int tmp = 0;
//         for(int j=i;j>=0;j--){
//             tmp = min(abs(tmp-a[j]),tmp);
//         }
//         ans+=tmp;
//     }
//     t[0].r = 1;
    
// }

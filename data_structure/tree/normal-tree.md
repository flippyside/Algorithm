
P4913
```cpp
#include <iostream>
#include <string>
#include <cstring>
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;
const int N = 1e6 + 10;
bool st[N];
int n; // n个结点
int ans = 0;
int cnt = 1;

struct T{
    int id;
    int h = 0; // 所在高度
    T*l; T*r;
    T(int id) : id(id), l(nullptr), r(nullptr){}
    T(int id, T*l, T*r) : id(id), l(l), r(r){}
};

T* find(T* root, int id){
    if(root == nullptr) return nullptr;
    if(root->id == id) return root;

    T* tmp = find(root->l, id);
    if(tmp != nullptr) return tmp; 
    // 当左子树没有找到时去查找右子树
    return find(root->r, id);
}
// bool checkSt(){
//     for(int i = 1; i <= n; i++)
//         if(!st[i]) return false;
//     return true;
// }

// 求树的最大深度 DFS
void height(T*root){
    if(root == nullptr){ // hit the bottom
        cnt--;
        return;
    }
    root->h = cnt;
    cout << root->id <<' ' << root->h << endl;
    cnt++;
    height(root->l);
    cnt++;
    height(root->r);
}

void depth(T* root){
    if(root == nullptr) return;
    if(root->r == nullptr && root->l == nullptr){
        ans = max(ans, root->h);
        return;
    }
    depth(root->r);
    depth(root->l);
}

int main(){
    cin >> n;
    T* root = new T(0);
    for(int i = 1; i <= n; i++){
        int l,r;cin>>l>>r;
        T* left = new T(l);
        T* right = new T(r);
        if(l == 0) left = nullptr;
        if(r == 0) right = nullptr;
        if(i == 1){
            root->id = 1; root->l = left; root->r = right;
        }else{
            T* tmp = find(root, i);
            tmp->l = left; tmp->r = right;
        }
    }
    root->h = 1;
    height(root);
    depth(root);
    cout<<ans;
}

```
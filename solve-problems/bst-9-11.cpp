#include <iostream>
#include <string>
#include <cstring>
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;
const int N = 1e6 + 10;

// BST

int idx = -1;
struct T{
    int x;
    int l = -1;
    int r = -1;
    int sz_l = 0; // 左子树大小
    int sz_r = 0;
} t[N];


int add(int rt, int e){
    if(rt == -1) { idx++; t[idx].l = t[idx].r = -1; t[idx].x = e; return idx;}
    if(e < t[rt].x) {t[rt].l = add(t[rt].l, e); t[rt].sz_l++; }
    else {t[rt].r = add(t[rt].r, e); t[rt].sz_r++; }
    return rt; // !!!!
}

void traverse(int rt){ // postorder
    if(rt == -1) return;
    traverse(t[rt].l);
    traverse(t[rt].r);
    cout << rt << ' ' << t[rt].x << ' ' << t[rt].sz_l << endl;
}
int findMaxNode(int rt){ // 返回最大结点的下标
    if(t[rt].r == -1) return rt;
    return findMaxNode(t[rt].r);
}

int findMinNode(int rt){ // 返回最小结点的下标
    if(t[rt].l == -1) return rt;
    return findMinNode(t[rt].l);
}

int fd(int rt, int e){ // 返回值为e的结点的下标
    if(rt == -1) return -1;
    if(e < t[rt].x) return fd(t[rt].l, e); // 递归调用需要返回值!!!!!
    else if(e > t[rt].x) return fd(t[rt].r, e);
    else return rt;
}

// 找x的父节点
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
    else if(x > t[rt].x) return ranking(t[rt].r, x) + t[rt].sz_l + 1;
    else return t[rt].sz_l + 1;
}

//-------------------------------------------

int queryRkX(int rt, int k){ // 查询 排名为 k 的结点的值
    // TODO


}



int queryPrex(int rt, int x){// 求x的前驱：小于x，且最大的数
    // 若x有左节点，则为x的左子树最大结点；
    // 无，则看父节点。如果他是父节点的左子，则为父节点。否则，不存在
    int idx = fd(rt, x);
    if(t[idx].l != -1){ // 有左节点
        return t[findMaxNode(t[idx].l)].x;
    }
    else{
        int father = findFather(rt, idx, -1);
        if(t[father].l == idx){ // 是父节点的左子，则为父节点
            return t[father].x;
        }else{
            return -2147483647;
        }
    }
}

int queryPost(int rt, int x){ // 求x的后继：大于x，且最小的数
    /* 
    x的右结点的左子树。
        如果没有右结点：看父节点。如果他是父节点的左子，则为父节点。否则，不存在
        有：看右结点的左子树的最小值
    */
    int idx = fd(rt, x);
    if(t[idx].r == -1){ // 没有右结点
        int father = findFather(rt, x, -1);
        if(t[father].l == idx){ // 是父节点的左子
            return t[father].x;
        }else{
            return 2147483647;
        }
    }
    else{
        int right = t[idx].r;
        int min_idx = findMinNode(right);
        return t[min_idx].x;
    }
}

int main(){
    int n, q, op, x;
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
                cout << queryRkX(0, x) << endl;
                break;
            }
            case 3:{ // 求x的前驱：小于x，且最大的数
                cout << queryPrex(rt, x) << endl;
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
    cout <<endl << ranking(rt, 1)<<' '<< ranking(rt, 6)<<' '<<ranking(rt, 13);
}

/*
11
5 8
5 3
5 10
5 1
5 6
5 4
5 14
5 7
5 13
1 10
2 6

7
5 1
5 3
5 5
1 3
2 2
3 3
4 3
*/


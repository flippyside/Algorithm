#include <iostream>
#include <string>
using namespace std;

const int N = 1e6;

// 双向循环链表

struct P{
    int id;
    int st; // 状态
    P* le, *ri;
};

void add(P* dh, int i){
    P* cur = dh;
    while(cur->ri->id != -1){
        cur = cur->ri;
    }
    P* p = new P;
    cur->ri->le = p;
    p->id = i; p->st = 1;
    p->ri = cur->ri;
    p->le = cur;
    cur->ri = p;
}

int main(){
    int n,m,k;
    cin>>n>>m>>k;
    // m 表示报数为m的小蓝鲸出列。
    // k 表示编号为k的倍数的小蓝鲸出列之后，反转报数的方向。

    P* dummy_head = new P;
    dummy_head->id = -1; dummy_head->st = 0; 
    dummy_head->le = dummy_head; dummy_head->ri = dummy_head;

    for(int i = 1; i <= n; i++) add(dummy_head, i);
    
    P* cur = dummy_head->ri;
    bool f = true; // 是否反转
    while(n--){
        for(int i = 0; i <= m;){
            if(cur->st) {
                i++;
                if(i == m) break;
            }
            if(f) cur = cur->ri;
            else cur = cur->le;
        }
        cout << cur->id <<' ';
        if(cur->id % k == 0) f = (f == true) ? false : true;
        cur->st = 0;
        if(n == 0) break;
        if(f) cur = cur->ri;
        else cur = cur->le;
    }
}

void traverse(P* dh){
    P* cur = dh;
    int cnt = 0;
    while(cnt!=16){
        cout << cur->id;
        cur = cur->ri;
        cnt++;
    }
}

/*
    P* cur = dummy_head->ri;
    bool f = true;
    while(cnt != 0){
        for(int i = 0; i <= m;){
            if(cur->st) {
                i++;
                if(i == m) break;
            }
            if(f) cur = cur->ri;
            else cur = cur->le;
        }
        cnt--;
        cout << cur->id <<' ';
        if(cur->id % k == 0) f = (f == true) ? false : true;
        cur->st = 0;
        if(cnt == 0) break;
        if(f) cur = cur->ri;
        else cur = cur->le;
*/
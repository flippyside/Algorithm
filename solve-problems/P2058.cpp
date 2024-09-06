// 队列
#include<iostream>
#include<cstring>
using namespace std;
typedef unsigned long long ull;
const int N = 1e6;
const int TIME = 86400;

struct P{
    int boat;
    int id;
    int l, r;
}p[N]; // 记录国家
// int tm[N] = {}; // every boat's arrive time
int q[N], hh = 0, tt = -1;
bool st[N]; // 该国籍是否被记录过
// 1+1*3+4
int main(){
    int n,t,k,timer = 0, idx = 0;
    cin>>n;
    // p[1].ne = 2;
    p[0].r = 1; p[0].l = 1; p[0].boat = -1; p[0].id = -1; // dummy head
    while(n--){
        cin>>t>>k;
        for(int i = hh; i <= tt; i++){
            if(t - q[i] > TIME) hh++; // 踢出队列
        }
        while(k--){
            p[0].r = 
        }
    }
}


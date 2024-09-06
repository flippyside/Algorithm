// 队列
#include<iostream>
#include<cstring>
using namespace std;
typedef unsigned long long ull;
const int N = 1e6;
const int TIME = 86400;
/*
船编号：1~n
每艘船有一个数组，记录出现过的数字。一个时间
*/
struct P{
    int k;
    int t;
    int* arr;
}p[N]; // 记录国家
// int tm[N] = {}; // every boat's arrive time
int q[N], hh = 0, tt = -1;
bool st[N]; // 该国籍是否被记录过
// 1+1*3+4
int main(){
    int n,t,k,timer = 0, idx = 0;
    cin>>n;
    // p[1].ne = 2;
    int idx = 0; // boat
    while(n--){
        idx++;
        cin>>t>>k;
        p[idx].t = t; p[idx].k = k;
        for(int i = hh; i <= tt; i++){
            if(t - q[i] > TIME) hh++; // 踢出队列
        }
        memset(st,0,sizeof st);
        p[idx].arr = new int[k];
        int tmp, j = 0;
        for(int i=0;i<k;i++){ // 国籍
            cin>>tmp;
            if(!st[tmp]){
                *(p[idx].arr + j*4) = tmp;
                st[tmp]=true;
                j++;
            }
        }
        memset(st,0,sizeof st);
        int cnt = 0;
        for(int i = hh; i <= tt; i++){
            // 遍历每个p[i]的arr数组，用st数组记录出现过的数字

        }
    }
}


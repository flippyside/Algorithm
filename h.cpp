#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <memory.h>
using namespace std;
typedef pair<int,int> pii;

const int N = 100010;

int h[N], e[N], ne[N], idx;
// h[i]: 第i个单链表
bool st[N]; // 存储点的遍历情况
int ans;

void add(int a,int b){
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}

// 以u为根的子树中 点的数量
void dfs(int u){
    st[u] = true; // 已经被遍历
    for(int i = h[u]; i != -1; i = ne[i]){
        int j = e[i];
        if(!st[j]) dfs(j);
    }
}

int main(){
    memset(h, -1, sizeof(h)); // 初始化头节点
}





// char e[N];
// char stk[N];
// int tt;
// // tt: 栈顶元素下标

// int main()
// {
//     for(int i = 0; e[i] != '\0'; i++){
//         if(e[i] == '(') continue;
//         else if(e[i] == ')') stk[++tt] = e[i] = '\0';
//         else stk[++tt] = e[i];
//     }
//     while(tt > 0){
//         while(stk[tt] != '\0') {
//             char s[3]; int res;
//             s[0] = stk[tt--];
//             s[1] = stk[tt--];
//             s[2] = stk[tt--];
//             switch (s[1])
//             {
//             case '+':
//                 res = int(s[0]) + int(s[2]);
//                 break;
//             case '-':
//                 res = int(s[0]) - int(s[2]);
//                 break;
//             case '*':
//                 res = int(s[0]) * int(s[2]);
//                 break;
//             }
//             stk[++tt] = char(res);
//         }
//         stk[tt - 1] = stk[tt];
//     }
//     cout << 5 / -3;
// }
/*
(2+2)*(1+1)

\0
1
+
1
*
\0
2
+ 
2
*/
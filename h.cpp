#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <memory.h>
using namespace std;

const int N = 100010;
int q[N], hh = 0, tt = -1;

int main(){
    int m;
    cin >> m;
    while(m--){
        string op;
        if(op == "push") { int x; cin >> x; q[++tt] = x;}
        else if(op == "pop") {}
    }
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
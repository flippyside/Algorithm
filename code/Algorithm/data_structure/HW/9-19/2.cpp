/*
小蓝鲸想开发一种括号编辑器，它可以接收正确的括号序列，并对其进行编辑。

正确的括号序列是指对于序列中的任何一个左括号"("都能找到与之对应的右括号")"，同时任何一个右括号")"都能找到与之对应的左括号"("。例如，序列"(())()"、"()"和"(()())"是正确的，而")("、"(()" 和"(()))("则不是。

小蓝鲸希望自己的括号编辑器支持三种操作，分别是

L— 向左移动一格光标
R 向右移动一格光标
D 删除光标所在的括号，删除 与之配对 的括号以及它们 之间的所有括号 (即删除光标所在括号和与之配对的括号之间的子串)
执行 D操作后，光标会移动到 右侧 最近的括号。如果没有这样的括号，则光标会移动到 左侧 最近的括号。

输入格式
每个测试用例包含三行

第一行包含三个整数 n,m,p (1≤n≤100,1≤m≤100,1≤p≤n)，分别表示正确括号序列的长度、操作的数量、光标的初始位置。
序列中的位置从 1 开始计数，从左至右编号。输入保证 n为偶数。
第二行是由 n个字符组成的字符串"("和")"，输入保证构成正确的括号序列。
第三行是由 m字符组成的关于字符串 "L"、"R"和 "D"的操作序列。输入保证不会删除整个序列，同时光标不会移动到序列之外的位置。
输出格式
对于每个测试用例，输出一行，打印出正确的括号序列，这是对初始序列进行所有运算后得到的结果。

样例1
Input

8 4 5
(())()()
RDLD

Output
()

样例2
Input

12 5 3
((()())(()))
RRDLD
Output

(()(()))
*/
#include <iostream>
#include <cstring>
using namespace std;
const int N = 1e4;

struct P{
    int v; // v = 0:(  v = 1:)
    int id; // id相同的p[i]是配对的
    bool st; // 状态，false表示被删除
    P():v(-1),id(-1),st(true){}
    P(int v, int id, bool st):v(v),id(id),st(st) {}
}p[N];

int stk[N];
int tt = -1;

int main(){
    int n, m, s;
    char a[N], op[N];
    cin >> n >> m >> s; // 正确括号序列的长度、操作的数量、光标的初始位置
    cin >> a >> op; // 正确的括号序列 操作序列
    for(int i = 1; i <= n; i++){
        char ch = a[i - 1];
        if(ch == '(') p[i] = P(0, -1, true);
        else p[i] = P(1, -1, true);
    }
    int idx = 1;
    for(int i = 1; i <= n; i++){
        if(p[i].v == 0){
            stk[++tt] = i;
        }else{
            p[stk[tt]].id = p[i].id = idx; // 配对
            idx++;
            tt--;
        }
    }
    // for(int i = 1; i <= n; i++) cout << p[i].v << ' ' << p[i].id << endl;
    int pos = s;
    for(int i = 0; i < m; i++){
        // cout << pos << endl;
        switch(op[i]){
            case 'L':{
                do{
                    pos--;
                }
                while(p[pos].st == false);
                break;
            }
            case 'R':{
                do{
                    pos++;
                }while(p[pos].st == false);
                break;
            }
            case 'D':{
                // p[pos].st = false;
                // cout << pos << endl;
                for(int ii = 1; ii <= n; ii++){
                    if(p[ii].id == p[pos].id && ii != pos){
                        for(int j = min(ii, pos); j <= max(ii, pos); j++){ p[j].st = false;}
                        // cout << endl;
                        break;
                    }
                }
                // 执行 D操作后，光标会移动到 右侧 最近的括号。
                do{
                    pos++;
                    if(pos > n) break;
                }
                while(p[pos].st == false);
                // 如果没有这样的括号，则光标会移动到 左侧 最近的括号。
                if(pos > n){
                    do{
                        pos--;
                        if(pos < 0) break;
                    }while(p[pos].st == false);
                }
                break;
            }
        }
    }
    for(int i = 1; i <= n; i++){
        if(p[i].st){
            if(p[i].v == 0) cout<<'(';
            else cout<<')';
        }
    }
}

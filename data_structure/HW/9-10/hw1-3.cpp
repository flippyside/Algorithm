#include <iostream>
#include <string>
using namespace std;

const int N = 1e3;
int g[N][N] = {};
/*
给定一个 m∗n 的矩阵，如果某一行/列的 0 的个数为奇数，那么将这一行/列的所有数都置零；否则不变。
*/

int main(){
    int m, n, cnt;
    cin>>m>>n;
    for(int i = 0; i < m; i++)
        for(int j = 0; j < n; j++)
            cin >> g[i][j];
    
    for(int i = 0; i < m; i++){
        cnt = 0;
        for(int j = 0; j < n; j++){
            if(g[i][j] == 0) cnt++;
        }
        if(cnt % 2 != 0) g[i][n] = 1;
    }

    for(int i = 0; i < n; i++){
        cnt = 0;
        for(int j = 0; j < m; j++){
            if(g[j][i] == 0) cnt++;
        }
        if(cnt % 2 != 0) for(int j = 0; j < m; j++) g[j][i] = 0;
    }

    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){ 
            if(g[i][n] == 1) cout << 0 << ' ';
            else cout << g[i][j] << ' ';
        }
        cout << endl;
    }
}

/*
3 4
1 2 3 1
0 0 0 0
1 0 1 2
*/


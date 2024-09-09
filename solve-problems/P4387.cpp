#include <iostream>
#include <string>
#include <cstring>
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;

const int N = 1e6;
int ans = 0;
int stk[N], tt = -1;

// min(a[j] - a[i]), j<i

int main(){
    int q; cin >> q;
    
    while(q--){
        int n; cin >> n;
        int x;
        int tmp = n;
        while(tmp--){
            cin >> x;
            stk[++tt] = x;
        }
        bool flag = true;
        memset(stk, 0, sizeof stk);
        while(n--){
            cin >> x;
            if(stk[tt--] != x) {cout << "No" << endl; flag = false; break;}
        }
        if(flag) cout << "Yes" << endl;
    }
}

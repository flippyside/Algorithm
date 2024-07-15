#include <iostream>
#include <string>
using namespace std;
typedef pair<int, int> pii;

const int N = 1e5;
pii p[N], idx;

// 按右端点排序
void qs(int l, int r){
    if(l >= r) return;
    int i = l - 1, j = r + 1, mid = i + j >> 1;
    while(i < j){
        do i++; while(p[i].second < p[mid].second);
        do j--; while(p[j].second > p[mid].second);
        if(i < j) swap(p[i], p[j]);
    }
    qs(l, j); qs(j + 1,r);
}

int main(){
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        int a, b;
        cin >> a >> b;
        p[i] = {a, b};
    }
    qs(0, n - 1);
    int res = n;
    cout << res;
}


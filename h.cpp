#include <iostream>
#include <string>
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;

const int N = 12;

int power10(int x){ // 10 的 x 次方
    int res = 1;
    while(x--) res *= 10;
    return res;
}

int get(int arr[], int l, int r){ // arr从l到r代表的数字
    int res = 0;
    for(int i = l; i >= r; i--)
        res = res * 10 + arr[i];
    return res;
}

// 计算1 ~ n中数字的每一位共出现x的次数
int count(int n, int x){
    // 1 <= xxxiyyy <= n
    int res = 0;
    if(!n) return 0;
    // 数组存储数字
    int arr[N] = {}, cnt = 0;
    while(n){
        arr[cnt++] = n % 10;
        n /= 10;
    }
    n = cnt;
    for(int i = n - 1; i >= 0; i--){
        // xxx < abc, 此时xxx1yyy一定小于abcdefg，故 yyy = 000 ~ 999。总数为`abc*1000`
        if(i < n - 1){
            res += get(arr, n - 1, i + 1) * power10(i);
            if(x == 0) res -= power10(i);
        }
        // xxx = abc
        // 1 = d
        if(x == arr[i]){
            res += get(arr, i - 1, 0); // egf
        }
        // 1 < d
        else if(x < arr[i]) res += power10(i);
    }
}



int main(){
    int a, b;
    while(cin >> a >> b, a || b){
        if(a > b) swap(a, b);
        for(int i = 0; i < 10; i++) cout << count(b, i) - count(a - 1, i) << ' ';
        cout << endl;
    }
}

// int _sizeof(int x){
//     int res = 0;
//     while(x){
//         x /= 10;
//         res++;
//     }
//     return res;
// }

// bool cmp(string a, string b){ // 1: a >= b
//     if(a.size() != b.size()) return a.size() > b.size();
//     else{
//         for(int i = 0; i < a.size(); i++){
//             if(a[i] != b[i]) return a[i] > b[i];
//         }
//         return true;
//     }
// }

// void f(string a, string b){ // 补齐
//     if(cmp(a, b)){
//         int len = a.size() - b.size();
//         while(len--){
//             b = "0" + b;
//         }
//     }else{
//         int len = b.size() - a.size();
//         while(len--){
//             a = "0" + a;
//         }        
//     }
// }

// void dp(string a, string b){
//     for(int i = 0; i < 10; i++){
//         // 统计数字 i 在每一位上出现的次数
//         if(a > b) swap(a,b);
//         int sz = _sizeof(b);
//         f(a, b);
//         // a <= xxjyy <= b
//         for(int j = 0; j < sz; j++){
//             string pre_a;
//             while(j){
//                 pre_a += a[p];
//             }
//         }
//     }
// }

// int main(){
//     string a, b;
//     cin>>a>>b;
//     while(a != "0" && b != "0"){
        
//     }
        
    
// }








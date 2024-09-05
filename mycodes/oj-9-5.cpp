#include<iostream>
#include<cstring>
using namespace std;

typedef long long ll;
const int N = 30;
int arr[N];
bool is_Palindromic(int n){// 十进制
    int len = 0, tmp = n;
    while(tmp){
        arr[len] = tmp % 10;
        tmp /= 10;
        len++;
    }
    int i = 0, j = len - 1;
    while(0 <= j){
        if(arr[i] != arr[j]) return false;
        i++; j--;
    }
    return true;
}

bool binary_is_Palindromic(int n){ // binary
    int i = 0, len = 0;
    while(n){
        arr[len] = n % 2;
        n /= 2;
        len++;
    }
    i = 0;
    int j = len - 1;
    while(j >= 0){
        if(arr[i] != arr[j]) return false;
        i++; j--;
    }
    return true;  
}

int main(){
    int s;
    cin >> s;
    for(int i = s + 1;;i++){
        if(is_Palindromic(i) && binary_is_Palindromic(i)) {cout << i; return 0;}
    }
}



// int main(){
//     int g[N][N];
//     int n;
//     cin >> n;
//     for(int i = 0; i < n; i++)
//         for(int j = 0; j < n; j++) 
//             cin >> g[i][j];

//     bool f = true;
//     for(int i = 0; i < n; i++)
//         for(int j = 0; j < n; j++)
//             if(i != j) {
//                 if(g[i][j]){
//                     f = false; break;
//                 }
//             }
//     if(f){
//         cout << "diagonal"; return 0;
//     }

//     f = true;
//     for(int i = 1; i < n; i++)
//         for(int j = 0; j < i; j++)
//             if(g[i][j]) {f = false; break;}
//     if(f){
//         cout << "upper"; return 0;
//     }

//     f = true;
//     for(int j = 1; j < n; j++)
//         for(int i = 0; i < j; i++)
//             if(g[i][j]) {f = false; break;}
//     if(f){
//         cout << "lower"; return 0;
//     }    
//     cout << "none";
// }

/*
给定一个 NxN 的非零方阵，判断其类型。输入的第一行是整数 N（N < 100），表示方阵的维度。接下来给出一个 NxN 的方阵，方阵中的每个元素都是自然数，且不超过 100。
1 0 0
2 3 0
4 5 5
如果它是对角矩阵（主对角线以外的元素全都为 0），请输出 "diagonal"
如果它是上三角矩阵（主对角线以下的元素全都为 0），请输出 "upper"
如果它是下三角矩阵（主对角线以上的元素全都为 0），请输出 "lower"
如果上面三种都不是，请输出 "none"
*/

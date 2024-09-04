字符串相关概念：

- 子串：`S[i...j], i <= j`
- 前缀：从第一个字母开始的子串。

  - 真前缀：不能是字符串本身
- 后缀：以最后一个字母结尾的子串。

  - 真后缀：同上。
- 子序列：提出若干元素，不改变相对位置，可以不连续

前缀函数：一个长度为 字符串长度 的数组。p[i]为：子串s[0..i]的最长的相等的真前缀与真后缀的长度。

- 真前缀 = 真后缀。eg abcdabc：abc = abc
- 最长的。eg abababab：ababab = ababab
- 真前缀的长度。如果没有相等的真前后缀，为0。

问题：给定一个字符串，求前缀函数：

```
int* prefix(string s){
    int* p = new int[N];
    int len = s.size();
    for(int i = 1; i < len; i++){
        int j = p[i - 1]; // 增加一个字符后，j最大为 p[i-1]+1
  
        // 若新增的字符s[i]和 上一轮循环的相等真前缀（也是目前最长的）的最后一个字符 不同，就将j退回到上上次循环
        while(j > 0 && s[i] != s[j]) j = p[j - 1];
  
        // j若退回到0，且字符相等，则应为1；若j没有被退回到0，说明s[i]!=s[j]，if为假
        if(s[i] == s[j])j++; 
        p[i] = j;
    }
    return p;
}

```

KMP

问题：给两个字符串，寻找其中一个字符串是否包含另一个字符串，如果包含，返回包含的起始位置。BBCABCDABABCDABCDABDE ABCDABD

```cpp
先求出ABCDABD的前缀函数：p[7]={0,0,0,0,1,2,0}
记录 已经匹配的长度
每次遇到不匹配的字符，就移动 已经匹配的长度 - 最后一个匹配的字符对应的p[i] 位
BBC ABCDAB ABCDABCDABDE
    ABCDABD  # D与空格不匹配，idx=6, D前面的B对应p[5]=2。所以向右移动 6 - 2 = 4位
	ABCDABD   

#include <iostream>
#include <string>
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;

const int N = 1e5;

void prefix(string s, int p[]){
    int len = s.size();
    for(int i = 1; i < len; i++){
        int j = p[i - 1]; // 增加一个字符后，j最大为 p[i-1]+1
      
        // 若新增的字符s[i]和 上一轮循环的相等真前缀（也是目前最长的）的最后一个字符 不同，就将j退回到上上次循环
        while(j > 0 && s[i] != s[j]) j = p[j - 1];

        // j若退回到0，且字符相等，则应为1；若j没有被退回到0，说明s[i]!=s[j]，if为假
        if(s[i] == s[j])j++; 
        p[i] = j;
    }
}

// 在s1中寻找s2
int main(){
    int p[N] = {};
    string s1, s2;
    cin >> s1 >> s2;
    prefix(s2, p); // 求前缀函数
    int n = s1.size(), idx = 0, len = s2.size();
    for(int i = 0; i < n; i++){
        // cout << i << ' ' << idx<<endl;
        if(s1[i] == s2[idx]){
            idx++;
            if(idx >= len) { // 找到了
                cout << i - len + 1 + 1 << endl;
                idx = p[idx - 1];
                // idx = 0;
                // i = i - len + 1;
            }
        }
        else{
            if(idx == 0) continue;
            else{
                i--;
                // int move_bit = idx - p[idx - 1];
                // idx -= move_bit;
                idx = p[idx - 1];
            }
        }
    }
    for(int i = 0; i < len; i++) cout << p[i] << ' ';
}

```

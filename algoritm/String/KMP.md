index
- 字符串相关概念
- 前缀函数
- KMP


# 字符串相关概念：

- 子串：`S[i...j], i <= j`
- 前缀：从第一个字母开始的子串。

  - 真前缀：不能是字符串本身
- 后缀：以最后一个字母结尾的子串。

  - 真后缀：同上。
- 子序列：提出若干元素，不改变相对位置，可以不连续

# 前缀函数：一个长度为 字符串长度 的数组。p[i]为：子串s[0..i]的最长的相等的真前缀与真后缀的长度。

- 真前缀 = 真后缀。eg abcdabc：abc = abc
- 最长的。eg abababab：ababab = ababab
- 真前缀的长度。如果没有相等的真前后缀，为0。

问题：给定一个字符串，求前缀函数：

```cpp
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

# KMP

问题：给两个字符串s1、s2，问s1是否包含s2，如果包含，返回包含的起始位置。

思路：
- 求出s2的前缀函数p
- 使用两个指针：i指向s1，idx指向s2
- 比较s1[i]和s2[idx]
    - 不等，只改变s2指针：`idx = p[idx - 1];`。使用while来加快速度。
    - 如果相等，就继续同时移动双指针。
        - 如果idx已经指向s2末尾后面，就输出结果

```cpp
先求出ABCDABD的前缀函数：p[7]={0,0,0,0,1,2,0}
记录 已经匹配的长度
遇到不匹配的字符，就移动 已经匹配的长度 - 最后一个匹配的字符对应的p[i] 位
BBC ABCDAB ABCDABCDABDE
    ABCDABD  # D与空格不匹配，idx=6, D前面的B对应p[5]=2。所以向右移动 6 - 2 = 4位
	ABCDABD   

void prefix(char s[], int p[]){
    int len = strlen(s);
    for(int i = 1; i < len; i++){
        int j = p[i - 1]; // 增加一个字符后，j最大为 p[i-1]+1
        
        // 若新增的字符s[i]和 上一轮循环的相等真前缀（也是目前最长的）的最后一个字符 不同，就将j退回到上上次循环
        while(j > 0 && s[i] != s[j]) j = p[j - 1];

        // j若退回到0，且字符相等，则应为1；若j没有被退回到0，说明s[i]!=s[j]，if为假
        if(s[i] == s[j])j++; 
        p[i] = j;
    }
}

void kmp(char s1[], char s2[]){
    int p[N] = {};
    prefix(s2, p); // 求前缀函数
    int n = strlen(s1), idx = 0, len = strlen(s2);
    for(int i = 0; i < n; i++){
        while(idx > 0 && s1[i] != s2[idx]) idx = p[idx - 1];
        if(s1[i] == s2[idx]){
            idx++;
            if(idx >= len) { // 找到了
                cout << i - len + 2 << endl; // 注意索引从1开始
                idx = p[idx - 1];
            }
        }
    }
    for(int i = 0; i < strlen(s1); i++) cout << p[i] << ' ';
}

// 在s1中寻找s2
int main(){
    char s1[N], s2[N];
    cin >> s1 >> s2;
    kmp(s1, s2);
}
```

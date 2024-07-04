# 算法分析

规模：n
执行算法所需的时间：T(n)

设每一步操作所用时间为常数c

线性表查询：
$ T(n)= cn $
赋值操作：
$ T(n)= c $
二重循环：
$ T(n)= cn^2 $

算法的增长率：输入的值增长时，算法代价的增长速率

- 线性增长率
- 二次增长率
- 指数增长率

上限（大O表示法）：对非负函数T(n)，若存在两个正常数c、n0，对任意n > n0，有T(n) <= cf(n)，则称T(n)在集合O(f(n))中。n0通常取1或者更小。

ADT：array-based list

# 双指针

1. 指向2个序列。如：归并排序
2. 指向1个序列。如：快排

```cpp
for(i = 0,j = 0; i < n; i++){
    while(j < i && check(i, j)) j++;
    //...
}
```



思路：

- 写出暴力算法
- 如果有单调性，考虑双指针优化

作用：将二重循环O(n^2)优化为O(n)。

给定一个长度为 n 的整数序列，请找出 最长 的不包含重复的数的 连续 区间，输出它的长度。

```cpp
// O(n^2)
for(int i = 0; i < n; i++){
    for(int j = 0; j <= i; j++){
        if(check(j, i)) result = max(result, i - j + 1);
    }
}
```

优化为：

```cpp
// O(kn)
int n;
cin >> n;
int arr[N];
int num[N]; // 记录数字出现的次数
for(int i = 0; i < n; i++) cin >> arr[i];
int res = 0;
for(int i = 0, j = 0; i < n; i++) {
    num[arr[i]]++;
    while(num[arr[i]] > 1){ num[arr[j]]--; j++; } // 若j和i之间有重复元素，则往右移
    res = max(res, i - j + 1);
}
```

# 位运算

n的二进制表示里，第k位数是什么?

思路：`n >> k & 1`

- 把第k位移到最后一位：`n >> k`
- 看最后一位：`n & 1`

求二进制数：

```cpp
int n = 2047;
for (int k = log(n) / log(2); k >= 0; k--)
{
    cout << (n >> k & 1);
}
```

lowbit(x)：返回x的最后一位1

```cpp
x & ~x + 1
```

```cpp
x = 1001000
~x = 0110111
~x + 1 = 0111000 // 补码
x & (~x + 1) = 0001000 
```

# 离散化

思想：把范围很大的一系列数字映射到范围较小的连续数字。

```cpp
1 2 49 300 202000 ...
0 1 2   3     4 ...
```

```cpp
vector<int> arr;

int find(int x){
    int p = 0, q = arr.size() - 1;
    while(p < q){
        int mid = p + q >> 1;
        if(arr[mid] >= x) q = mid;
        else p = mid + 1;
    }
    return q; // x映射到q
}

int main()
{
    sort(arr.begin(), arr.end());
    arr.erase(unique(arr.begin(), arr.end()), alls.end());
}
```

eg：区间和

```cpp
typedef pair<int, int> pii;
const int N = 300005;

vector<pii> arr, ques;
vector<int> alls;
int ans[N], s[N];

int find(int x){
    int l = 0, r = alls.size() - 1;
    while(l < r){
        int mid = l + r >> 1;
        if(alls[mid] >= x) r = mid;
        else l = mid + 1;
    }
    return r + 1;
}

int main()
{
    int m,n;
    cin >> n >> m;

    for(int i = 0; i < n; i++){
        int x, c;
        cin >> x >> c;
        arr.push_back({x, c});
        alls.push_back(x);
    }

    for(int i = 0; i < m; i++){
        int l, r;
        cin >> l >> r;   
        ques.push_back({l, r});
        alls.push_back(l);
        alls.push_back(r);
    }   
    // 去重
    sort(alls.begin(), alls.end());
    alls.erase(unique(alls.begin(), alls.end()), alls.end());
    for(auto it : arr){
        int x = find(it.first);
        ans[x] += it.second;
    }
    for(int i = 1; i <= alls.size(); i++) s[i] = s[i - 1] + ans[i];
    for(auto it : ques){
        int l = find(it.first);
        int r = find(it.second);
        cout << s[r] - s[l - 1] << endl;
    }
}
```

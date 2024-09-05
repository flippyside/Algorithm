
# 高斯消元

$$
\begin{cases}
a_{11}x_{1}+a_{12}x_{2}+ \dots +a_{1n}x_{n}=b_{1}  \\
a_{21}x_{1}+a_{22}x_{2}+ \dots +a_{2n}x_{n}=b_{2}  \\
\dots \\
a_{n1}x_{1}+a_{n2}x_{2}+ \dots +a_{nn}x_{n}=b_{n}   \\
\end{cases}
$$

实现操作：
1. 把某一行乘以一个非零数k
2. 交换某2行
3. 把某一行的k倍加到另一行

思路：
- 遍历所有列
  - 找到第 i 列的绝对值最大的元素所在的行 j
  - 将行 j 与行 1交换，并将行 j 的第 i 列的元素化为 1
  - 用行 j 将下面的所有行的第 i 列的元素化为 0

结果：
- 阶梯型：唯一解
- 0 = 非零：无解
- 0 = 0：无穷解


```cpp
int gauss()
{
    int cur = 0, row = 0;
    // 遍历系数矩阵所有列
    for (cur = 0; cur < n; cur++)
    {
        // 当前列：cur
        // 当前行：row
        // 最大绝对值元素所在行：t
        int t = row;
        // 1. 找第 cur 列的绝对值最大的元素
        for (int i = row; i < n; i++)
            if (fabs(g[i][cur]) > fabs(g[t][cur])) t = i;

        if (fabs(g[t][cur]) < eps) continue; // 如果绝对值最大的元素为 0，直接跳过

        // 2. 交换 第 t 行和第 row 行
        for (int i = cur; i < n + 1; i++)
            swap(g[t][i], g[row][i]);
        // 将第 row 行的元素化为 1。注意要从前往后
        for (int i = n; i >= 0; i--)
            g[row][i] /= g[row][cur];
        // now g[row][cur] = 1
        // 3. 消去第 row 行后面的行的第 cur 列元素
        for (int i = row + 1; i < n; i++)
            if (fabs(g[i][cur]) > eps) // 如果非0
                for (int j = n; j >= cur; j--)
                    g[i][j] -= g[row][j] * g[i][cur];
        row++;
    }
    // 4. 判断解的情况
    if (row < n) // 不是有唯一解
    {
        for (int i = row; i < n; i++)
            if (fabs(g[i][n]) > eps)
                return 2; // 出现 0 = 非零，无解
        return 1; // 有无穷解
    }
    /*
    1 2 -1 -6
    0 1 1 1
    0 0 1 3
    */
   
   // 现在 g 为上三角矩阵
   // 5. 回代求解
    for (int i = n - 1; i >= 0; i--) // 从最后一行开始
        for (int j = i + 1; j < n; j++)
            // x2 + g[i][j] * x3 = b3
            // new(g[i][n]) + g[i][j] * g[j][n] = g[i][n]
            g[i][n] = g[i][n] - g[i][j] * g[j][n]; // 用已知的解(g[j][n])求解上一行的解g[i][n]，常数项是g[i][n]
    /*
    1 2 -1 1
    0 1 1 -2
    0 0 1 3
    */
    return 0; // 有唯一解
}
```


# 求组合数

## 递推

适用于：数量多，数据小。

$$
\binom{a}{b} = \binom{a-1}{b} + \binom{a-1}{b-1}
$$

```cpp
int c[N][N];
void init()
{
    for(int i = 0; i < N; i++){
        for(int j = 0; j <= i; j++){
            if(!j) c[i][j] = 1;
            else c[i][j] = (c[i - 1][j] + c[i - 1][j - 1])%mod; // // C(a, b) = C(a - 1, b) + C(a - 1, b - 1)
        }
    }
}
```

## 逆元

适用于：数量少，数据大。

$$
\binom{a}{b} = \frac{a!}{(a-b)!b!}
$$

思路：将除法转化为逆元

逆元：
$$
\frac{a}{b} = ab^{-1} (mod\ m), x=b^{-1}(mod\ m)\\
$$

$$
\begin{align*}
&fact[i]=i! mod\ 10^9+7 \\
&infact[i]=(i!)^{-1} mod\ 10^9+7 \\
&\binom{a}{b} = \frac{a!}{(b-a)!b!} = fact[a]*infact[a-b]*infact[b]
\end{align*}
$$

```cpp
int fact[N], infact[N];

//计算 a^k mod p
int qmi(int a, int k, int p){
    int res = 1;
    while(k){
        if(k & 1) res = (ll) res * a % p; //  k 的当前位（最低位）是 1，将当前的 a 乘到 res 上
        a = (ll)a * a % p; // a 平方
        k >>= 1;
    }
    return res;
}

int main(){
    fact[0] = infact[0] = 1;
    for(int i = 1; i < N; i++){
        // fact[i] = i! mod 10^9+7
        // infact[i] = (i!)^{-1} mod 10^9+7 
        fact[i] = (ll)fact[i - 1] * i % mod;
        infact[i] = (ll)infact[i - 1] * qmi(i, mod - 2, mod) % mod;
    }
    int n;
    cin >> n;
    while(n--){
        int a,b;
        cin>>a>>b;
        // C(a, b) = fact[a] * infact[a - b] * infact[b]
        cout << (ll) fact[a] * infact[b] % mod * infact[a - b] % mod << endl;
    }
}
```

## 卢卡斯定理

适用于：数量很少，数据极大(1e18)

$$
\binom{a}{b} \equiv \binom{b mod\ p}{a mod\ p} \binom{b / p}{a / p} (mod\ p)
$$

思路：
1. 快速幂
2. 组合数计算C：C(a, b) mod p = (a!)/(b!(a - b)!) mod p, (a/b) mod p = a * b^{p - 2} mod p
3. lucas：C(a, b) mod p = C(a mod p, b mod p) * C(a/p, b/p) (mod p)

```cpp
#include <iostream>
#include <string>
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;

const int N = 1e6;
const int mod = 1e9 + 7;
const int INF = 1e9;
int p;

int qmi(int a, int k){ // a^k mod p
    int res = 1;
    while(k){
        if(k & 1) res = (ll) res * a % p;
        a = (ll) a * a % p;
        k >>= 1;
    }
    return res;
}

// C(a ,b) = (a!)/(b!(a - b)!) mod p
// (a/b) mod p = a*b^{p - 2} mod p
int C(int a , int b, int p){
    int res = 1;
    for(int i = 1, j = a; i <= b; i++, j--){
        res = (ll) res * j % p; // 逐步计算(a!)/(a - b)!
        res = (ll) res * qmi(i, p - 2) % p; // 逐步计算(a/b)! 即 res * i^{p - 2} mod p
    }
    return res;
}

// C(a, b) = C(a mod p, b mod p) * C(a/p, b/p) (mod p)
int lucas(ll a, ll b){
    if(a < p && b < p) return C(a, b, p);
    return (ll) C(a % p, b % p, p) * lucas(a / p, b / p) % p;
}

int main(){
    int n;
    cin >> n;
    while(n--){
        ll a, b;
        cin >> a >> b >> p;
        cout << lucas(a, b) << endl;
    }
}
```

## 

$$
\binom{a}{b} = \frac{a(a-1)\dots (a-b+1)}{b(b-1) \dots 1} = \frac{a!}{b!(a-b)!}\\ \\
分解质因数：= p_{1}^{a_{1}}p_{2}^{a_{2}} \dots p_{k}^{a_{k}}
$$

思路：
1. 筛素数
2. 求分解式：每个素数对应的指数
3. 高精度乘法，把所有质因子乘起来




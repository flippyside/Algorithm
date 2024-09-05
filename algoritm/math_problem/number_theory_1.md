# 质数

在大于1的整数中，只包含1和本身这两个因子。

## 试除法判断质数

$$
O(\sqrt{n})
$$

```cpp
bool is_prime(int n){
    if(n < 2) return false;
    for(int i = 2; i <= n / i; i++)
        if(n % i == 0) return false;
    return true;
}
```

## 分解质因子


原理：

- n最多只有一个大于$\sqrt{n}$的质因子。
- 从最小的因数 2 开始，并且每次把所有能除掉的因数都除掉（即不断除以 `i`），所以 `i` 实际上代表了一个质数。这样，后续的 `i` 只会在 `n` 被前面所有较小质因数除干净后，才会再次被判断为 `n` 的因数。因此，后续判断的 `i` 一定是质数。

```cpp
void divide(int n){
    for(int i = 2; i <= n / i; i++){
        if(n % i == 0){ // 经过while循环处理，i一定是质数
            int s = 0;
            while(n % i == 0){
                n /= i;
                s++;
            }
            cout << i << " " << s << endl;
        }
    }
    if(n > 1) cout << n << " "<< 1 << endl; // 不要忘记剩下的
}
```

## 筛法

```
求出 1 ~ n中质数的个数。
```

指导思想：一个数字的 x 倍一定是合数。

1. 埃拉托色尼筛法：
   $$
   O(nloglog{n})
   $$

思路：删去 质数 的所有倍数。

1~n中有$n/ln{n}$个质数。

```cpp
int primes[N], cnt; // primes存储所有质数。cnt：质数的数量
bool st[N]; // st[x] = true，说明 x 被筛掉
void get_primes(int n){
    for(int i = 2; i <= n; i++){
        if(!st[i]){ // x 没被筛掉，即 x 是质数
            primes[cnt++] = i; 
            for(int j = i * 2; j <= n; j += i) st[j] = true; // 筛掉 i 的所有倍数
        }
    }
}
```

2. 线性筛法：优于埃拉托色尼筛法(未理解)

$$
O(n)
$$

确保 u 只被它的**最小质因子**筛掉

```cpp
int primes[N], cnt; // primes存储所有质数。cnt：质数的数量
bool st[N]; // st[x] = true，说明 x 被筛掉
void get_primes(int n){
    for(int i = 2; i <= n; i++){
        if(!st[i]) primes[cnt++] = i; // x 没被筛掉
        for(int j = 0; primes[j] <= n / i; j++){ // 枚举所有质数
            st[primes[j] * i] = true; // 筛掉 primes[j] * i
            if(i % primes[j] == 0) break; // prime[j] 是 i 的最小质因子
        }
    }
}
```

`if(i % primes[j] == 0) break;`：

- `i % primes[j] == 0`：`pj`是 `i`的最小质因子，故 `pj`是 `pj * i`的最小质因子
- `i % primes[j] != 0`：`pj`小于 `i`的最小质因子，故 `pj`是 `pj * i`的最小质因子

# 约数

## 试除法求约数

思路：如果 `d|n, 那么(n/d)|n`，即d、n/d 都是 n 的因子

$$
O(\sqrt n)
$$

```cpp
vector<int> get_divisors(int n){
    vector<int> res;
    for(int i = 1; i <= n / i; i++){
        if(n % i == 0){
            res.push_back(i);
            if(i != n / i) res.push_back(n / i); // 防止重复
        }
    }
    sort(res.begin(), res.end());
    return res;
}
```

## 求约数个数

$$
x = p_{1}^{a_{1}} p_{2}^{a_{2}}\dots p_{k}^{a_{k}} \\
 N = (a_{1}+1)(a_{2}+1)\dots(a_{k}+1)
$$

推导：

$$
因为x的因子可以表示成 d = p_{1}^{b_{1}} p_{2}^{b_{2}} \dots p_{k}^{b_{k}},\\
而b_{i}范围为(0, a_{i})，所以有(a_{i}+1)种取法，\\
分解式不同，对应的数字就不同，\\
由计数原理得，x的因子总数为所有b_{i}的取法的乘积。\\
$$

```cpp
int main(){
    int n;
    cin >> n;
    unordered_map<int, int> primes; // 存储pi和它的指数ai
    while(n--){
        int x;
        cin >> x;
        // 求 x 的分解式
        for(int i = 2; i <= x / i; i++){
            while(x % i == 0){
                x /= i;
                primes[i]++;
            }
        }
        if(x > 1) primes[x]++;
    }
    ll res = 1;
    for(auto it : primes) res = res * (it.second + 1); // (a1+1)(a2+1)...
    cout << res;
}
```

## 求约数之和

乘法分配律展开

$$
x = p_{1}^{a_{1}} p_{2}^{a_{2}}\dots p_{k}^{a_{k}} \\
 S = (p_{1}^0 + p_{1}^1+\dots +p_{1}^{a_{1}})\dots(p_{k}^0 + p_{k}^1+\dots +p_{k}^{a_{k}})
$$

```cpp
int main(){
    int n;
    cin >> n;
    unordered_map<int, int> primes; // 存储pi和它的指数ai
    while(n--){
        int x;
        cin >> x;
        // 求 x 的分解式
        for(int i = 2; i <= x / i; i++){
            while(x % i == 0){
                x /= i;
                primes[i]++;
            }
        }  
        if(x > 1) primes[x]++;
    }
    ll res = 1;
    for(auto it : primes) {
        int p = it.first, a = it.second;
        ll tmp = 1;
        while(a--) tmp = tmp * p + 1;
        res = res * tmp;
    }
    cout << res;
}
```

知识点：
计算

$$
x = p^0+p^1+p^2+\dots+p^a
$$

转换为代码：

```cpp
while(a--) x = x * p + 1;
```

总结：

```
如果 x = p1^c1 * p2^c2 * ... *pk^ck
约数个数： (c1 + 1) * (c2 + 1) * ... * (ck + 1)
约数之和： (p1^0 + p1^1 + ... + p1^c1) * ... * (pk^0 + pk^1 + ... + pk^ck)
```

## 计算最大公约数：欧几里得算法（辗转相除法）

$$
gcd(a,b) = gcd(b, a\mod b)
$$

```cpp
int gcd(int a, int b){
    if(b == 0) return a;
    return gcd(b, a % b);
}
```

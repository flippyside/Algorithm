# 数位DP

- 用【前缀和】的思想，`[X,Y] = f[1,Y] - f[1,X-1]`
- 用【树】的思想


```txt
problem
求给定区间[X,Y]中满足下列条件的整数个数：这个数恰好等于K个互不相等的B的整数次幂之和。
```

求0～N之间满足条件的个数

N：$a_{n-1},a_{n-2}...a_0$

```cpp
const int N = 33;
int n, m;
int K, B;
int f[N][N];

// 求给定区间[X,Y]中满足下列条件的整数个数：这个数恰好等于K个互不相等的B的整数次幂之和。
// 例如，k=4，B=2，即为1111。这是二进制表示。沿着这个思路拓展：
// 问题即为：在B进制的表示之下，有多少个 1
void init(){
    for(int i = 0; i < N; i++)
        for(int j = 0; j <= i; j++)
            if(j == 0) f[i][j] = 1;
            else f[i][j] = f[i - 1][j] + f[i - 1][j - 1];
}

string B_base(int num){ // 十进制转B进制
/*
    vector<int> res;
    while(num) res.push_back(n % B). n /= B;
    return res;
*/
    string res;
    while(num){
        res += to_string(num % B);
        num /= B;
    }
    reverse(res.begin(), res.end());
    return res;
}

int dp(int n){
    if(n == 0) return 0;
    string nums = B_base(n);
    int res = 0, last = 0; // last: 前面已经有1的个数
    for(int i = nums.size() - 1; i >= 0; i--){
        int x = nums[i] - '0';
        if(x != 0){ // 求左分支
            res += f[i][K - last];
            if(x > 1){
                if(K - last - 1 >= 0) res += f[i][K - last - 1];
                break;
            }
        }
        else{ // 右分支
            last++;
            if(last > K) break;
        }
    if(i == 0 && last == K) res++; // special judge 最右侧
    }
    return res;
}

int main(){
    B=2;
 //   scanf("%d%d", &n, &m);
cout<<B_base(10);
}
```





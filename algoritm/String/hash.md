index
- 不同字符串的个数


- 定义hash函数：通常使用p进制转换
- 读入字符串s，将它hash，遍历数组看之前是否存储过这个值，如果有，那么重复了。
- 我卡在数组这里很久，因为我希望用O（1）的复杂度去看是否存储过这个hash值，但ull的数字那么大，怎么可能用数组下标来表示。。。所以直接扔进数组里，以后遍历就行了。似乎也不会超时

```cpp
typedef unsigned long long ull;
const int N = 1e6, P = 131;
int n;
ull arr[N];

ull get_hash(string s){
    ull res = 0, p = 1;
    for(int i = 0; i < s.size(); i++){
        res += s[i] * p;
        p *= P;
    }
    return res;
}

int main(){
    cin >> n;
    ull cnt = 0;
    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        int val = get_hash(s);
        cnt++;
        for(int j = 0; j < i; j++){
            if(arr[j] == val) {
                cnt--;
                break;
            }
        }
        arr[i] = val;
    }
    cout << cnt;
}
```

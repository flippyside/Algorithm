// FFT
#include <iostream>
#include <cstring>
using namespace std;
const long double pi = 3.14159265358979323846;
const int TIME = 20;

long double sin_(long double x){ // sin1 = 0.841471
// sin2 = 0.90929742682
    long double res = 0, ele = 1, xx = x, sign = 1;
    for(int i = 0; i < TIME; i++){
        if(i != 0) ele *= (2 * i) * (2 * i + 1); // (2n+1)!
        res += sign * (xx / ele);
        sign *= -1; // (-1)^n
        xx *= x * x; // x^(2n+1)
    }
    return res;
}

long double cos_(long double x){ // cos1 = 0.540302
    long double res = 0, ele = 1, xx = 1, sign = 1;
    for(int i = 0; i < TIME; i++){
        if(i != 0) ele *= (2 * i) * (2 * i - 1); // (2n)!
        res += sign * (xx / ele);
        sign *= -1; // (-1)^n
        xx *= x * x; // x^(2n)
    }
    return res;
}

long long round_(long double x){
    if(x >= 0){
        if(x - (long long)x >= 0.5) return (long long)x + 1;
        else return (long long)x;
    }else{
        if(x - (long long)x <= -0.5) return (long long)x - 1;
        else return (long long)x;
    }
}

struct Complex{
    long double a, b; // a + bi

    Complex operator + (const Complex& x) const {
        Complex tmp;
        tmp.a = a + x.a;
        tmp.b = b + x.b;
        return tmp;
    }
    Complex operator - (const Complex&x)const{
        Complex tmp;
        tmp.a = a - x.a;
        tmp.b = b - x.b;
        return tmp;
    }
    bool operator!=(const Complex&x)const{
        return (a != x.a) || (b != x.b);
    }
    bool operator==(const Complex&x)const{
        return (a == x.a) && (b == x.b);
    }
    Complex operator * (const Complex& x) const {
        Complex tmp;
        tmp.a = a * x.a - b * x.b;
        tmp.b = a * x.b + b * x.a;  
        return tmp;
    }
    friend ostream& operator << (ostream& os, const Complex& x)
    {
        os << x.a << ' ' << x.b;
        return os;
    }   

    Complex(long double a = 0.0, long double b = 0.0):a(a),b(b){}
};

// Complex w_n = Complex(cos(2 * pi / length), sin(2 * pi / length));
// FFT: 系数表达式 -> 点值表达式
// Complex A[N], B[N];
Complex* FFT(Complex* P, int n, int flag){ // flag = 0, 表示为 逆FFT

    if(n == 1) return P;

    // 奇偶分组
    Complex* A1 = new Complex[n/2];
    Complex* A2 = new Complex[n/2];
    int idx = 0;
    for(int i = 0; i < n / 2; i++){
        A1[i] = P[2 * i];
        A2[i] = P[2 * i + 1];
    }

    // 递归计算
    Complex* y1 = FFT(A1, n / 2, flag);
    Complex* y2 = FFT(A2, n / 2, flag);
    
    delete[] P;

    // 单位根
    Complex w(1, 0);
    Complex wn1;
    if(flag == 1)
        wn1 = Complex(cos_(2 * pi / n), sin_(2 * pi / n));
    else
        wn1 = Complex(cos_(-1 * 2 * pi / n), sin_(-1 * 2 * pi / n));

    Complex* y = new Complex[n];
    for(int k = 0; k < n / 2; k++){
        y[k] = y1[k] + w * y2[k]; // y[k] = y1[k] + w^k * y2[k]
        y[k + n / 2] = y1[k] - w * y2[k]; // y[k+n/2] = y1[k] - w^k * y2[k]
        w = w * wn1; // 计算w^k： w^k = w^k-1 * w^1
    }
    return y;
}

Complex* mul(int n, int* a, int* b){
    Complex* A = new Complex[n], *B =  new Complex[n], *C =  new Complex[n];
    for(int i = 0; i < n; i++) { // 系数表达式
        A[i] = Complex(a[i], 0.0);
        B[i] = Complex(b[i], 0.0);
    }
    // 系数表达式 -> 点值表达式
    A = FFT(A, n, 1);
    B = FFT(B, n, 1);

    // 求C的点值表达式
    for(int i = 0; i < n; i++) C[i] = A[i] * B[i];
    
    C = FFT(C, n, 0); // 点值表达式 -> 系数表达式
    for(int i = 0; i < n; i++) C[i].a /= n; // 归一化
    return C;
}

string remove_pre0(string s){
    while(s[s.size() - 1] == '0'){
        s = s.substr(0, s.size() - 1);
    }
    return s;
}

string f(Complex* a, int n){
    string res;
    int carry = 0;
    for(int i = 0; i < n; i++){
        int num = round_(a[i].a) + carry; 
        carry = num / 10;
        res += to_string(num % 10);
    }
    if(carry) res += to_string(carry);
    res = remove_pre0(res);
    return res;
}

int main(){
    int n, m;
    cin >> n >> m;
    
    // 扩展至2的幂次
    int len = max(n, m);
    for(int i = 0; ; i++){
        if(len <= (1 << i)){
            len = 1 << i;
            break;
        }
    }
    // 将A(x)、B(x)的项数补充至相同。
    if(len < m + n) len <<= 1;

    int* a = new int[len];
    int* b = new int[len];
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < m; i++) cin >> b[i];
    

    Complex* C = new Complex[n];
    C = mul(len, a ,b);
    string res = f(C, len);
    for(int i = res.size() - 1; i >= 0; i--) cout << res[i];
}



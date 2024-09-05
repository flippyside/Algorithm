


数据：集合 eg全部矩阵
数据对象：一组实例/值。eg单个矩阵
数据元素：eg向量
数据项：数据对象的属性 eg元素

数据结构：某一数据对象，及该对象中所有数据元素之间的相互关系
- 逻辑结构
- 物理结构：存储结构

## ADT

## 算法

常用的算法描述方式

算法的五个特性：


<<<<<<< HEAD
空间
复杂度 (space complexity)是指当问题的规模以某种单位从 1 增加到 n 时，解决这个问题的
算法在执行时所占用的存储空间也以某种单位由 1 增加到 S(n),则称此算法的空间复杂度为 S(n); 时间复杂度 (time complexity)是指当问题的规模以某种单位从 1 增加到 n 时，解
•  27• 
决这个问题的算法在执行时所耗费的时间也以某种单位由 1 增加到 T(n),则称此算法的时
间复杂度为 T(n) 。

空间复杂度S(n)：问题规模从1->n时，算法占用的存储空间也从1->S(n)


程序步数：T(n)
- 声明语句：0
- 表达式：
    - 不包含函数调用：1
    - 包含函数调用：1 + 函数调用的步数
- 赋值语句：`变量 = 表达式` 表达式的步数
    - 如果`变量`为数组/字符串，则为变量的体积+表达式的步数
- 循环语句：
    - while(exp) do...: 执行一次的步数 = exp的步数
    - do...while(exp)：同上
    - for(init; exp1; exp2)：2
        - 第一次执行：init的步数+exp1的步数
        - 后续执行：exp1步数+exp2步数
- switch：
    - switch(exp){ ... } : exp步数
    - case 1: 语句 case 2: 语句 ... : 语句步数+前面所有case条件计算的步数
- 函数调用：0
- 函数执行：1
    - 若函数执行语句中包含传参，且传参的体积与实例特性有关，则为 参数的体积之和
    - 递归：考虑局部变量
- 动态内存管理：1
    - 若隐式调用了构造/析构函数，就转到函数调用
- 转移语句：continue\break\goto\return：1
    - return exp: exp步数

```cpp
float sum(float a[], const int n){ 
    float s = 0.0; count++;
    for(int i=0; i < n; i++) count+=2;
        s += a[i]; count++;
    count+=2;
    return s;count++;
=======
```c
int idx, e[N], l[N], r[N];

void i(){r[0]=1;l[1]=0;idx=2;}

void ath(){
    r[idx]=r[head];
    r[head]=idx;l[r[head]]=idx;
    l[idx]=head;
>>>>>>> 1c5c2e34157d55500b57430046c9f57e98d96ec4
}
// 程序步=3n+4
```

<<<<<<< HEAD
```cpp
x = sum(R, n);
// 程序步= 1 +（3n+4）
```

```cpp
for(int i = 0;i<n;i++){ // n+1
    for(int j=0;j<n;j++){ // n(n+1)
        c[i][j]=0; // n^2
        for(int k=0;k<n;k++) // n^2 (n+1)
            c[i][j]=c[i][j]+a[i][k]*b[k][j]; // n^3
=======
void insert(int k, int x){
    e[idx]=x;
    r[idx]=r[k];
    l[r[k]]=idx;
    r[k]=idx;
    l[idx]=k;
}

void remove(int k){//删除k
    r[l[k]]=r[k];
    l[r[k]]=l[k];
}

// 输入一个表达式，求其前缀、后缀形式

void pre(char s[]){
    for(int i=0;s[i]!='\0';i++){
        if(s[i]!='('&&s[i]!=')'&&s[i]!='+'){
            if(s[i+2]=='(') continue;

        }
>>>>>>> 1c5c2e34157d55500b57430046c9f57e98d96ec4
    }
}
// T(n)=2n^3+3n^2+2n+1
```

<<<<<<< HEAD

渐进的时间复杂度O(n)：当且仅当存在正整数c和n0，使得`T(n)<=c*f(n)`对所有的`n>=n0`成立，则称该算法的时间增长率在O(f(n))中，记为`T(n) = O(f(n))`

=======
int hh=0,tt=-1,q[N];
q[++tt]=x; // insert
q[hh++];// pop
while(hh<=tt)
void f(int arr[]){
    for(int i=0;i<N;i++){
        while(hh <= tt && q[hh]>=arr[i]) hh++; // pop the front
        if(hh<=tt) cout<<q[hh];
        else cout<<"-1";
        q[++tt]=arr[i];
    }
}

void w(){
    for(int i=0;i<N;i++){
        q[++tt]=arr[i];
        
    }
}
>>>>>>> 1c5c2e34157d55500b57430046c9f57e98d96ec4
```
T(n) = n^3 + 2n^2 + 1
令n>=n0>=1
     <= n^3 + 2n^3 + n^3
     = 4n^3  
T(n) = O(n^3)
```

$$
O(1)<O(log_2n)<O(n)<O()
$$



渐进的空间复杂度S(n)：在最坏情况下表示问题规模n的某个函数f(n)的数量级，S(n) = O(f(n))，指的是为解决问题所用到的辅助存储空间：临时工作单元、递归工作栈...




求时间复杂度：
```cpp
int i = 1;
while(i*i <= n) i++; 
// sqrt(n)
```

```cpp
int s=0;
for(int i = 1;i <= n;i++) // 
    for(j = i * i; j <= n; j++)
        s = s+1;
```




<!-- ```c
int idx, e[N], l[N], r[N];

void i(){r[0]=1;l[1]=0;idx=2;}

void ath(){
    r[idx]=r[head];
    r[head]=idx;l[r[head]]=idx;
    l[idx]=head;
}

void insert(int k, int x){
    e[idx]=x;
    r[idx]=r[k];
    l[r[k]]=idx;
    r[k]=idx;
    l[idx]=k;
}

void remove(int k){//删除k
    r[l[k]]=r[k];
    l[r[k]]=l[k];
} -->

// // 输入一个表达式，求其前缀、后缀形式

// void pre(char s[]){
//     for(int i=0;s[i]!='\0';i++){
//         if(s[i]!='('&&s[i]!=')'&&s[i]!='+'){
//             if(s[i+2]=='(') continue;

//         }
//     }
// }

// int hh=0,tt=-1,q[N];
// q[++tt]=x; // insert
// q[hh++];// pop
// while(hh<=tt)
// void f(int arr[]){
//     for(int i=0;i<N;i++){
//         while(hh <= tt && q[hh]>=arr[i]) hh++; // pop the front
//         if(hh<=tt) cout<<q[hh];
//         else cout<<"-1";
//         q[++tt]=arr[i];
//     }
// }

// void w(){
//     for(int i=0;i<N;i++){
//         q[++tt]=arr[i];

//     }
// }
// ```

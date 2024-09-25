
# chap1

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
}
// 程序步=3n+4

x = sum(R, n);
// 程序步= 1 +（3n+4）
```

```cpp
for(int i = 0;i<n;i++){ // n+1
    for(int j=0;j<n;j++){ // n(n+1)
        c[i][j]=0; // n^2
        for(int k=0;k<n;k++) // n^2 (n+1)
            c[i][j]=c[i][j]+a[i][k]*b[k][j]; // n^3
    }
}
// T(n)=2n^3+3n^2+2n+1
```


渐进的时间复杂度O(n)：当且仅当存在正整数c和n0，使得`T(n)<=c*f(n)`对所有的`n>=n0`成立，则称该算法的时间增长率在O(f(n))中，记为`T(n) = O(f(n))`

推导过程
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

```cpp
void f(float s[][], int m,int n,int k){
    float sum[];
    for(int i=0;i<m;i++){ // m
        sum[i]=0;
        for(int j=0;j<n;j++) sum[i]+=x[i][j]; // n
    }// m*n
    for(int i=0;i<m;i++) cout<<sum[i]; // m
}
// O(max(m*n, n)) = O(m*n)
```

```cpp
 template <class Type>
 void dataList<Type>::bubbleSort ( ) {
 //对表 Element[0] 到 Element[ArraySize-1]
 //逐趟进行比较, ArraySize 是表当前长度
       int i = 1;  int exchange = 1;	
 	 //当exchange为0则停止排序
       while ( i < ArraySize && exchange ) {  // n - 1
           BubbleExchange ( i, exchange );
           i++;
      } 	//一趟比较
 }

template <class Type>
void dataList<Type>::BubbleExchange(const int i, int & exchange ){
     exchange = 0;	           //假定元素未交换
     for ( int j = ArraySize-1; j>=i; j--) // n
        if ( Element[j-1] > Element[j] ) {	
	        Swap ( j -1, j );	 //发生逆序
		//交换Element[j-1]与Element[j]
            exchange = 1;	//做“发生了交换”标志
        }
 }

// O(n^2)
```


渐进的空间复杂度S(n)：在最坏情况下表示问题规模n的某个函数f(n)的数量级，S(n) = O(f(n))，这里的空间指的是为解决问题所用到的辅助存储空间：临时工作单元、递归工作栈...




求复杂度：
```cpp
int i = 1;
while(i*i <= n) i++; 
// O(sqrt(n))
```

```cpp
int s=0;
for(int i = 1;i <= n;i++) // n
    for(j = i * i; j <= n; j++) // i=1, n+1; i=2, n-4+1; i=3, n-9+1...i=\sqrt(n), n-n+1
    // = n\sqrt(n)-4-9-...-n + n + sqrt(n) = n\sqrt(n)-(\s(n)(\s(n)+1)(2\s{n}+1))/6+n+\s{n}
    // = n^{3/2} - n^{3/2}/3 = 2/3 n^{3/2}
        s = s+1;
// O(n^{3/2})
```


# chap2









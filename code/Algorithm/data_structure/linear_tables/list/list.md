链表

- 单链表
- 双链表
- 邻接表
- 单循环链表
- 双向循环链表
- 多项式
- 其它知识


# 链表与邻接表

- 单链表：邻接表：存储图、树
- 双链表：优化某些问题

## 单链表

`e[i]表示节点i的 值，ne[i]表示节点i的 next指针`

```
    head->3->5->7->9->null
idx       0  1  2  3  -1
e[0]=3 e[1]=5 e[2]=7 e[3]=9
ne[0]=1 ne[1]=2 ne[2]=3 ne[3]=-1
```

```cpp
const int N = 100010;
int head, e[N], ne[N], idx;
// head: 头节点的下标
// e[i]: 节点i的值
// ne[i]: 节点i的next指针
// idx：第idx个插入的数
// 第 k 个插入的点的下标是 k - 1

void init(){
    head = -1; idx = 0;
}

void add_to_head(int x){
    e[idx] = x;
    ne[idx] = head;
    head = idx;
    idx++;
}

// 将x插入 下标为 k（第 k + 1 个插入）的节点 的后面
void add(int k, int x){
    e[idx] = x;
    ne[idx] = ne[k];
    ne[k] = idx;
    idx++; 
}
// 删除 下标为 k（第 k + 1 个插入）的节点 的后面的点
void remove(int k){
    ne[k] = ne[ne[k]];
}

int main()
{
    int n;
    cin >> n;
    init();
    while(n--) {
        char op[2];
        int k,x;
        scanf("%s", op);
        if(op[0] == 'H') {
            scanf("%d", &x);
            add_to_head(x);
        }
        else if(op[0] == 'D'){
            scanf("%d", &k);
            if(k == 0) head = ne[head]; // 删除头节点
            else remove(k - 1);
        }
        else {
            scanf("%d%d", &k, &x);
            add(k - 1, x);
        }
    }
    for(int i = head; i != -1; i = ne[i])
        cout << e[i] << " ";
}
```

## 双链表

```
problem：
实现一个双链表，双链表初始为空，支持 5 种操作：
在最左侧插入一个数；
在最右侧插入一个数；
将第 k 个插入的数删除；
在第 k 个插入的数左侧插入一个数；
在第 k 个插入的数右侧插入一个数
```

数据结构：
- 将idx为0、1分别作为head、tail节点，真正的节点从idx=2开始
- 可方便地操作第k个插入的数

0：head
1：tail

```cpp
int e[N], l[N], r[N] ,idx; // l[i]表示节点i的左边节点, r[i]表示节点i的右边节点

// 初始化
void init(){
    r[0] = 1, l[1] = 0;
    idx = 2;
}

// 将x插到下标为k的节点的右边
void add(int k, int x){
    e[idx] = x;
    r[idx] = r[k];
    l[idx] = k;
    l[r[k]] = idx;
    r[k] = idx;
}
// 将x插到下标为k的节点的左边：add(l[k], x)

// 将下标为k的点删除
void remove(int k){
    r[l[k]] = r[k];
    l[r[k]] = l[k];
}
```

```cpp
int n, m, q;
const int N = 100010;
int e[N], r[N], l[N], idx, head, tail;

void init(){
    idx = 2; head = 0; tail = 1;
    r[0] = 1;
    l[1] = 0;
}

void remove(int k){
    r[l[k]] = r[k];
    l[r[k]] = l[k];
}
void insert(int k, int x){
    e[idx] = x;
    r[idx] = r[k];
    l[idx] = k;
    l[r[k]] = idx;
    r[k] = idx;
    idx++;
}

int main(){
    cin >> m;
    init();
    while (m--)
    {
        int x, k;
        char op[2];
        cin >> op;
        if(op[0] == 'L') { cin >> x; insert(0, x); } // 在链表的最左端插入数 x
        else if(op[0] == 'R') { // 在链表的最右端插入数 x
            cin >> x;
            insert(l[1], x); // 插到 尾结点的左节点 的后面
        }
        else if(op[0] == 'D'){ // 将第 k 个插入的数删除
            cin >> k;
            remove(k + 1); // 链表从2开始。k - 1 + 2 = k + 1
        }
        else if(op[0] == 'I'){
            if(op[1] == 'L') { // 在第 k 个插入的数左侧插入一个数
                cin >> k >> x;
                insert(l[k + 1], x);
            }
            else{ // 在第 k 个插入的数右侧插入一个数
                cin >>k>>x;
                insert(k + 1, x);
            }
        }
    }
    for(int i = r[0]; i != 1; i = r[i]) cout << e[i] << " ";
}
```

```
problem：
将 N 个同学排成一列，同学被编号为 1∼N，采取如下的方法：
- 先将 1 号同学安排进队列，这时队列中只有一个人；
- 2∼N 号同学依次入列，编号为 i 的同学入列方式为：指定编号为 i 的同学站在编号为 1∼(i−1) 中某位同学（即之前已经入列的同学）的左边或右边；

然后，从队列中去掉 M 个同学，其他同学位置顺序不变。

完毕后，从左到右输出编号。
```

数据结构：
- 虚拟头节点0，用来判断队伍的起终点

![Alt text](image.png)

```cpp
struct S{
    int l, r;
    int st; // 是否在队伍中
}s[N] = {0,0,0};

void insert(int p, int k, int i){
    switch(p){
        //s[k].l  s[i]  s[k]
        case 0:{ // insert s[i] to the left of s[k]
            s[s[k].l].r = i;
            s[i].l = s[k].l;
            s[k].l = i;
            s[i].r = k;
            break;
        }
        // s[k]  s[i]  s[k].r
        case 1:{ // insert s[i] to the right of s[k]
            s[s[k].r].l = i;
            s[i].r = s[k].r;
            s[k].r = i;
            s[i].l = k;
            break;
        }
    }
}

int main(){
    int n, k, p;
    cin >> n; // n students
    int len = 0;
    s[0].l = 0; s[0].r = 0; s[0].st = 0; // dummy head
    s[1].l = 0; s[1].r = 0; s[1].st = 1; // first student
    for(int i = 2; i <= n; i++){
        cin >> k >> p;
        s[i].st = 1;
        insert(p, k, i);
    }
    int m;
    cin >> m;
    while(m--){
        int x;
        cin >> x; 
        // remove stu[x] from the queue, if existed
        s[s[x].l].r = s[x].r;
        s[s[x].r].l = s[x].l;
        s[x].st = 0; 
    }
    for(int i = s[0].r; i ; i = s[i].r){
        if(s[i].st) cout << i << ' ';
    }
}
```

---

## 邻接表

多个单链表组成。

```c
head[1]-> ->...
head[2]-> ->...
head[3]-> ->...
...
```

## 单循环链表

## 双向循环链表

## other

### static

全局变量、static修饰的变量存放在静态存储区

静态成员变量：声明类定义时，就为它分配存储空间。所有对象共享。


```cpp
f(){
    int a = 1;
    static int b = 1;
    b = b + a;
    cout << a << b;
}
int main(){
    f();
// 1 2
    f();
// 1 3
}
```

```cpp
class Polynomial{
    struct Term{
        //...
    };

    static Term termArray[maxTerms];
    static int free, maxTerms;
private:
    int start, finish;
};
```

普通成员变量：声明类定义时，不会为它分配存储空间。只有在声明类的对象(实例化)时，才会为它分配空间




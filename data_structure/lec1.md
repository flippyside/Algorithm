


数据：集合 eg全部矩阵
数据对象：一组实例/值。eg单个矩阵
数据元素：eg向量
数据项：数据对象的属性 eg元素

数据结构：某一数据对象，及该对象中所有数据元素之间的相互关系
- 逻辑结构
- 物理结构：存储结构



```c
int head, idx, e[N], ne[N];

void init(){
    head=-1,idx=0;
}

void add(int x){
    e[idx] = x;
    ne[idx] = head;
    head = idx;
    idx++;
}
void p(){
    for(int i=head;i!=-1;i=ne[i];)cout<<e[i];
}
void insert(int i, int x){
    e[idx] = x;
    ne[idx] = ne[i];
    ne[i] = idx++;
    // 全部移动
    int tmp;
    for(int j=i;j!=-1;j=tmp){
        j = ne[j];
    }

}

int q[N], st[N], n, m, cnt = 0;

void f(int i){
    int tmp=m--;
    while(tmp){
        if(st[i]) tmp--;
        i = (i+1)%n;
    }
    st[i]=false;
}


```

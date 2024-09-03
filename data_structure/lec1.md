


数据：集合 eg全部矩阵
数据对象：一组实例/值。eg单个矩阵
数据元素：eg向量
数据项：数据对象的属性 eg元素

数据结构：某一数据对象，及该对象中所有数据元素之间的相互关系
- 逻辑结构
- 物理结构：存储结构



```c
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
}

// 输入一个表达式，求其前缀、后缀形式

void pre(char s[]){
    for(int i=0;s[i]!='\0';i++){
        if(s[i]!='('&&s[i]!=')'&&s[i]!='+'){
            if(s[i+2]=='(') continue;

        }
    }
}

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
```

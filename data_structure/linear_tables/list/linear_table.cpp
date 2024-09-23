
// 顺序表 Sequential table

# define maxSize 100
typedef int T;
typedef struct 
{
    T* data;
    int n;
}SeqList;

template<class T>
SeqList<T>::SeqList(int sz){
    if(sz>0){
        maxSize=sz; last=-1;
        data = new T[maxSize];
        if(data==nullptr) {
            cerr<<""<<endl;exit(1);
        }
    }
}


SeqList<T>::SeqList(SeqList<T>&L){
    maxSize=L.maxSize;
    
}

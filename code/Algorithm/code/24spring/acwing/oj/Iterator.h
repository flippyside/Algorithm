class MyArray{
  int *arr;
  int size;
public:
  class Iterator{
  int *p;
  public:
    Iterator(int *p) : p(p) { };
    ~Iterator(){
      p = nullptr;
    }
    bool get(int & value) const{// 获取当前迭代器所指向的元素
       if(p){
          value = *p;
          return 1;
       }
       return 0;
    }
    bool put(int value){// 向迭代器指向的元素存放值value
      if(p){
        *p = value;
        return 1;
      }
      return 0;
    }
    Iterator& operator++(){
        ++p;
        return *this;
    }
    const Iterator operator++(int){
        Iterator tmp = *this;
        ++p;
        return tmp;
    }
    Iterator& operator--(){
        --p;
        return *this;
    }
    const Iterator operator--(int){
        Iterator tmp = *this;
        --p;
        return tmp;
    }
    bool operator==(Iterator &a){
      return a.p == p;
    }
    bool operator!=(Iterator &a){
      return a.p != p;
    }
    Iterator& operator+(int len){
      p = p + len;
      return *this;
    }
    Iterator& operator-(int len){
      p = p - len;
      return *this;
    }    
  };

public:
  MyArray(int sz){
    arr = new int[sz];
    // Iterator ite(arr);
  }
  ~MyArray(){ // MyArray类的对象析构时，其所有的迭代器也应随之失效——调用get和put时返回值为false。
    // arr = nullptr;
    delete[] arr;
  }
  Iterator begin(){
    Iterator ite(arr);
    return ite;
  } // 返回的迭代器对象，指向数组的第一个元素arr[0]
  // 如果MyArray类中的arr数组为空（长度为0），Iterator begin()返回的迭代器应该指向哪儿？
  Iterator end(){
    Iterator ite(arr + size);
    return ite;
  } // 返回的迭代器对象，指向数组arr的末尾，但不是数组中的元素
}; 
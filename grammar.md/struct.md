index
- 操作符重载


操作符重载
```cpp
struct A{
    int e;
    int id;
    bool operator == (const A& a) const {return this->e == a.e; }
    bool operator > (const A& a) const {return this->e > a.e; }
    bool operator < (const A& a) const {return this->e < a.e; }
}a[N];
```
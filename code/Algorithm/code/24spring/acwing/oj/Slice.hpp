#include <memory>
#include <cstring>
#include <iostream>

struct SliceOutOfBoundError {};

class Slice {
private:
    std::shared_ptr<int> buf;// 指向当前切片所操作的底层数组
    size_t base;// 切片对应的区间 在底层数组中的 第一个位置的下标
    size_t length;// 切片对应的区间的长度
    size_t capacity;// 底层数组的大小

    static void free_buf(int *buf) {
        delete[] buf;
    }

    static std::shared_ptr<int> allocate_buf(size_t size) {
        return std::shared_ptr<int>(new int[size], free_buf);
    }

public:
    Slice(size_t size, int initial = 0) {
        // size: 新切片的大小 initial：初始值 
        this->base = 0;
        this->length = size;
        this->capacity = size * 2;// 底层数组的cap为其大小size的2倍.
        this->buf = allocate_buf(this->capacity);
        for(int i = 0; i < size; i++){
            buf.get()[i] = initial;
        }
    }

    Slice(const Slice &other) {
        // 构造出的新切片应该和原切片 共享 底层数组.
        this->buf = other.buf;
        base = other.base;
        length = other.length;
        capacity = other.capacity;
    }
    
    static Slice copy_from(const Slice &other) {
        // 返回的切片与原切片 不共享 底层数组, 新生成的切片的底层数组的cap大小为切片长度的2倍.
        Slice s(other.length, 0);
        s.base = other.base;
        s.length = other.length;
        s.capacity = s.length * 2;
        for(int i = 0; i < s.capacity; i++) {
            s.buf.get()[i] = other.buf.get()[i];
        }
        return s;
    }

    void operator=(const Slice &other) {
        // 与拷贝构造函数相似,但区别在于赋值操作会使原来切片指向的内容不再被使用. 共享底层数组
        this->buf = other.buf;
        base = other.base;
        length = other.length;
        capacity = other.capacity;        
    }

    void append(int x) {
    // 在切片的尾部加入一个元素 
        length++;
        if(length + base > capacity){
    // 否则为当前切片新申请一个空间（cap：切片加了元素之后大小的2倍）
            std::shared_ptr<int> tmp = allocate_buf(length * 2);
            for(int i = 0; i < capacity; i++){ // 复制原来的内容到新空间中,
                tmp.get()[i] = this->buf.get()[i];
            }
            tmp.get()[length - 1 + base] = x; // 然后在切片尾部追加新元素.
            this->capacity = length * 2;
            this->buf = tmp;
        }
        else{// 当底层数组的容量ok时,不扩容.
            this->buf.get()[length + base - 1] = x;
        }
    }

    Slice operator[](std::pair<size_t, size_t> range) {
// l 和 r 是相对于 base 的偏移量; 新切片和拷贝构造函数一样,和原切片共享底层数组.
//如果l和r不合法(l > r或者超出了底层数组的容量),此时需要抛出一个SliceOutOfBoundError(定义已经在slice.hpp中给出).
        int l = range.first + this->base, r = range.second + this->base;
        if(l > r || r > capacity){
            throw SliceOutOfBoundError();
        }
        //range:原切片的区间[l, r)。返回一个对应于这个区间的切片.
        int sz = r - l;
        Slice tmp(this->length);
        tmp.buf = this->buf;
        tmp.capacity = this->capacity;
        tmp.buf = this->buf;
        tmp.base = l;
        tmp.length = sz;
        return tmp;
    }

    int& operator[](size_t pos) {
        int p = pos + base;// pos是相对于base的偏移量.
        if(pos >= length){ // inlegal
            throw SliceOutOfBoundError();
        }else{
            return buf.get()[p]; // 获取切片中下标为pos的值的引用. 
        }
    }

    void print() {
        for (int i = 0; i < length; ++i) {
            std::cout << buf.get()[base + i] << ' ';
        }
        std::cout << '\n';
    }

    size_t len() {
        return length;
    }
    
    size_t cap() {
        return capacity;
    }
};
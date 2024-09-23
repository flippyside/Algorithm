#include <iostream>
#include <string>
#include <cstring>
using namespace std;

const int maxSize = 100;

template<class T>
struct SLinkNode{
    T data;
    int link;
};

template<class T>
class StaticList{
    SLinkNode<T> e[maxSize];
    int avil;
public:
    void init();
};

template<class T>
void StaticList<T>::init(){
    e[0] 
}



#include <iostream>
#include <string>
#include <cstring>
using namespace std;

template <class T>
struct LinkNode{
    T data;
    LinkNode<T> *link;
    LinkNode(LinkNode<T>* ptr = nullptr){link = ptr; }
    LinkNode(const T& item, LinkNode<T>* ptr = nullptr){
        data = item;
        link = ptr;
    }
};

template<class T>
class List{
public:

private:
    LinkNode* head;
};

// 单链表
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
    bool insert(int i, int &x);
    bool remove(int i, int &x);

private:
    LinkNode* first;
};

/*
1. 插到头节点之前
2. 插到队伍中
*/
template<class T> bool List<T>::insert(int i, int &x){
    if(first == nullptr || i == 0){
        LinkNode<T>* newnode = new LinkNode(x, first);
        first = newnode;
    }else {
        LinkNode<T>* cur = first;
        while(i != 1 && cur != nullptr){
            cur = cur->link;
            i--;
        }
        if(cur == nullptr) return false;
        else{
            LinkNode<T>* newnode = new LinkNode(x, cur->link);
            cur->link = newnode;
        }
    }
    return true;
}

template<class T> bool List<T>::remove(int i, int &x){
    LinkNode *del, * cur; // del为临时存储结点，cur为待删除结点的pre结点
    if(i == 0 || first == nullptr) return false;
    else if(i == 1){ // delete head
        del = first; first = first->link;
    }
    else{
        cur = first;
        for(int j = 2; j < i && cur != nullptr; j++){
            cur = cur->link;
        }
        if(cur == nullptr || cur->link = nullptr) return false;
        del = cur->link;
        cur->link = del->link;
    }
    delete del;
    return true;
}





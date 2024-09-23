
template<class T>
struct DblNode
{
    T data;
    DblNode<T> *lLink, *rLink;
    DblNode(DblNode<T>* left = nullptr, DblNode<T>*right = nullptr)
    : lLink(left), rLink(right) {}

    DblNode(T val, DblNode<T>* left = nullptr, DblNode<T>*right = nullptr)
    : data(val), lLink(left), rLink(right) {}
};


template<class T>
class DblList: public List<T>{
public:
    DblList(T val);
    ~DblList();
    bool remove(int i, int d); // delete the ith node, d = 0: pre direction; d = 1: suc direction
    DblNode<T>* first;
};

template<class T> bool DblList<T>::remove(int i, int d){
    DblNode<T>* cur = first;
    
}

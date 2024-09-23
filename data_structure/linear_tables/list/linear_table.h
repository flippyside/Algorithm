template<class T>
class SeqList{
    protected:
    T*data;
    int maxSize;
    int last;
    void reSize(int newSize);
    public:
    SeqList(int sz=defaultSize);
    SeqList(SeqList<T>&L);
    ~SeqList(){delete[] data; }
}
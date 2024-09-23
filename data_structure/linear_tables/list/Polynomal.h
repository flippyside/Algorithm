#include <iostream>
#include <string>
#include <cstring>
using namespace std;

struct Term{
    float coef; // 系数
    int exp; // 指数
    Term* link;
    Term(float c, int e, Term* next = nullptr){
        coef = c; exp = e; link = next;
    }
    Term* insertAfter(float c, int e);
    friend ostream& operator << (ostream&, const Term&);
};

class Polynomial{
public:
    Polynomial(){first = new Term(0, -1);}
    Polynomial(Polynomial& R);
    ~Polynomial();
    int maxOrder(); // 最大阶数
    Term* getHead() const {return first; }
private:
    Term* first;
    friend Polynomial operator+(Polynomial& A, Polynomial& B);
    friend Polynomial operator*(Polynomial& A, Polynomial& B);

};

Term* Term::insertAfter(float c, int e){
    link = new Term(c, e, link);
    return link;
}

/*
多项式加法
1. 双指针：pa指向多项式A，pb指向B，结果为C
2. 比较指数：
- 相等：相加，存入C，pa、pb同时+1
- 不等：小者加入C，其对应的指针+1
3. 将剩余的项扔进C

*/


Polynomial operator+(Polynomial& A, Polynomial& B){
    Term*pa = A.getHead()->link;
    Term*pb = B.getHead()->link;
    Polynomial C;
    Term* pc = C.first;
    while(pa != nullptr && pb != nullptr){
        int a = pa->exp, b = pb->exp;
        if(a == b){
            // 相等：相加，存入C，pa、pb同时+1
            int tmp = pa->coef + pb->coef;
            if(fabs(tmp) > 0.001) pc = pc->insertAfter(tmp, a);
            pa = pa->link; pb = pb->link;
        }
        else{
            // 小者加入C，其对应的指针+1
            if(a < b){
                pc = pc->insertAfter(pa->coef, a);
                pa=pa->link;
            }
            else{
                pc = pc->insertAfter(pb->coef, b);
                pb=pb->link;               
            }
        }
    }
    while(pa != nullptr){
        pc = pc->insertAfter(pa->coef, pa->exp);
        pa = pa->link; 
    }
    while(pb != nullptr){
        pc = pc->insertAfter(pa->coef, pa->exp);
        pb = pb->link; 
    }
    return C;
}

Polynomial operator* (Polynomial& A, Polynomial& B){

}

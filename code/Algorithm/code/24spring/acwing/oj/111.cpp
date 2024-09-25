#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class A
{
};
class B : public A
{
};
class C : public B
{
};
class D : public C
{
};

class X
{
public:
    void func(A) { cout << "X::func(A)" << endl; };
    void func(B){cout<<"X::func(B)"<<endl;};
    void func(C){cout<<"X::func(C)"<<endl;};
    // void func(D){cout<<"X::func(D)"<<endl;};
};
class Y:public X
{
public:
    void func(A) { cout << "Y::func(A)" << endl; }
};
class Z:public Y
{
public:
};

int main()
{
    X x;
    //x.func(A()); // X::func(A)
    //x.func(D()); // X::func(C) X::func(B) X::func(A),有多个
    // X::func(A)  not X::func(C)。配对的形参类型必须是原来调用时形参的ancestor
    Y y;
    y.func(B());
    Z z;
    z.func(B());
    return 0;
}
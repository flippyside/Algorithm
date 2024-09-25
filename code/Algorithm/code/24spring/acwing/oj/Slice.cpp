#include "Slice.hpp"
#include <iostream>

using namespace std;

int main()
{
    Slice s1(0);
    s1.print();
    s1.append(1);
    s1.print();
    cout << s1.len() << s1.cap() << endl;
}
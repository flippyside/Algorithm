#include "object.h"
#include "class.h"
#include <iostream>

using namespace std;

int main(){
        // 声明类A，并定义成员变量a
    Class A;
    A.add_member_variable("a");
    
    // 声明类B，并普通继承A
    Class B;
    B.add_inherit_class(&A, false);
    // 使用类B实例化一个对象obj_b
    Object obj_b(&B);
    
    bool is_legal = true;
    is_legal = obj_b.set_member_variable("a", nullptr, 1); // 合法的，隐式访问B中的成员变量a，返回true
    cout << is_legal << endl;
    is_legal = obj_b.set_member_variable("a", &A, 2); // 合法的，显式访问B中的成员变量a，返回true
    cout << is_legal << endl;

    is_legal = obj_b.set_member_variable("b", nullptr, 2); // 不合法，返回false
    cout << is_legal << endl;

    
    int result;
    is_legal = obj_b.get_member_variable("a", nullptr, &result); // 合法的，隐式访问B中的成员变量a，返回true，此时result中的值应该变为2
    cout << is_legal << endl;

    is_legal = obj_b.get_member_variable("a", &A, &result); // 合法的，显式访问B中的成员变量a，返回true，此时result中的值仍为2
    cout << is_legal << endl;

    is_legal = obj_b.get_member_variable("b", nullptr, &result); // 不合法，返回false，此时result中的值未定义
    cout << is_legal << endl;

}

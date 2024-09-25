#ifndef CLASS_H
#define CLASS_H
// 你可以根据你的需要增加任何标准库头文件
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#include <map>
// 这个宏用于禁止Class对象和Object对象的复制和赋值操作
// 所以在题目中,两个地址不同的Class对象对应于C++中不同的类
// 两个地址不同的Object对象对应于不同的C++对象
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
TypeName(TypeName&) = delete;              \
void operator=(TypeName) = delete;
using namespace std;

// 假定所有创建的类都只有默认的无参构造函数
// 假定类中只有成员变量，所有成员变量都是int类型，初始化的默认值均为0，不考虑成员函数。
// 假定所有创建的类的成员变量都是public访问权限,不考虑静态成员

class Class {
public:
    vector<pair<const Class*, bool>> parents;// 基类
    map<string, int> member_variables;// 成员变量
    /**
     * 声明无参构造函数(因为禁用了复制操作所以隐式的无参构造函数失效了)
     * 测试样例会使用无参构造函数构造Class对象
     * 你可以添加你自己想要的初始化操作,但是不能修改本函数签名
    */
    Class() {}

    void add_inherit_class(const Class* parent, bool is_virtual){
        parents.push_back(make_pair(parent, is_virtual));
    }

    void add_member_variable(const char* name){
        member_variables.emplace(name, 0);
    }

    DISALLOW_COPY_AND_ASSIGN(Class)
};

#endif // CLASS_H
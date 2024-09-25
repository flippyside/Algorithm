#include "Class.h"
#include <map>

void Class::add_function(const Function &f) {
    funcs.push_back(f);
}

void Class::inherit(const Class &c) {
    parent = &c;
}

int Class::is_ancestor(const Class &ar) const{
    if(this->name == ar.name) return true; 
    Class* cur = const_cast<Class*>(&ar);
    cur = const_cast<Class*>(cur->parent);
    int index = 1;
    while(cur != nullptr){
        if(cur->name == this->name) return index;
        cur = const_cast<Class*>(cur->parent);
        index++;
    }
    return 0;
}
string findMinString(const map<std::string, int>& data) {
    int maxNum = 100; // 初始化最大数字为 int 类型的最小值
    string maxString;

    for (const auto& pair : data) {
        if (pair.second < maxNum) {
            maxNum = pair.second;
            maxString = pair.first;
        }
    }
    return maxString;
}

bool call(CallSite cs) {
    string caller = cs.base.name;// 调用这个函数的对象的类型
    string fn = cs.function_name;
    string ar = cs.arg.name; // 原来函数的形参类型名

    Class* cur = const_cast<Class*>(&cs.base);
    while(cur != nullptr){
        int s= cur->funcs.size();
        for(int i = 0; i < s; i++){
            if(cur->funcs[i].name == fn &&cur->funcs[i].arg.name == ar){
                cout << cur->name <<"::"<< fn <<"(" << ar << ")" << endl;
                return true;
            }
        }
        
        map<string, int> anc;
        for(int i = 0; i < s; i++){
            if(cur->funcs[i].name == fn){
                int index = cur->funcs[i].arg.is_ancestor(cs.arg);
                if(index != 0){ 
                    anc[cur->funcs[i].arg.name] = index;
                }
            }
        }
        if(!anc.empty()){
            string str = findMinString(anc);
            cout << cur->name <<"::"<< fn <<"(" << str << ")" << endl;
            // <静态绑定到的成员函数定义所在类>::<函数名>(<该函数形参的类型>)
            return true;
        }
        cur =  const_cast<Class*>(cur->parent);
    }
    cout << "Function not found." << endl;
}

int main(){
    Class A("A");
    Class B("B");
    B.inherit(A);
    Class C("C");
    C.inherit(B);
    Class D("D");
    D.inherit(C);
    
    Class X("X");
    X.add_function({"func", A});
    X.add_function({"func", B});
    X.add_function({"func", C});
    Class Y("Y");
    Y.add_function({"func", A});
    call({X, "func", A});
    call({X, "func", D});

}
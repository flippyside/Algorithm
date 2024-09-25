#pragma once
#ifndef OBJECT_H
#define OBJECT_H

#include "class.h"
/*
虚继承用于解决多重继承中的“菱形继承”问题。
在菱形继承中，一个类被多个子类继承，这些子类又被另一个类继承，
导致最底层的类拥有多个基类的实例。
虚继承通过确保只有 一个基类实例 来解决这个问题。
*/

class Object {
public:
    map<string, int> member_variables;// 成员变量
    map<const Class*, map<string, int>> parent_class_member_variables; // 对象所属类的基类们对应的成员变量


    explicit Object(const Class* construct_class) {
        // 直接拥有所有成员
        // D
        for (auto it : construct_class->member_variables) {
            member_variables.insert(it);
        }
        const Class* current_class = construct_class;
        vector<const Class*> virtual_base_classes;

        for (pair<const Class*, bool> it : current_class->parents) {
            current_class = it.first;
            bool isVir = it.second;
            while (current_class != nullptr) {
                if (isVir == false) {
                    // 普通继承：直接拥有其所有成员。
                    map<string, int> tmp;
                    for (auto va : current_class->member_variables) {
                        tmp.emplace(va);
                    }
                    parent_class_member_variables.emplace(current_class, tmp);
                }
                else {
                    // 虚继承：用于解决多重继承中的菱形继承问题，通过确保只有 一个 基类实例，避免重复实例。
                    auto result = find(virtual_base_classes.begin(), virtual_base_classes.end(), current_class);
                    if (result != virtual_base_classes.end()) {// 确保只有 一个 基类实例
                        current_class = current_class->parents[0].first;
                        isVir = current_class->parents[0].second; continue;
                    }
                    auto parent_class = it.first;
                    map<string, int> tmp;
                    for (auto va : parent_class->member_variables) {
                        tmp.emplace(va);
                    }
                    parent_class_member_variables.emplace(parent_class, tmp);
                    virtual_base_classes.push_back(parent_class);
                }
                if (current_class->parents.empty()) break;
                current_class = current_class->parents[0].first;
                isVir = current_class->parents[0].second;
            }
        }

    }

    // name: 成员变量名称  qualified_class: 作用域类限定符  result: 把对应成员变量的值传入这个指针
    bool get_member_variable(const char* name, const Class* qualified_class, int* result) {
        if (qualified_class == nullptr) {
            auto find_in_current_class = member_variables.find(name);
            // 在直属类
            if (find_in_current_class != member_variables.end()) {
                result = &find_in_current_class->second;
                return true;
            }
            else { // 往上
                int counter = 0;
                int* re = new int;
                for (auto parent : parent_class_member_variables) {
                    auto current_class = parent.first;
                    auto find_in_current_class = current_class->member_variables.find(name);
                    if (find_in_current_class != member_variables.end()) {// 找到变量
                        if (counter != 0) {
                            return false;// 二义性
                        }
                        counter++;
                        re = const_cast<int*>(&find_in_current_class->second); // 暂存
                    }
                }
                if (counter == 1) {
                    result = re;
                    return true;
                }
                else {
                    return false; // 完全没有
                }
            }
        }
        else {// A::
            auto find_class = parent_class_member_variables.find(qualified_class);
            if (find_class != parent_class_member_variables.end()) {// 找到了类
                auto find_in_current_class = find_class->first->member_variables.find(name);
                if (find_in_current_class != find_class->first->member_variables.end()) {// 找到了变量
                    result = const_cast<int*>(&find_in_current_class->second);
                    return true;
                }
            }
            return false;
        }

    }

    /**
     * 根据传入的成员变量名称，以及名称前面的类限定符，修改这个成员变量的值。
    */

    bool set_member_variable(const char* name, const Class* qualified_class, int value) {
        if (qualified_class == nullptr) {
            auto find_in_current_class = member_variables.find(name);
            // 在直属类
            if (find_in_current_class != member_variables.end()) {
                find_in_current_class->second = value;
                return true;
            }
            else { // 往上
                int counter = 0;
                int* re = new int;
                int* found_value_ptr = nullptr;
                for (auto parent : parent_class_member_variables) {
                    auto current_class = parent.first;
                    auto find_in_current_class = current_class->member_variables.find(name);
                    if (find_in_current_class != member_variables.end()) {// 找到变量
                        if (counter != 0) {
                            return false;// 二义性
                        }
                        counter++;
                        found_value_ptr = const_cast<int*>(&find_in_current_class->second); // 暂存
                    }
                }
                if (counter == 1) {
                    *found_value_ptr = value;
                    return true;
                }
                else {
                    return false; // 完全没有
                }
            }
        }
        else {
            auto find_class = parent_class_member_variables.find(qualified_class);
            if (find_class != parent_class_member_variables.end()) {// 找到了类
                map<string, int>& vals = find_class->second;
                auto tmp = vals.find(name);
                if (tmp != find_class->first->member_variables.end()) {// 找到了变量
                    tmp->second = value;
                    return true;
                }
            }
            return false;
        }
    }

    DISALLOW_COPY_AND_ASSIGN(Object)
};

#endif // OBJECT_H
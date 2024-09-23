#pragma once
#ifndef OBJECT_H
#define OBJECT_H

#include "class.h"
/*
��̳����ڽ�����ؼ̳��еġ����μ̳С����⡣
�����μ̳��У�һ���౻�������̳У���Щ�����ֱ���һ����̳У�
������ײ����ӵ�ж�������ʵ����
��̳�ͨ��ȷ��ֻ�� һ������ʵ�� �����������⡣
*/

class Object {
public:
    map<string, int> member_variables;// ��Ա����
    map<const Class*, map<string, int>> parent_class_member_variables; // ����������Ļ����Ƕ�Ӧ�ĳ�Ա����


    explicit Object(const Class* construct_class) {
        // ֱ��ӵ�����г�Ա
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
                    // ��ͨ�̳У�ֱ��ӵ�������г�Ա��
                    map<string, int> tmp;
                    for (auto va : current_class->member_variables) {
                        tmp.emplace(va);
                    }
                    parent_class_member_variables.emplace(current_class, tmp);
                }
                else {
                    // ��̳У����ڽ�����ؼ̳��е����μ̳����⣬ͨ��ȷ��ֻ�� һ�� ����ʵ���������ظ�ʵ����
                    auto result = find(virtual_base_classes.begin(), virtual_base_classes.end(), current_class);
                    if (result != virtual_base_classes.end()) {// ȷ��ֻ�� һ�� ����ʵ��
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

    // name: ��Ա��������  qualified_class: ���������޶���  result: �Ѷ�Ӧ��Ա������ֵ�������ָ��
    bool get_member_variable(const char* name, const Class* qualified_class, int* result) {
        if (qualified_class == nullptr) {
            auto find_in_current_class = member_variables.find(name);
            // ��ֱ����
            if (find_in_current_class != member_variables.end()) {
                result = &find_in_current_class->second;
                return true;
            }
            else { // ����
                int counter = 0;
                int* re = new int;
                for (auto parent : parent_class_member_variables) {
                    auto current_class = parent.first;
                    auto find_in_current_class = current_class->member_variables.find(name);
                    if (find_in_current_class != member_variables.end()) {// �ҵ�����
                        if (counter != 0) {
                            return false;// ������
                        }
                        counter++;
                        re = const_cast<int*>(&find_in_current_class->second); // �ݴ�
                    }
                }
                if (counter == 1) {
                    result = re;
                    return true;
                }
                else {
                    return false; // ��ȫû��
                }
            }
        }
        else {// A::
            auto find_class = parent_class_member_variables.find(qualified_class);
            if (find_class != parent_class_member_variables.end()) {// �ҵ�����
                auto find_in_current_class = find_class->first->member_variables.find(name);
                if (find_in_current_class != find_class->first->member_variables.end()) {// �ҵ��˱���
                    result = const_cast<int*>(&find_in_current_class->second);
                    return true;
                }
            }
            return false;
        }

    }

    /**
     * ���ݴ���ĳ�Ա�������ƣ��Լ�����ǰ������޶������޸������Ա������ֵ��
    */

    bool set_member_variable(const char* name, const Class* qualified_class, int value) {
        if (qualified_class == nullptr) {
            auto find_in_current_class = member_variables.find(name);
            // ��ֱ����
            if (find_in_current_class != member_variables.end()) {
                find_in_current_class->second = value;
                return true;
            }
            else { // ����
                int counter = 0;
                int* re = new int;
                int* found_value_ptr = nullptr;
                for (auto parent : parent_class_member_variables) {
                    auto current_class = parent.first;
                    auto find_in_current_class = current_class->member_variables.find(name);
                    if (find_in_current_class != member_variables.end()) {// �ҵ�����
                        if (counter != 0) {
                            return false;// ������
                        }
                        counter++;
                        found_value_ptr = const_cast<int*>(&find_in_current_class->second); // �ݴ�
                    }
                }
                if (counter == 1) {
                    *found_value_ptr = value;
                    return true;
                }
                else {
                    return false; // ��ȫû��
                }
            }
        }
        else {
            auto find_class = parent_class_member_variables.find(qualified_class);
            if (find_class != parent_class_member_variables.end()) {// �ҵ�����
                map<string, int>& vals = find_class->second;
                auto tmp = vals.find(name);
                if (tmp != find_class->first->member_variables.end()) {// �ҵ��˱���
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
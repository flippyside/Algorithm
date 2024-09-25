#pragma once
#ifndef CLASS_H
#define CLASS_H
// ����Ը��������Ҫ�����κα�׼��ͷ�ļ�
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#include <map>
// ��������ڽ�ֹClass�����Object����ĸ��ƺ͸�ֵ����
// ��������Ŀ��,������ַ��ͬ��Class�����Ӧ��C++�в�ͬ����
// ������ַ��ͬ��Object�����Ӧ�ڲ�ͬ��C++����
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
TypeName(TypeName&) = delete;              \
void operator=(TypeName) = delete;
using namespace std;

// �ٶ����д������඼ֻ��Ĭ�ϵ��޲ι��캯��
// �ٶ�����ֻ�г�Ա���������г�Ա��������int���ͣ���ʼ����Ĭ��ֵ��Ϊ0�������ǳ�Ա������
// �ٶ����д�������ĳ�Ա��������public����Ȩ��,�����Ǿ�̬��Ա

class Class {
public:
    vector<pair<const Class*, bool>> parents;// ����
    map<string, int> member_variables;// ��Ա����
    /**
     * �����޲ι��캯��(��Ϊ�����˸��Ʋ���������ʽ���޲ι��캯��ʧЧ��)
     * ����������ʹ���޲ι��캯������Class����
     * �����������Լ���Ҫ�ĳ�ʼ������,���ǲ����޸ı�����ǩ��
    */
    Class() {}

    void add_inherit_class(const Class* parent, bool is_virtual) {
        parents.push_back(make_pair(parent, is_virtual));
    }

    void add_member_variable(const char* name) {
        member_variables.emplace(name, 0);
    }

    DISALLOW_COPY_AND_ASSIGN(Class)
};

#endif // CLASS_H
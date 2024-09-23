#include <iostream>
#include <string>
#include <cstring>
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;
const int N = 1e6 + 10;
const int INF = 2147483647;

/*
前序：根左右
中：左根右
后：左右根
给定前序、后序遍历结果，输出可能的中序遍历的总数
6
abc
bdi
cj*
d**
i**
j**
*/

struct T{
    T*le,*ri;
    int e;
};

int main(){
    string pre, post;
    cin>>pre>>post;
}

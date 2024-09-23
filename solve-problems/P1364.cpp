#include <iostream>
#include <string>
#include <cstring>
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;
const int N = 1e6 + 10;
const int INF = 2147483647;

/*
找到使得距离之和最小的源点
点到点的距离
f[i][j]=min(f[i-1][j-1],f[i-1][j]+w[i])
*/

struct T{
    T*le,*ri;
    int e;
};



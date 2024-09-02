#include <iostream>
#include <string>
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;

const int N = 12;

typedef struct 
{
    int top[2];
    int* base;
    int StackSize;
}SStack;


bool Pop(SStack& s, int elem){
    if(s.top[1]+1 = s.top[0]) return false;
    else{
        s.base[++s.top[0]] = elem;
        return true;
    }
}







#include <iostream>
#include <string>
using namespace std;

void expand(string s){
    int idx = 0, len = s.size();
    while(idx < len){
        if(s[idx] == '-'){
            char left = s[idx - 1], right = s[idx + 1];
            if(left - right < 0){
                for(int i = left + 1; i <= right; i++){
                    cout << char(i);
                }
            }
            else if(left - right > 0){
                for(int i = left - 1; i >= right; i--){
                    cout << char(i);
                }
            }else{
                cout << right;
            }
            idx += 2;
        }else{
            cout << s[idx];
            idx++;
        }
    }
}

int main(){
    string s;
    cin>>s;
    expand(s);
}

/*
typedef pair<int, int> pii;
typedef long long ll;
const int N = 1e6 + 10;
int n;
*/

/*
给定一个包含字符 - 的字符串，将其扩展为等价的完整字符串，例如将 a-d 扩展为 abcd，并输出扩展后的字符串，扩展要符合字母表顺序。

当 - 两侧为形如 a-c 的形式时，该运算符会以递增的形式进行扩展，即扩展为 abc。
当 - 两侧为形如 c-a 的形式时，该运算符会以递减的形式进行扩展，即扩展为 cba。
当 - 两侧为形如 a-a 的形式时，直接在原字符串中删除该运算符即，即扩展为 aa。
*/



/*
用例 1
Input

acgb-et
Output

acgbcdet
用例 2
Input

bc-a
Output

bcba
用例 3
Input

a-a
Output

aa
*/
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>

using namespace std;

int main()
{
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            cout << i << "," << j << "\t";
        }
        cout << endl;
    }
}

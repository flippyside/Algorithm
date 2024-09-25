
#include <iostream>
#include <algorithm>
#include<numeric>
#include <string>
#include <vector>
using namespace std;

struct S {
    std::string name;
    int population;
    std::vector<int> temperatures;
};

vector<vector<double>> result;

vector<vector<double>> extract(const vector<S>& data, int index) {
    if (index > data.size() - 1) {
        return result;
    }
    else {
        double sum = double(accumulate(data[index].temperatures.begin(), data[index].temperatures.end(), 0));
        double pop = data[index].population;
        sum /= data[index].temperatures.size();
        result.push_back({ pop, sum });
        extract(data, index + 1);
    }
    return result;
}

int main() {
    S a = { "Nanjing", 120985, {-3, 0, 28, 29, 35, 34, 33, 32} };
    S b = { "Shanghai",  283960, {14, 15, 24, 34, 27, 26, 10, 11, 12} };
    S c = { "Hangzhou",  65536, {15, 17, 18, 25, 3, 31} };
    std::vector<S> data;
    data.push_back(a);
    data.push_back(b);
    data.push_back(c);

    vector<vector<double>> r = extract(data, 0);

    for (int i = 0; i <= 2; i++) {
        for (int j = 0; j < 2; j++) {
            cout << r[i][j] << endl;
        }
    }
}
#include <iostream>
#include <sstream>
#include <cmath>
#include <numeric>
#include <algorithm>
using namespace std;

int main() {

    vector<int> l1, l2, diff;
    string line;
    while (getline(cin, line)) {
        istringstream stream(line);
        int n1, n2;
        stream >> n1 >> n2;
        l1.push_back(n1);
        l2.push_back(n2);
    }

    sort(l1.begin(), l1.end());
    sort(l2.begin(), l2.end());
    transform(l1.begin(), l1.end(), l2.begin(), back_inserter(diff), [](int a, int b) { return abs(a-b); });
    long long tot_diff = accumulate(diff.begin(), diff.end(), 0LL);
    cout << tot_diff << endl;

    return 0;
}

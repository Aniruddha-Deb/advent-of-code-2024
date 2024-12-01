#include <iostream>
#include <sstream>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <set>
using namespace std;

int main() {

    vector<uint64_t> l1, score;
    multiset<int> s2;
    string line;
    while (getline(cin, line)) {
        istringstream stream(line);
        int n1, n2;
        stream >> n1 >> n2;
        l1.push_back(n1);
        s2.insert(n2);
    }

    transform(l1.begin(), l1.end(), back_inserter(score), [&](uint64_t a) { return a*s2.count(a); });
    uint64_t tot_score = accumulate(score.begin(), score.end(), 0LL);
    cout << tot_score << endl;

    return 0;
}

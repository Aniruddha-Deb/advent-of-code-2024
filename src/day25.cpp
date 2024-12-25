#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cassert>

using namespace std;

string ht2str(uint16_t ht) {
    stringstream ss;
    for (int i=4; i>=0; i--) {
        ss << ((ht & (15 << (i*4))) >> i*4);
        if (i != 0) ss << ",";
    }
    return ss.str();
}

int main() {

    vector<string> input;
    string line;
    while (getline(cin, line)) {
        input.push_back(line);
    }

    // int repr because wasn't sure how long input would be 
    // this is simd'd by the compiler
    vector<uint32_t> locks;
    vector<uint32_t> keys;

    for (int i=0; i<input.size(); i++) {
        vector<string> pattern;
        while (i < input.size() and input[i] != "") {
            pattern.push_back(input[i]);
            i++;
        }
        // for (auto p : pattern) {
        //     cout << p << endl;
        // }
        int n = pattern.size();
        int m = pattern[0].size();
        if (pattern[0][0] == '#') {
            // lock
            uint32_t lock = 0;
            for (int j=0; j<m; j++) {
                uint16_t k=0;
                while (k < n and pattern[k][j] == '#') {
                    k++;
                }
                k--;
                lock |= (k << ((m-j-1)*4));
            }
            // cout << ht2str(lock);
            locks.push_back(lock);
        }
        else {
            // key
            uint32_t key = 0;
            for (int j=0; j<m; j++) {
                uint16_t k=0;
                while (k < n and pattern[n-k-1][j] == '#') {
                    k++;
                }
                k--;
                key |= (k << ((m-j-1)*4));
            }
            // cout << ht2str(key);
            keys.push_back(key);
        }
        // cout << endl;
    }

    int ans = 0;
    for (const uint32_t& lock : locks) {
        for (const uint32_t& key : keys) {
            uint32_t sum = lock + key;
            // cout << ht2str(lock) << " " << ht2str(key) << " " << ht2str(sum);
            bool valid = true;
            for (int i=0; i<5; i++) {
                valid = valid and (((sum & (15 << (i*4)))>>(i*4)) <= 5);
            }
            // if (valid) cout << " Y";
            // cout << endl;
            ans += valid;
        }
    }

    cout << ans << endl;

    return 0;
}

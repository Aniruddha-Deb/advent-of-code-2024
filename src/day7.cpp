#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <regex>

using namespace std;

int main() {

    string line;
    vector<pair<uint64_t, vector<uint64_t>>> inputs;
    regex re(R"((\d+): )");
    while (getline(cin, line)) {
        auto pos = line.find(":");
        auto tgt = stoull(line.substr(0,pos));
        auto rest = line.substr(pos+1);
        stringstream ss(rest);
        uint64_t n;
        vector<uint64_t> nums;
        while ((ss >> n)) {
            nums.push_back(n);
        }
        inputs.push_back({tgt, nums});
    }

    uint64_t ans = 0;

    for (auto [tgt, nums] : inputs) {
        int n = nums.size();
        for (int i=0; i<(1<<(n-1)); i++) {
            uint64_t acc = nums[0];
            for (int j=0; j<n-1; j++) {
                if (i & (1 << j)) acc *= nums[j+1];
                else acc += nums[j+1];
            }
            if (acc == tgt) {
                ans += acc;
                break;
            }
        }
    }


    cout << ans << endl;

    return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <regex>
#include <cmath>

using namespace std;

struct num3 {

    vector<int> digits;
    bool ovf;

    num3(int sz): digits(sz, 0), ovf{false} {}

    num3 operator++(int) {
        int carry = 1;
        for (size_t i=0; i<digits.size(); i++) {
            if (digits[i] == 0 and carry == 0) break;
            int sum = digits[i] + carry;
            digits[i] = sum%3;
            carry = sum/3;
        }
        if (carry == 1) ovf = true;
        return *this;
    }

    int operator[](const size_t index) {
        return digits[index];
    }
};

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

        for (num3 i(n-1); !i.ovf; i++) {
            uint64_t acc = nums[0];
            for (int j=0; j<n-1; j++) {
                if (i[j] == 0) acc += nums[j+1];
                else if (i[j] == 1) acc *= nums[j+1];
                else {
                    uint64_t t = nums[j+1];
                    uint64_t p = 1;
                    while (t > 0) {
                        t /= 10;
                        p *= 10;
                    }
                    acc = (acc * p)+nums[j+1];
                }
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


#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <set>

using namespace std;

int main() {

    string layout;
    cin >> layout;

    vector<int> disk;
    bool file = true;
    int id = 0;
    for (char& c : layout) {
        c -= '0';
        for (int i=0; i<c; i++) {
            disk.push_back(file ? id : -1);
        }
        id += file;
        file = !file;
    }

    int n = disk.size();

    vector<set<int>> DP(10, set<int>());
    vector<int> psum;

    exclusive_scan(layout.begin(), layout.end(), back_inserter(psum), 0);

    for (int l=1; l<=9; l++) {
        for (int i=0; i<n-l+1; i++) 
        if (all_of(disk.begin()+i, disk.begin()+i+l, [](const int& a){ return a<0; })) {
            DP[l].insert(i);
        }
    }

    int j = layout.size()-1;
    if (j%2 == 1) j--;
    for (; j>=0; j-=2) {
        int file_size = layout[j];
        int file_loc = psum[j];
        if (DP[file_size].empty()) continue;
        int tgt_loc = *DP[file_size].begin();

        if (tgt_loc >= file_loc) continue;
        for (int i=0; i<file_size; i++) {
            swap(disk[tgt_loc+i], disk[file_loc+i]);
            for (int j=1; j<=9; j++) {
                DP[j].erase(tgt_loc+i);
            }
        }
    }

    uint64_t ans = 0;
    for (int i=0; i<disk.size(); i++) {
        ans += max(disk[i],0)*i;
    }

    cout << ans << endl;

    return 0;
}

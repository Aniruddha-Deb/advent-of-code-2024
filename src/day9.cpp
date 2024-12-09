#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>

using namespace std;

int main() {

    string layout;
    cin >> layout;

    vector<int> disk;
    bool file = true;
    int id = 0;
    for (char c : layout) {
        for (int i=0; i<c-'0'; i++) {
            disk.push_back(file ? id : -1);
        }
        id += file;
        file = !file;
    }

    int free_ptr = 0;
    int n = disk.size();
    int end_ptr = n-1;

    while (free_ptr < end_ptr) {
        while (disk[free_ptr] >= 0) free_ptr++;
        while (disk[end_ptr] < 0) end_ptr--;
        swap(disk[free_ptr], disk[end_ptr]);
    }

    uint64_t ans = 0;
    int mul = 0;
    for (int i=0; i<n; i++) {
        if (disk[i] >= 0) {
            ans += disk[i]*mul;
            mul++;
        }
    }

    cout << ans << endl;

    return 0;
}

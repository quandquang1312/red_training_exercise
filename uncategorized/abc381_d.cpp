#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n; cin >> n;

    vector<int> arr(n);
    for (auto &e : arr) cin >> e;
    
    int ans = 0;
    
    int lst = -1, cur = 0, chain = 0;
    set<int> appear;

    bool donetwo = true;
    for (int i=0; i<n; i++) {
        if (donetwo) {
            if (find(appear.begin(), appear.end(), arr[i]) != appear.end()) {
                ans = max(ans, chain);
                appear.clear();
                chain = 0;
                cur = 1;
            } else {
                lst = arr[i];
                cur = 1;
                donetwo = false;
                appear.insert(lst);
            }
        } else {
            if (arr[i] != lst) {
                ans = max(ans, chain);
                chain = 0;
                lst = arr[i];
                appear.clear();
                appear.insert(lst);
                cur = 1;
            } else {
                cur++;
                if (cur == 2) {
                    chain++;
                    donetwo = true;
                    ans = max(ans, chain);
                }
            }
        }
    }

    cout << ans * 2 << endl;
}
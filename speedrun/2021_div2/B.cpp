// https://codeforces.com/contest/2021/problem/B

#include <bits/stdc++.h>
using namespace std;

#define int long long

void findMex(int n, vector<int>& arr, multiset<int> &redundant, vector<int>& mex) {
    redundant.clear();
    vector<bool> visited(n + 1, false);
    mex.clear();

    int j = 0;
    for (int i=0; i<n; i++) {
        visited[arr[i]] = true;
        if (i && arr[i] == arr[i - 1]) redundant.insert(arr[i]);
    }

    for (int i=0; i<=n; i++) {
        if (visited[i] == false) mex.push_back(i);
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    while (tc--) {
        int n, x; cin >> n >> x;

        vector<int> arr(n);
        for (int i=0; i<n; i++) cin >> arr[i];
        sort(arr.begin(), arr.end());

        multiset<int> redundant;
        vector<int> mex;

        findMex(n, arr, redundant, mex);
        if (arr[0] > mex[0]) {
            cout << mex[0] << "\n";
        } else {
            bool repl = true;
            int i;
            // for (int i=0; i<mex.sze)
            for (i=0; i<mex.size() && repl; i++) {
                int cur_mex = mex[i];
                if (redundant.empty()) {
                    repl = false;
                    break;
                }

                auto iter = redundant.begin();
                while (iter != redundant.end()) {
                    int val = *iter;
                    if (val > mex[i]) break;
                    if ((cur_mex - val) % x == 0) {
                        redundant.erase(iter);
                        break;
                    }
                    iter++;
                }

                if (iter == redundant.end()) {
                    repl = false;
                    break;
                }
            }

            if (!repl && i != mex.size()) {
                cout << mex[i] << "\n";
            } else {
                cout << mex[mex.size() - 1] + 1 << "\n";
            }
        }
    }

    return 0;
}
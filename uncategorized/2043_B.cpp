// https://codeforces.com/contest/2043/problem/B

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    while (tc--) {
        int n, d; cin >> n >> d;

        vector<int> ans = {1};

        // check 3
        if (d % 3 == 0) ans.push_back(3);
        else if (n >= 3) ans.push_back(3);

        // check 5
        if (d == 5) ans.push_back(5);

        // check 7
        if (d == 7) ans.push_back(7);
        else if (n >= 3) ans.push_back(7);

        // check 9
        if (d == 9) ans.push_back(9);
        else {
            if (n >= 6) ans.push_back(9);
            else if (d % 3 == 0 && n >= 3) ans.push_back(9);
        }

        for (auto &e : ans)
            cout << e << " ";
        cout << "\n";

    }

    return 0;
}
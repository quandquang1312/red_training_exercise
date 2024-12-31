// https://codeforces.com/contest/2053/problem/C

#include <bits/stdc++.h>
using namespace std;

#define int long long

vector<int> trace;

int solve(int l, int r, int k) {
    int len = r - l + 1;
    if (len < k) return 0;

    int mid = (r + l) / 2;
    if (len % 2 == 0)
        return solve(l, mid, k) + solve(mid + 1, r, k);
    else {
        // trace.push_back(mid);
        return mid + solve(l, mid - 1, k) + solve(mid + 1, r, k);  
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
        trace.clear();

        int n, k; cin >> n >> k;

        int tmpN = n;
        vector<int> tmp;
        while (tmpN) {
            int ff = tmpN / 2;
            tmp.push_back(ff);
            tmpN /= 2;
        }

        sort(tmp.rbegin(), tmp.rend());

        tmpN = n;
        // for (auto &e : tmp) {
        //     cout << e + 1 << "->" << tmpN / 2 + 1 << "\n";
        //     tmpN /= 2;
        // }

        for (int myK = 1; myK < n; myK++) {
            trace.clear();
            int ans = solve(1, n, myK);

            sort(trace.begin(), trace.end());
            cout << myK << "_ " << ans << ": " << ans / n;
            // for (int i=0; i<trace.size(); i++) {
            //     cout << trace[i] << " ";
            // }
            cout << "\n";
        }

    }

    return 0;
}
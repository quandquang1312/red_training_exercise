// https://codejam.lge.com/problem/25571

#include <bits/stdc++.h>
using namespace std;

#define int long long

int calc(int n, vector<int>& vct) {
    int ans = 0, k = 2;
    bool sign;

    if (n == 2) return (vct[0] != vct[1]);
    for (int i=1; i<n; i++) {
        if (i == 1) {
            sign = (vct[i-1] < vct[i]);
            continue;
        }

        if (sign && vct[i-1] > vct[i]) { k++, sign = !sign; }
        else if (!sign && vct[i-1] < vct[i]) { k++, sign = !sign; }
        else {
            ans += (k * (k - 1)) / 2;
            k = 2;
        }
    }

    ans += (k * (k - 1)) / 2;
    return ans;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<vector<int>> arr;
        vector<int> tmp;
        for (int i=0, u, lst_u; i<n; i++) {
            cin >> u;
            if (i) {
                if (u == lst_u) {
                    if (tmp.size() > 1) arr.push_back(tmp);
                    tmp.clear();
                }
                tmp.push_back(u);
            } else {
                tmp.push_back(u);
            }
            lst_u = u;
        }

        if (tmp.size() > 1) arr.push_back(tmp);

        int ans = 0;
        for (auto &e : arr) {
            // cout << e.size() << "\n";
            ans += calc(e.size(), e);
        }

        cout << ans << '\n';
    }

    return 0;
}
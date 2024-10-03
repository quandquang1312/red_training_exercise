// https://codejam.lge.com/problem/28310

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    while (tc--) {
        int n, m; cin >> n >> m;

        vector<vector<pair<int, int>>> A(n);
        for (int i=0; i<m; i++) {
            int x; cin >> x;
            for (int j=0; j<n; j++) {
                int d; cin >> d;
                if (d != 0) A[j].push_back({d, x});
            }
        }

        vector<pair<int, int>> ans;
        for (int j=0; j<n; j++) {
            auto cat = A[j];
            if (cat.size() == 0) continue;
            int _lcm = cat[0].second; 
            for (int i=1; i<cat.size(); i++) {
                _lcm = lcm(_lcm, cat[i].second);
            }

            int ab = cat[0].first * (_lcm / cat[0].second);
            for (int i=1; i<cat.size(); i++) {
                ab += cat[i].first * (_lcm / cat[i].second);
            }

            ans.push_back({ab, _lcm});
        }

        sort(ans.begin(), ans.end(), [](pair<int, int> p1, pair<int, int> p2) {
            if (p1.second != p2.second) {
                int _lcm = lcm(p1.second, p2.second);
                return (p1.first * (_lcm / p1.second)) < (p2.first * (_lcm / p2.second));
            } else {
                return p1.first < p2.first;
            }
        });

        auto sub = [](pair<int, int> p1, pair<int, int> p2) -> pair<int, int> {
            if (p1.second != p2.second) {
                int _lcm = lcm(p1.second, p2.second);
                int ab = (p1.first * (_lcm / p1.second)) - (p2.first * (_lcm / p2.second));
                return {ab, _lcm};
            } else {
                return {p1.first -  p2.first, p1.second};
            }
        };

        pair<int, int> rs;
        if (ans.size() < n) {
            rs = ans[ans.size()-1];
        } else {
            rs = sub(ans[n-1], ans[0]);
        }

        int f = rs.first / __gcd(rs.first, rs.second);
        int s = rs.second / __gcd(rs.first, rs.second);
        if (s != 1) cout << f << "/" << s << "\n";
        else cout << f << "\n";
    }

    return 0;
}
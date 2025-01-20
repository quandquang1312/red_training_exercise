// https://atcoder.jp/contests/abc374/tasks/abc374_e

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 1e8;

int minComb(int a, int p, int b, int q, int w) {
    int ans = 1e18;
    int LIM = (w / a) + (w % a != 0); // if buy all a's
    for (int i=0; i<=LIM; i++) {
        // i is the number of machine a purchased
        // j will be the number of machine b purchased if purchase i machine a
        int rm = max(0LL, w - (i * a));

        int j   = (rm / b) + (rm % b != 0);
        int cost_a = (i * p);
        int cost_b = (j * q);
        ans = min(ans, cost_a + cost_b);
    }

    return ans;
}

bool solve(int w, int yen, vector<tuple<int, int, int, int>> &process) {
    int rm_yen = yen;
    bool possible = true;
    int n = process.size();
    for (int i=0; i<n && possible; i++) {
        auto [a, p, b, q] = process[i];
        int min_cur = minComb(a, p, b, q, w);
        rm_yen -= min_cur;

        if (rm_yen < 0) possible = false;
        if (rm_yen == 0 && i < n - 1) possible = false; 
    }

    return possible;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n, yen; cin >> n >> yen;
    vector<tuple<int, int, int, int>> process;
    for (int i=0; i<n; i++) {
        int a, p, b, q;
        cin >> a >> p >> b >> q;

        process.push_back({a, p, b, q});
    }

    int l = 0, r = INF;
    while (l < r) {
        int w = (l + r + 1) / 2;
        bool possible = solve(w, yen, process);
        if (possible) l = w;
        else r = w - 1;
    }

    if (l == 1e8) {
        r = 1e9;
        while (l < r) {
            int w = (l + r + 1) / 2;
            bool possible = solve(w, yen, process);
            if (possible) l = w;
            else r = w - 1;
        }
    }

    cout << l << "\n";

    return 0;
}
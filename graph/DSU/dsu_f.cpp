// https://oj.vnoi.info/problem/dsu_f

#include <bits/stdc++.h>
using namespace std;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n, m; cin >> n >> m;
    set<int> st;

    vector<bool> out(n + 1, false);

    vector<pair<int, int>> queries;
    for (int i=0, x; i<m; i++) {
        char c; cin >> c;
        cin >> x;
        queries.push_back({(c == '?'), x});
        if (c == '-') out[x] = true;
    }

    for (int i=1; i<=n; i++) {
        if (!out[i]) st.insert(i);
    }

    vector<int> ans;
    for (int i=m-1; i>=0; i--) {
        auto [t, x] = queries[i];

        if (t == 1) {
            auto it = st.lower_bound(x);
            if (it == st.end()) ans.push_back(-1);
            else ans.push_back(*it);
        } else {
            st.insert(x);
        }
    }

    reverse(ans.begin(), ans.end());

    for (auto &e : ans) {
        cout << e << "\n";
    }

    return 0;
}

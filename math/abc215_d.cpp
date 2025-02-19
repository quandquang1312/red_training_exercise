// https://atcoder.jp/contests/abc215/tasks/abc215_d

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n, m; cin >> n >> m;

    vector<int> arr(n);

    int max_e = m;
    for (int i=0; i<n; i++) {
        cin >> arr[i];
        max_e = max(max_e, arr[i]);
    }

    sort(arr.begin(), arr.end());

    vector<bool> visited(max_e + 1, false);
    vector<bool> ans(m + 1, true);

    for (int i=2; i<=m; i++) {
        if (!visited[i]) {
            bool flag = true;
            for (int j=i; j<=max_e; j+=i) {
                visited[j] = true;
                if (binary_search(arr.begin(), arr.end(), j)) {
                    flag = false;
                    break;
                }
            }

            if (!flag) {
                for (int j=i; j<=m; j+=i) ans[j] = false;
            }
        }
    }

    vector<int> rs;
    for (int i=1; i<=m; i++) {
        if (ans[i]) rs.push_back(i);
    }

    cout << rs.size() << "\n";
    for (const auto &e : rs) cout << e << "\n";

    return 0;
}
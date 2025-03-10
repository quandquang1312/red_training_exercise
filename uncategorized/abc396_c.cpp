// https://atcoder.jp/contests/abc396/tasks/abc396_c

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 1e18;

int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n, m; cin >> n >> m;

    vector<int> B(n), W(m);
    for (int i=0; i<n; i++) cin >> B[i];
    for (int i=0; i<m; i++) cin >> W[i];
    
    sort(B.begin(), B.end(), greater<int>());
    sort(W.begin(), W.end(), greater<int>());

    vector<int> prefix_B(n + 1, 0), prefix_W(m + 1, 0);
    vector<int> max_B(n + 2, -INF);
    for (int i=0; i<n; i++) {
        prefix_B[i + 1] += prefix_B[i] + B[i];
    }

    for (int i=n; i>=1; i--) {
        max_B[i] = max(max_B[i + 1], prefix_B[i]);
    }

    for (int i=0; i<m; i++) {
        prefix_W[i + 1] += prefix_W[i] + W[i];
    }

    int ans = 0;
    for (int i=0; i<=m; i++) {
        if (i == 0) {
            ans = max(ans, max_B[i + 1]);
            continue;
        }

        if (W[i - 1] < 0) break;
        if (i > n) break;
        ans = max(ans, prefix_W[i] + max_B[i]);
    }

    cout << ans << "\n";

    return 0;
}
// https://cses.fi/problemset/task/1084

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

    int n, m, k;
    cin >> n >> m >> k;

    vector<int> a(n), b(m);
    for (int i=0; i<n; i++) cin >> a[i];
    for (int i=0; i<m; i++) cin >> b[i];

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    // j - index of apartments available
    int ans = 0, j = 0;

    // loop for needs
    for (int i=0; i<m; i++) {
        int pos = lower_bound(a.begin() + j, a.end(), b[i] - k) - a.begin();
        if (pos == n) break;
        if (a[pos] > b[i] + k) continue;
        
        // right the 'pos' apartment for people 'i'
        j = pos + 1;
        ans++; 
    }

    cout << ans << "\n";

    return 0;
}
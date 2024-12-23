// https://codeforces.com/problemset/problem/1419/B

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

    int sm = 0, meet = (1 << 1); 
    const int LIMIT = 1e18;

    vector<int> cell_needs;
    int quant = 0;
    for (int i = 1; i <= 30; i++) {
        int value = (1 << i) - 1;
        quant = (value * (value + 1)) / 2;
        cell_needs.push_back(quant);
    }

    vector<int> presum(cell_needs.size() + 1, 0);
    for (int i=0; i<cell_needs.size(); i++) presum[i + 1] = presum[i] + cell_needs[i];

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        int ans = 0, idx = 0;
        ans = lower_bound(presum.begin(), presum.end(), n) - presum.begin();
        if (presum[ans] != n) ans--;

        cout << ans << "\n";
    }

    return 0;
}
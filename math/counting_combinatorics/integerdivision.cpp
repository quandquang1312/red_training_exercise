// https://open.kattis.com/problems/integerdivision

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

    int n, d; cin >> n >> d;

    unordered_map<int, int> cnt;
    for (int i=0; i<n; i++) {
        int x; cin >> x;
        cnt[x/d]++;
    }

    int ans = 0;
    for (auto &[k, v] : cnt) {
        ans += (v * (v-1))/2;
    }

    cout << ans << endl;

    return 0;
}
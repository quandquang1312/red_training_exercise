// https://atcoder.jp/contests/abc374/tasks/abc374_c

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 1e9;

int total, ans;

void solve(int idx, int sm, vector<int>& arr) {
    if (idx >= arr.size()) {
        ans = min(ans, max(sm, total - sm));
        return;
    }

    int cur = sm + arr[idx];

    solve(idx + 1, cur, arr);
    solve(idx + 1, sm, arr);
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n; cin >> n;

    total = 0;
    ans = INF;

    vector<int> arr(n);

    for (int i=0; i<n; i++) {
        cin >> arr[i];
        total += arr[i];
    }

    solve(0, 0, arr);

    cout << ans << endl;

    return 0;
}
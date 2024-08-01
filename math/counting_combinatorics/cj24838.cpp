// https://codejam.lge.com/problem/24838

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 60100
const int MOD = 1e9 + 7;

vector<int> diff;

void update(vector<int>& diff, int l, int r, int vl) {
    diff[l] += vl;
    diff[r] -= vl;
}

void apply_update(vector<int>& diff, int n)
{
    for (int i=1; i<=n; i++) diff[i] += diff[i-1];
}

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
        int arr[n];
        diff.assign(n+5, 0);
        for (int i=0; i<n; i++) cin >> arr[i];
        sort(arr, arr+n);

        for (int i=0; i<m; i++) {
            int l, r; cin >> l >> r;
            update(diff, l, r + 1, 1);
        }

        apply_update(diff, n);

        map<int, int> cnt;

        int ub = -1;
        for (int i=1; i<=n; i++) {
            cnt[diff[i]]++;
            ub = max(ub, cnt[diff[i]]);
            // cout << i << " " << diff[i] << '\n';
        }

        vector<int> fact(ub+5, 1);
        for (int i=1; i<=ub; i++) {
            fact[i] = (fact[i-1] * i) % MOD;
        }

        int ans = 1, sm = 0, idx = 0;
        auto sm_range = []() {
            
        };
        for (auto &[k, v] : cnt) {
            ans *= fact[v];
        }

        cout << sm << " " << ans << endl;
    }

    return 0;
}
// https://open.kattis.com/problems/orders

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX_N 110
#define MAX_S 30050

int dp[MAX_S][MAX_N], cnt[MAX_N];

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n; cin >> n;
    vector<int> arr(n);
    for (int i=0; i<n; i++) cin >> arr[i];

    int q, up = 0; cin >> q;
    vector<int> qu(q);
    for (int i=0; i<q; i++) {
        cin >> qu[i];
        up = max(up, qu[i]);
    }

    dp[0][0] = 1;
    for (int i=0; i<=up; i++) {
        for (int j=1; j<=n; j++) {
            int p = arr[j - 1];

            dp[i][j] = dp[i][j - 1];
            if (i - p >= 0) {
                dp[i][j] += dp[i - p][j];
            }
        }
    }


    for (int i=0; i<q; i++) {
        int res = dp[qu[i]][n];
        if (res == 0) cout << "Impossible\n";
        else if (res >= 2) cout << "Ambiguous\n";
        else {
            int sm = qu[i], j = n;

            // trace solution knapsack ways
            while (sm > 0 && j > 0) {
                if (dp[sm][j] != dp[sm][j - 1]) {
                    cnt[j - 1]++;
                    sm -= arr[j - 1];
                } else {
                    j--;
                }
            }

            for (int k=0; k<n; k++) {
                while (cnt[k] > 0) {
                    cout << k + 1 << ' ';
                    cnt[k]--;
                }
            }

            cout << '\n';
        }
    }

    return 0;
}

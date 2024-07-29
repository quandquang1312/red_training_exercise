// https://atcoder.jp/contests/abc362/tasks/abc362_e

#include <bits/stdc++.h>
using namespace std;

#define MAXN 5000
const int MOD = 998244353;
int dp[85][85][MAXN];

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n; cin >> n;
    vector<int> arr(n+1), ans(n+1, 0);
    for (int i=0; i<n; i++) cin >> arr[i];

    vector<int> points;
    for (int i=0; i<n; i++) {
        for (int j=i+1; j<n; j++) {
            points.push_back(arr[j] - arr[i]);
        }
    }

    unordered_map<int, int> idx;
    sort(points.begin(), points.end());
    points.erase(unique(points.begin(), points.end()), points.end());
    int sz = points.size();
    for (int i=0; i<sz; i++) idx[points[i]] = i;

    /* dp[i][j][k]:
        i: index
        j: length of the arith seq
        k: common difference
    */

    for (int i=0; i<n; i++) {
        for (int j=0; j<=sz; j++)
            dp[i][1][j] = 1;
    }

    for (int i=0; i<n; i++) {
        for (int j=0; j<i; j++) {
            int d = idx[arr[i] - arr[j]];
            for (int l=2; l<=n; l++) {
                dp[i][l][d] += dp[j][l-1][d];
                dp[i][l][d] %= MOD;
            }
        }
    }

    for (int k=0; k<n; k++) {
        for (int i=1; i<=n; i++) {
            for (int j=0; j<=sz; j++) {
                ans[i] += dp[k][i][j];
                ans[i] %= MOD;
            }
        }
    }

    for (int i=1; i<=n; i++) {
        if (i == 1) cout << n << " ";
        else cout << ans[i] << " ";
    } cout << endl;

    return 0;
}
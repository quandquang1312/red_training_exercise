// http://lgedvoj.lge.com/problem/graexhlite

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    int n, m;
    cin >> n >> m;

    int adj[10][10] {};

    int vi, ai, bi;
    for (int i=0; i<m; i++) {
        cin >> vi >> ai >> bi;
        adj[ai][bi] += vi;
    }

    vector<int> order(n);

    for (int i=0; i<n; i++) order[i] = i+1;

    int res = -1, cnt = 0;
    do {
        int ans = 0;
        for (int i=0; i<n-1; i++) {
            for (int j=i+1; j<n; j++) {
                ans += adj[order[i]][order[j]];
            }
        }
        if (ans > res) {
            res = ans;
            cnt = 1;
        } else if (ans == res) {
            cnt++;
        }
    } while (next_permutation(order.begin(), order.end()));

    cout << res << " " << cnt << endl;

    return 0;
}
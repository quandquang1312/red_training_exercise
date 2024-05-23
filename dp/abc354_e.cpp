// https://atcoder.jp/contests/abc354/tasks/abc354_e

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

    int n; cin >> n;
    vector<pair<int, int>> arr(n);

    for (int i=0; i<n; i++) {
        cin >> arr[i].first >> arr[i].second;
    }

    int dp[1 << n];
    memset(dp, -1, sizeof dp);

    dp[0] = 0; // If there's no pair left, it's a losing state

    for (int mask=1; mask < (1 << n); mask++) {
        bool f = false;

        for (int i=0; i<n-1; i++) {
            for (int j=i+1; j<n; j++) {

                // if pair i,j has not been choosen
                if ((mask & (1 << i)) && (mask & (1 << j))) {
                    if (arr[i].first == arr[j].first || arr[i].second == arr[j].second) {
                        
                        // if choosing the pair i,j (S / {i,j}) leads to a losing state, then
                        //  (S) is a winning state
                        if (dp[mask ^ (1 << i) ^ (1 << j)] == 0)
                            f = true;
                    }
                }
            }
        }

        dp[mask] = f;
    }

    // Takahashi go first, if S{1,2,3...,n} can lead to a losing state,
    // than Takahashi will win

    if (dp[(1 << n) - 1]) printf("Takahashi\n");
    else printf("Aoki\n");

    return 0;
}
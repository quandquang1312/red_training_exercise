// https://codeforces.com/contest/607/problem/B

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

    int n; cin >> n;
    vector<int> arr(n);
    for (int i=0; i<n; i++) cin >> arr[i];

    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    vector<vector<int>> palindrome(n + 1);

    for (int i=0; i<n; i++) {
        palindrome[i].push_back(i);
        dp[i][i] = 1;
        if (i + 1 < n && arr[i] == arr[i+1]) {
            dp[i][i+1] = 1; 
            palindrome[i].push_back(i+1);
        }
    }

    for (int len=2; len<n; len++) {
        for (int i=0; i<(n-len); i++) {
            int j = i + len;

            if (arr[i] == arr[j] && dp[i+1][j-1]) {
                dp[i][j] = 1;
                palindrome[i].push_back(j);
            }
        }
    }



    return 0;
}
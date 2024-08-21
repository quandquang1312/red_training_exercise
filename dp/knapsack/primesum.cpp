// https://vjudge.net/problem/HackerRank-euler077

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX_N 1050

vector<int> linear_sieve()
{
    vector<int> primes;
    bool is_composite[MAX_N] {};

    for (int i=2; i<MAX_N; i++) {
        if (!is_composite[i]) primes.push_back(i);
        for (int j=0; j<primes.size() && i * primes[j] < MAX_N; j++) {
            is_composite[i * primes[j]] = true;
            if (i % primes[j] == 0) break;
        }
    }

    return primes;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int tc, n;
    cin >> tc;

    vector<int> primes = linear_sieve();
    int m = primes.size();

    while (tc--) {
        cin >> n;

        vector<vector<int>> dp(MAX_N, vector<int>(m + 10, 0));

        dp[0][0] = 1;
        for (int j=1; j<=m; j++) {
            int p = primes[j - 1];
            for (int i=0; i<=n; i++) {
                dp[i][j] = dp[i][j-1];
                if (i - p >= 0) dp[i][j] += dp[i-p][j];
            }
        }

        cout << dp[n][m] << '\n';
    }

    return 0;
}
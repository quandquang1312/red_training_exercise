// https://vjudge.net/problem/UVA-1213

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX_N 1150
#define MAX_PRIMES 210
#define MAX_K 17

vector<int> primes;
// int dp[MAX_PRIMES][MAX_K][MAX_N];
int dp[MAX_N][MAX_K];

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

// int solve(int idx, int rm_k, int sm, int n) {
//     if (sm > n || rm_k < 0 || idx >= primes.size()) return 0;
//     if (rm_k == 0) return sm == n;

//     if (dp[idx][rm_k][sm] != -1) return dp[idx][rm_k][sm];

//     int ans = 0;

//     ans += solve(idx + 1, rm_k - 1, sm + primes[idx], n);
//     ans += solve(idx + 1, rm_k, sm, n);

//     return dp[idx][rm_k][sm] = ans;
// }

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int n, k;

    primes = linear_sieve();

    dp[0][0] = 1;
    for (int j=0; j<primes.size(); j++) {
        for (int i=1130; i>=0; i--) {
            for (int rm_k = 14; rm_k >= 0; rm_k--) {
                if (i - primes[j] >= 0) dp[i][rm_k] += dp[i-primes[j]][rm_k-1];
            }
        }
    }

    while (cin >> n >> k) {
        if (n == 0 && k == 0) break;
        cout << dp[n][k] << '\n';
    }

    return 0;
}
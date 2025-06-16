// https://vjudge.net/problem/Kattis-busplanning

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 1e18;

void printBin(int n, int bin) {
    for (int i=0; i<n; i++) {
        if (bin & (1 << i)) cout << "1";
        else cout << "0";
    }
    cout << ": ";
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    
    int n, m, c; cin >> n >> m >> c;

    map<string, int> str_idx;
    vector<string> name(n);

    for (int i=0; i<n; i++) {
        cin >> name[i];
        str_idx[name[i]] = i;
    }

    // create enemy bitmask
    vector<int> enemy(n);

    for (int i=0; i<m; i++) {
        string a, b; cin >> a >> b;
        int a_idx = str_idx[a], b_idx = str_idx[b];
        enemy[a_idx] |= (1 << b_idx);
        enemy[b_idx] |= (1 << a_idx);
    }

    // precompute valid subsets
    vector<bool> isValid(1 << n, true);
    for (int mask=1; mask<=((1 << n) - 1); mask++) {
        if (__builtin_popcount(mask) > c) isValid[mask] = false;
        for (int a=0; a<n; a++) {
            if (!(mask & (1 << a))) continue;
            for (int b=a+1; b<n; b++) {
                if (!(mask & (1 << b))) continue;
                if (enemy[a] & (1 << b)) isValid[mask] = false;
            }
        }
    }

    // DEBUG
    // for (int mask=1; mask<=(1<<n) - 1; mask++) {
    //     printBin(n, mask);
    //     cout << isValid[mask] << "\n";
    // }

    vector<int> dp(1 << n, INF);
    vector<int> trace(1 << n, 0);
    dp[0] = 0;

    // dp[mask] : the minimum number of valid subsets (in isValid) to cover all bits in mask
    for (int mask=0; mask<=(1 << n) - 1; mask++) {
        // itervate over all subsets of 'mask'
        for (int sub=mask; sub; sub=((sub - 1) & mask)) {
            if (!isValid[sub]) continue;
            int prev = mask ^ sub;
            if (dp[mask] > dp[prev] + 1) {
                dp[mask] = dp[prev] + 1;
                trace[mask] = sub;
            }
        }
    }

    int rs_mask = (1 << n) - 1;

    cout << dp[rs_mask] << "\n";

    while (rs_mask) {
        int g = trace[rs_mask];
        for (int i=0; i<n; i++) {
            if (g & (1 << i)) cout << name[i] << " ";
        }
        cout << "\n";
        rs_mask ^= g;
    }

    return 0;
}
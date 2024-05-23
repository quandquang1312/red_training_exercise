#include <bits/stdc++.h>
using namespace std;

#define int long long

vector<pair<int, int>> posibilities;
bool takahashi;
int dp[2][1 << 19];

bool possible_move(int mask)
{
    for (auto &e : posibilities) {
        if ((mask & (1 << e.first)) && (mask & (1 << e.second)))
            return true;
    }

    return false;
}

int solve(bool turn, int mask)
{
    if (dp[turn][mask] != -1) return dp[turn][mask];

    if (__builtin_popcount(mask) == 1) {
        if (turn == true) return dp[turn][mask] = takahashi = true;
        else return dp[turn][mask] = false;
    }

    if (!possible_move(mask))
    {
        if (turn == true) return dp[turn][mask] = takahashi = true;
        else return dp[turn][mask] = false;
    }

    for (auto &e : posibilities) {
        if ((mask & (1 << e.first)) && (mask & (1 << e.second))) {
            int new_mask = mask ^ (1 << e.first);
            new_mask = new_mask ^ (1 << e.second);

            dp[turn][mask] |= solve(!turn, new_mask);
        }
    }

    return dp[turn][mask];
}

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

    for (int i=0; i<n-1; i++) {
        for (int j=i+1; j<n; j++) {
            if (i == j) continue;
            if (arr[i].first == arr[j].first || arr[i].second == arr[j].second) {
                posibilities.push_back({i, j});
            }
        }
    }

    memset(dp, -1, sizeof dp);

    int init_mask = (1 << n) - 1;
    takahashi = false;

    for (int i=0; i<posibilities.size(); i++) {
        int new_mask = init_mask;
        new_mask = new_mask ^ (1 << posibilities[i].first);
        new_mask = new_mask ^ (1 << posibilities[i].second);

        solve(true, new_mask);
    }

    if (takahashi) printf("Takahashi\n");
    else printf("Aoki\n");

    return 0;
}
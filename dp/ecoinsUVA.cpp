// https://vjudge.net/problem/UVA-10306

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define INF 1e12
int m, s;
vector<pair<int, int>> ecoins;
int dp[45][30][30];

int solve(int idx, int conven, int infor, int cnt)
{
    if (idx >= m) {
        if ((conven * conven + infor * infor) != (s * s)) return INF;
        return cnt;
    }

    if ((conven * conven + infor * infor) > (s * s)) return INF;

    if (dp[idx][conven][infor] != -1) {
        if (cnt > dp[idx][conven][infor])
            return dp[idx][conven][infor];
    }

    int skip = solve(idx+1, conven, infor, cnt);
    int use  = solve(idx, conven + ecoins[idx].first, infor + ecoins[idx].second, cnt+1);
    return dp[idx][conven][infor] = min(skip, use);
}

int32_t main() {

    int tc; cin >> tc;
    while (tc--)
    {
        cin >> m >> s;
        ecoins.resize(m);

        memset(dp, -1, sizeof dp);

        for (auto &e : ecoins) cin >> e.first >> e.second;

        int ans = solve(0, 0, 0, 0);

        cout << (ans == INF ? "not possible" : to_string(ans)) << endl;
    }

    return 0;
}
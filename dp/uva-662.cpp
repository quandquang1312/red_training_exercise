// https://vjudge.net/problem/UVA-662

#include <bits/stdc++.h>
using namespace std;

#define int long long

int n, k, arr[202], res = 1e9, dp[202][40];
vector<int> vt;

int solve(int idx, int rm, vector<int> depot)
{
    if (idx == n) {
        if (depot.size() > k) return 1e9;

        int ans = 0;
        for (int i=0; i<n; i++) {
            int mmin = 1e9;
            for (int j=0; j<depot.size(); j++) {
                mmin = min(mmin, abs(arr[i] - arr[depot[j]]));
            }
            ans += mmin;
        }

        if (ans < res) {
            res = ans;
            vt = depot;
        }

        return dp[idx][rm] = ans;
    }

    if (rm < 0) return 1e9;

    // if (dp[idx][rm] != -1) return dp[idx][rm];

    depot.push_back(idx);
    int placed = solve(idx + 1, rm - 1, depot);
    depot.pop_back();
    int nplaced = solve(idx + 1, rm, depot);

    dp[idx][rm] = min(placed, nplaced); 
    return dp[idx][rm];
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("ou.txt", "w", stdout);
    #endif

    n = 1, k = 1; int chain = 1;
    while((cin >> n >> k), n && k) {
        memset(dp, -1, sizeof(dp));

        for (int i=0; i<n; i++) cin >> arr[i];

        vector<int> depot;
        cout << "Chain " << chain << endl;

        int tol = solve(0, k, depot);

        vector<vector<int>> trace(k+1, vector<int>());
        for (int i=0; i<n; i++) {
            int mmin = 1e9, hh = -1;
            for (int j=0; j<vt.size(); j++) {
                if (mmin > abs(arr[i] - arr[vt[j]])) {
                    mmin = abs(arr[i] - arr[vt[j]]);
                    hh = j;
                }
            }
            trace[hh].push_back(i);
        }

        for (int i=0; i<k; i++) {
            if (trace[i].size() == 0) {
                continue;
            } else if (trace[i].size() == 1) {
                printf("Depot %lld at restaurant %lld serves restaurant %lld\n", i+1, vt[i]+1, trace[i][0]+1);
            } else {
                printf("Depot %lld at restaurant %lld serves restaurants %lld to %lld\n", i+1, vt[i], trace[i][0]+1, trace[i][trace[i].size()-1]+1);
            }
        }

        printf("Total distance sum = %lld\n", tol);

        chain++;
    }

    return 0;
}
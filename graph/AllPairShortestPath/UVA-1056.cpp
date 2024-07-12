// https://vjudge.net/problem/UVA-1056

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

    int n, m, tc = 1;
    while (cin >> n >> m)
    {
        if (n + m == 0) break;

        unordered_map<string, int> idx;

        vector<vector<int>> mtr(n, vector<int>(n, 1e9));
        int cnt = 0;
        for (int i=0; i<m; i++) {
            string n1, n2;
            cin >> n1 >> n2;
            if (idx.find(n1) == idx.end()) idx[n1] = cnt++;
            if (idx.find(n2) == idx.end()) idx[n2] = cnt++;
            mtr[idx[n1]][idx[n2]] = 1;
            mtr[idx[n2]][idx[n1]] = 1;
        }

        for (int i=0; i<n; i++) mtr[i][i] = 0;

        for (int k=0; k<n; k++) {
            for (int i=0; i<n; i++) {
                for (int j=0; j<n; j++) {
                    if (mtr[i][k] != 1e9 && mtr[k][j] != 1e9)
                        mtr[i][j] = min(mtr[i][j], mtr[i][k] + mtr[k][j]);
                }
            }
        }

        // for (auto &[name, i] : idx) {
        //     cout << name << ": " << i << endl;
        // }

        // for (int i=0; i<n; i++) {
        //     for (int j=0; j<n; j++) {
        //         cout << mtr[i][j] << " ";
        //     }
        //     cout << endl;
        // }

        bool disconnect = false;
        int ans = -1; 
        for (int u=0; u<n; u++) {
            for (int v=0; v<n; v++) {
                if (u == v) continue;
                ans = max(ans, mtr[u][v]);
                disconnect |= (mtr[u][v] == 1e9);
            }
        }

        cout << "Network " << tc++ << ": ";
        cout << (disconnect == false ? to_string(ans) : "DISCONNECTED") << endl;
        cout << "\n";
    }

    return 0;
}
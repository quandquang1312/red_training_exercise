// https://community.topcoder.com/stat?c=problem_statement&pm=10187

#include <bits/stdc++.h>
using namespace std;

#define int long long
vector<vector<int>> adj;
vector<bool> visited;
vector<int> RightMatch, LeftMatch;

bool check(int p1, int p2) {
    int p = p1 + p2;
    if (p == 2 || p == 3 || p == 5) return true;
    if (p == 1 || p % 3 == 0 || p % 5 == 0) return false;
    for (int i=4; i*2<=p; i++)
        if (p % i == 0) return false;
    return true;
}

bool kuhn(int u) {
    if (visited[u]) return 0;
    visited[u] = true;

    for (auto &v : adj[u]) {
        if (RightMatch[v] == -1 || kuhn(RightMatch[v])) {
            RightMatch[v] = u;
            return true;
        }
    }

    return false;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        adj.assign(n, vector<int>());
        RightMatch.resize(n, -1);
        LeftMatch.resize(n, -1);

        int arr[n];
        for (int i=0; i<n; i++) cin >> arr[i];

        for (int i=0; i<n; i++) {
            for (int j=i+1; j<n; j++) {
                if (check(arr[i], arr[j])) {
                    adj[i].push_back(j);
                    if (i != 0) adj[j].push_back(i);
                }
            }
        }

        // for (int i=0; i<n; i++) {
        //     cout << arr[i] << ": ";
        //     for (auto &e : adj[i]) {
        //         cout << arr[e] << " ";
        //     } cout << endl;
        // }

        vector<int> ans;
        for (int i=0; i<adj[0].size(); i++) {
            int v = adj[0][i];

            while (true) {
                 bool foundMatch = false;
                visited.resize(n, false);
                RightMatch.resize(n, -1);

                visited[v] = true;
                visited[0] = true;
                RightMatch[v] = 0;
                RightMatch[0] = v;

                for (int j=1; j<n; j++) {
                    if (v == j) continue;
                    if (RightMatch[j] != -1) continue;
                    cout << arr[i] << ": " << arr[j] << endl;
                    if (kuhn(j)) {
                        foundMatch = true;
                        ans.push_back(v);
                    }
                }

                if (!foundMatch) break;
            }
        }

        cout << ans.size() << endl;
        for (auto &e : ans) cout << arr[e] << " ";
        cout << endl;
    }

    return 0;
}
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

    int tc; cin >> tc;
    while (tc--) {
        int n, m, l;
        cin >> n >> m >> l;

        vector<pair<int, int>> hurdle(n);
        for (int i=0; i<n; i++) {
            cin >> hurdle[i].first >> hurdle[i].second;
        }

        sort(hurdle.begin(), hurdle.end());

        vector<pair<int, int>> energy(m);
        for (int i=0; i<m; i++) {
            cin >> energy[i].first >> energy[i].second;
        }

        sort(energy.begin(), energy.end());

        priority_queue<int> q;
        int cur_power = 0, ans = 0, j = 0;
        for (int i=0; i<n; i++) {
            for (; j < m && energy[j].first < hurdle[i].first; j++) {
                q.push(energy[j].second);
            }
            while (!q.empty() && cur_power < (hurdle[i].second - hurdle[i].first + 1)) {
                cur_power += q.top();
                ans++;
                q.pop();
            }

            if (cur_power < (hurdle[i].second - hurdle[i].first + 1)) {
                ans = -1;
                break;
            }
        }

        cout << ans << "\n";
    }

    return 0;
}
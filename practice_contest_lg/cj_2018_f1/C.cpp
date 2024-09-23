// https://codejam.lge.com/problem/16207

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

    vector<int> stick(n);
    map<int, int> mp;
    vector<pair<int, int>> freq;
    for (int i=0; i<n; i++) {
        cin >> stick[i];
        mp[stick[i]]++;
    }

    for (auto &[e, f] : mp) {
        freq.push_back({e, f});
    }

    sort(freq.begin(), freq.end(), greater<>());
    for (int i=0; i<freq.size(); i++) {
        auto &[e, f] = freq[i];
        if (f % 2) {
            if (i < freq.size() - 1 && freq[i + 1].first == e - 1) {
                freq[i + 1].second += 1;
            }
            f -= 1;
        }
    }

    vector<pair<int, int>> pq;

    for (auto &[cur, f] : freq) {
        if (f < 2) continue;
        pq.push_back({cur, f / 2});
    }

    int ans = 0, prev = -1;
    for (int i=0; i<pq.size(); i++) {
        auto [cur, f] = pq[i];

        if (prev != -1) {
            f -= 1;
            ans += (prev * cur);
        }

        int p = f / 2;
        ans += p * (cur * cur);

        if (f % 2 == 0) prev = -1;
        else prev = cur;
    }

    cout << ans << "\n";

    return 0;
}
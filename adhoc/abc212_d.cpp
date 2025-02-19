// https://atcoder.jp/contests/abc212/tasks/abc212_d

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int q; cin >> q;

    vector<int> prefix {0};

    auto comp = [&] (const pair<int, int> &p1, const pair<int, int> &p2) {
        int sz = prefix.size();
        int val1 = p1.first + (prefix[sz - 1] - prefix[p1.second]);
        int val2 = p2.first + (prefix[sz - 1] - prefix[p2.second]);

        return val1 > val2;
    };

    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(comp)> pq(comp);
    while (q--) {
        int tp; cin >> tp;
        if (tp == 1) {
            int x; cin >> x;
            pq.push({x, prefix.size() - 1});
        } else if (tp == 2) {
            int x; cin >> x;
            prefix.push_back(x);
            int sz = prefix.size();
            prefix[sz - 1] += prefix[sz - 2];
        } else {
            auto [u, p] = pq.top(); pq.pop();
            int sz = prefix.size();
            cout << u + (prefix[sz - 1] - prefix[p]) << "\n";
        }
    }

    return 0;
}
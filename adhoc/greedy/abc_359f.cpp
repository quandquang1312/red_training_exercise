// https://atcoder.jp/contests/abc359/tasks/abc359_f

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n; cin >> n;

    // cur: d^2 * ai
    // add 1: (d + 1) ^ 2 * ai
    // margin cost: ((d + 1) ^ 2 - d^2) * ai = (d^2 * 2d + 1 - d^2) * ai
    // = (2d + 1) * ai
    // that means if we want to add 1 more add to vertex i, the cost is (2 * d + 1) * ai

    priority_queue<tuple<int, int, int>> pq;
    for (int i=0, x; i<n; i++) {
        cin >> x;
        int margin_cost = (2 * 1 + 1) * x;
        pq.push({-margin_cost, 1, x});
    }

    int k = (n - 1) * 2 - n;
    while (k > 0) {
        auto [_, degree, ai] = pq.top(); pq.pop();
        degree++;

        int margin_cost = (2 * degree + 1) * ai;

        pq.push({-margin_cost, degree, ai});

        k--;
    }

    int ans = 0;
    while (!pq.empty()) {
        auto [_, degree, ai] = pq.top(); pq.pop();
        ans += (degree * degree * ai);
    }

    cout << ans << "\n";

    return 0;
}

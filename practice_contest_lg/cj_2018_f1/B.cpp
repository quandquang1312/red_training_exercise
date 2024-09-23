// https://codejam.lge.com/problem/16206

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

    int n, m;
    cin >> n >> m;

    int ans = 0;
    auto comp = [](int a, int b) {
        return a < b;
        if (a % 10 == 0 && b % 10 == 0) {
            if (a < b) return a < b;
            else return a < b;
        }

        if (a % 10 == 0) {
            return a > b;
        }

        if (b % 10 == 0) {
            return b > a;
        }

        return a > b;
    };

    priority_queue<int, vector<int>, decltype(comp)> pq(comp);

    vector<int> dv10;
    for (int i=0, x; i<n; i++) {
        cin >> x;
        if (x == 10) ans++;
        else if (x % 10 == 0) dv10.push_back(x);
        else if (x > 10) pq.push(x);
    }

    sort(dv10.begin(), dv10.end());

    for (auto &e : dv10) {
        if ((e / 10 - 1) <= m) {
            ans += e / 10;
            m -= (e / 10) - 1;
        } else {
            ans += m;
            m -= m;
        }

        // cout << e << " : " << ans << endl;
        // cout << "m: " << m << endl;
    }

    int cnt = 0;
    while (!pq.empty() && cnt < m) {
        int c = pq.top();
        pq.pop();
        if (c < 10) continue;
        else {
            int x = c - 10;
            ans++;
            if (x == 10) ans++;
            else pq.push(x);

            cnt++;
        }
    }

    cout << ans << endl;

    return 0;
}
// https://www.hackerrank.com/contests/dn-swpct-2024-batch-3/challenges/candy-fair

#include <bits/stdc++.h>
using namespace std;

#define int long long

bool check(int val, int n, vector<int>& arr) {
    priority_queue<int> q;

    for (auto &e : arr) {
        if (q.empty()) {
            q.push(e);
            continue;
        } else {
            int t = q.top();
            if (t + e > val) {
                q.push(e);
            } else {
                q.pop();
                q.push(t + e);
            }
        }
    }

    if (q.size() > n) return false;
    return true;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    int k, n;
    cin >> k >> n;
    vector<int> arr(k);

    for (auto &e : arr) cin >> e;

    int i = 1;
    for (; i<=1000; i++) {
        if (check(i, n, arr)) break;
    }

    cout << i << '\n';
    return 0;
}
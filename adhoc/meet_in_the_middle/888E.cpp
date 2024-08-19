// https://codeforces.com/contest/888/problem/E

#include <bits/stdc++.h>
using namespace std;

#define int long long

int n, x, ans;
vector<int> arr;
vector<int> sa, sb;

void solve(int idx, int running_sm, int tp) {
    if (running_sm != 0) {
        if (tp == 0) sa.push_back(running_sm % x);
        else sb.push_back(running_sm % x);
    }

    int bound = (tp == 0 ? n/2 : n);
    for (int i=idx; i<bound; i++) {
        solve(i + 1, running_sm + arr[i], tp);
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    #ifdef LOCAL
        freopen("../in.txt", "r", stdin);
        freopen("../ou.txt", "w", stdout);
    #endif

    cin >> n >> x;
    arr.assign(n, 0);

    for (auto &e : arr) cin >> e;

    solve(0, 0, 0);
    solve(n/2, 0, 1);

    sort(sa.begin(), sa.end());
    sort(sb.begin(), sb.end());

    for (auto &e : sa) {
        if (e >= x) break;
        ans = max(ans, e);
    }

    for (auto &e : sb) {
        if (e >= x) break;
        ans = max(ans, e);
    }

    for (auto &e1 : sa) {
        int low = lower_bound(sb.begin(), sb.end(), x - e1) - sb.begin();

        low -= 1;
        if (e1 + sb[low] >= x) continue;

        ans = max(ans, e1 + sb[low]);
    }

    cout << ans << endl;

    return 0;
}